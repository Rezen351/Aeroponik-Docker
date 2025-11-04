import cv2
import time
import os

# --- PENGATURAN KAMERA UNTUK 4 CCTV ---
CCTV_URLS = [
    os.getenv('CCTV_URL_1', 'rtsp://admin:Admin_TF24!@192.168.1.110:554/stream1'),
    os.getenv('CCTV_URL_2', 'rtsp://admin:Admin_TF24!@192.168.1.101:554/stream1'),
    os.getenv('CCTV_URL_3', 'rtsp://admin:Admin_TF24!@192.168.1.102:554/stream1'),
    os.getenv('CCTV_URL_4', 'rtsp://admin:Admin_TF24!@192.168.1.103:554/stream1')
]

cameras = [None] * 4
def initialize_camera(index):
    """Inisialisasi kamera berdasarkan indeks."""
    global cameras
    print(f"Mencoba menginisialisasi kamera {index+1}...")
    url = CCTV_URLS[index]
    if not url:
        print(f"Error: CCTV_URL_{index+1} environment variable tidak diatur.")
        return False
        
    cameras[index] = cv2.VideoCapture(url)
    if not cameras[index].isOpened():
        print(f"Error: Tidak bisa membuka stream RTSP di {url}")
        return False
    
    print(f"Kamera {index+1} berhasil diinisialisasi.")
    return True

def generate_frames(camera_index):
    """Generator untuk mengambil frame dari kamera tertentu dan menyajikannya sebagai MJPEG."""
    while True:
        camera = cameras[camera_index]
        # Jika kamera tidak terinisialisasi atau koneksi terputus, coba inisialisasi ulang
        if camera is None or not camera.isOpened():
            if not initialize_camera(camera_index):
                print(f"Inisialisasi kamera {camera_index+1} gagal, mencoba lagi dalam 5 detik...")
                time.sleep(5)
                continue
        
        # Baca satu frame dari kamera
        success, frame = camera.read()
        if not success:
            print(f"Gagal membaca frame dari kamera {camera_index+1}, koneksi mungkin terputus. Mencoba re-inisialisasi...")
            camera.release()
            time.sleep(2)
            continue

        # Resize frame untuk performa lebih baik
        frame = cv2.resize(frame, (640, 480))

        # Encode frame ke format JPEG dengan kualitas lebih rendah untuk kecepatan
        ret, buffer = cv2.imencode('.jpg', frame, [cv2.IMWRITE_JPEG_QUALITY, 70])
        if not ret:
            continue

        # Konversi buffer ke bytes
        frame_bytes = buffer.tobytes()

        # Sajikan frame sebagai bagian dari multipart response
        yield (b'--frame\r\n'
               b'Content-Type: image/jpeg\r\n\r\n' + frame_bytes + b'\r\n')

        # Tambahkan delay untuk mengurangi FPS dan meningkatkan performa
        time.sleep(0.1)  # Sekitar 10 FPS



def initialize_all_cameras():
    """Inisialisasi semua kamera."""
    for i in range(4):
        initialize_camera(i)
