import cv2
import time
import os
import io
from datetime import datetime
from minio import Minio
from minio.error import S3Error
from flask import Flask, jsonify, Response, render_template, request
from mqtt import setup_mqtt, MQTT_BROKER

# --- PENGATURAN KAMERA UNTUK 3 CC
CCTV_URLS = [
    os.getenv('CCTV_URL_1', 'rtsp://admin:Admin_TF24!@192.168.1.100:554/stream1'),
    os.getenv('CCTV_URL_2', 'rtsp://admin:Admin_TF24!@192.168.1.101:554/stream1'),
    os.getenv('CCTV_URL_3', 'rtsp://admin:Admin_TF24!@192.168.1.103:554/stream1')
]

# MinIO configuration from environment variables
MINIO_ENDPOINT = 'minio:9000'
MINIO_ACCESS_KEY = os.getenv('MINIO_ACCESS_KEY', 'minioadmin')
MINIO_SECRET_KEY = os.getenv('MINIO_SECRET_KEY', 'minioadmin')
MINIO_BUCKET = os.getenv('MINIO_BUCKET', 'camera-images')

# Initialize MinIO client
minio_client = Minio(
    MINIO_ENDPOINT,
    access_key=MINIO_ACCESS_KEY,
    secret_key=MINIO_SECRET_KEY,
    secure=False
)

# Ensure bucket exists
if not minio_client.bucket_exists(MINIO_BUCKET):
    minio_client.make_bucket(MINIO_BUCKET)

app = Flask(__name__)

# Setup MQTT
mqtt_client = setup_mqtt()

from camera import generate_frames, initialize_all_cameras, cameras, initialize_camera

# --- ENDPOINTS API ---

@app.route('/')
def home():
    """Endpoint utama yang menyajikan halaman HTML untuk menampilkan video."""
    return render_template('index.html')

@app.route('/video_feed/<int:camera_id>')
def video_feed(camera_id):
    """Endpoint yang menghasilkan stream video MJPEG untuk kamera tertentu."""
    if camera_id < 1 or camera_id > 3:
        return "Invalid camera ID", 400
    return Response(generate_frames(camera_id - 1),
                    mimetype='multipart/x-mixed-replace; boundary=frame')

@app.route('/status')
def status():
    """Endpoint status."""
    camera_status = [cam.isOpened() if cam else False for cam in cameras]
    return jsonify({
        "status": "active",
        "mqtt_broker": MQTT_BROKER,
        "cameras_connected": camera_status
    })

def upload_image_to_minio(camera_index, frame):
    """Upload a frame to MinIO."""
    try:
        timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
        object_name = f"camera_{camera_index+1}_{timestamp}.jpg"
        # Encode frame to JPEG
        ret, buffer = cv2.imencode('.jpg', frame)
        if not ret:
            print(f"Failed to encode frame for camera {camera_index+1}")
            return
        frame_bytes = buffer.tobytes()
        # Upload to MinIO
        minio_client.put_object(
            MINIO_BUCKET,
            object_name,
            data=io.BytesIO(frame_bytes),
            length=len(frame_bytes),
            content_type='image/jpeg'
        )
        print(f"Uploaded {object_name} to MinIO")
    except S3Error as exc:
        print(f"Error uploading image: {exc}")

@app.route('/upload')
def upload():
    """Endpoint to upload current frames from all cameras to MinIO."""
    results = []
    for idx in range(3):
        camera = cameras[idx]
        if camera is None or not camera.isOpened():
            print(f"Kamera {idx+1} tidak terhubung, mencoba inisialisasi ulang untuk upload...")
            if not initialize_camera(idx):
                print(f"Inisialisasi ulang gagal untuk kamera {idx+1}.")
                results.append({
                    "camera_index": idx + 1,
                    "status": "failed",
                    "reason": "Failed to initialize camera"
                })
                continue
            camera = cameras[idx]

        success, frame = camera.read()
        if not success:
            print(f"Gagal membaca frame dari kamera {idx+1} untuk upload.")
            results.append({
                "camera_index": idx + 1,
                "status": "failed",
                "reason": "Failed to read frame"
            })
            continue

        # Resize frame
        frame = cv2.resize(frame, (640, 480))
        # Upload to MinIO
        upload_image_to_minio(idx, frame)
        results.append({
            "camera_index": idx + 1,
            "status": "success",
            "minio_path": f"camera_{idx+1}_{datetime.now().strftime('%Y%m%d_%H%M%S')}.jpg"
        })
    return jsonify({"upload_results": results})

@app.route('/image/<path:filename>')
def get_image(filename):
    """Endpoint to retrieve an image by filename from MinIO."""
    try:
        response = minio_client.get_object(MINIO_BUCKET, filename)
        image_data = response.read()
        response.close()
        return Response(image_data, mimetype='image/jpeg')
    except S3Error as exc:
        if exc.code == 'NoSuchKey':
            return jsonify({"error": "Image not found"}), 404
        return jsonify({"error": f"Error retrieving image: {exc}"}), 500

@app.route('/image-list/<int:camera_id>')
def get_image_list(camera_id):
    """Endpoint to list images for a specific camera from MinIO."""
    if camera_id < 1 or camera_id > 3:
        return jsonify({"error": "Invalid camera ID"}), 400

    prefix = f"camera_{camera_id}_"
    objects = list(minio_client.list_objects(MINIO_BUCKET, prefix=prefix))
    if not objects:
        return jsonify({"images": []})

    # Sort by last_modified descending
    objects.sort(key=lambda obj: obj.last_modified, reverse=True)
    # Limit to last 80 images
    objects = objects[:80]

    image_list = [
        {
            "filename": obj.object_name,
            "last_modified": obj.last_modified.isoformat() if obj.last_modified else None,
            "size": obj.size
        }
        for obj in objects
    ]
    return jsonify({"images": image_list})

if __name__ == '__main__':
    initialize_all_cameras()
    app.run(host='0.0.0.0', port=5000, debug=True, use_reloader=False)
