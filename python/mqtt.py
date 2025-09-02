import paho.mqtt.client as mqtt
import os

# --- PENGATURAN MQTT ---
MQTT_BROKER = os.getenv('MQTT_BROKER', 'mosquitto')
MQTT_PORT = 1883
MQTT_TOPIC = 'iot/cctv'

client = mqtt.Client()

def on_connect(client, userdata, flags, rc):
    print("Terhubung ke MQTT broker")
    client.subscribe(MQTT_TOPIC)

def on_message(client, userdata, msg):
    print(f"Pesan diterima: {msg.payload.decode()}")

def setup_mqtt():
    client.on_connect = on_connect
    client.on_message = on_message
    client.connect(MQTT_BROKER, MQTT_PORT, 60)
    client.loop_start()
    return client
