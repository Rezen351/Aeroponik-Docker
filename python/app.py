from flask import Flask, jsonify
import paho.mqtt.client as mqtt
import os

app = Flask(__name__)

# MQTT settings
MQTT_BROKER = os.getenv('MQTT_BROKER', 'mosquitto')
MQTT_PORT = 1883
MQTT_TOPIC = 'iot/cctv'

# MQTT client
client = mqtt.Client()

def on_connect(client, userdata, flags, rc):
    print("Connected to MQTT broker")
    client.subscribe(MQTT_TOPIC)

def on_message(client, userdata, msg):
    print(f"Message received: {msg.payload.decode()}")

client.on_connect = on_connect
client.on_message = on_message
client.connect(MQTT_BROKER, MQTT_PORT, 60)
client.loop_start()

@app.route('/')
def home():
    return jsonify({"message": "API is running"})

@app.route('/status')
def status():
    return jsonify({"status": "active", "mqtt_broker": MQTT_BROKER})

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)
