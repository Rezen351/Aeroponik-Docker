# 🚀 Aeroponik IoT Project

[![Docker](https://img.shields.io/badge/Docker-2496ED?style=for-the-badge&logo=docker&logoColor=white)](https://www.docker.com/)
[![Python](https://img.shields.io/badge/Python-3776AB?style=for-the-badge&logo=python&logoColor=white)](https://www.python.org/)
[![Node-RED](https://img.shields.io/badge/Node--RED-8F0000?style=for-the-badge&logo=nodered&logoColor=white)](https://nodered.org/)
[![MQTT](https://img.shields.io/badge/MQTT-3C5280?style=for-the-badge&logo=mqtt&logoColor=white)](https://mqtt.org/)
[![MariaDB](https://img.shields.io/badge/MariaDB-003545?style=for-the-badge&logo=mariadb&logoColor=white)](https://mariadb.org/)
[![MinIO](https://img.shields.io/badge/MinIO-C72E49?style=for-the-badge&logo=minio&logoColor=white)](https://min.io/)

## 📋 Table of Contents
- [Overview](#overview)
- [Services](#services)
- [Prerequisites](#prerequisites)
- [Running the Project](#running-the-project)
- [API Endpoints](#api-endpoints)
- [MQTT Integration](#mqtt-integration)
- [Directory Structure](#directory-structure)
- [Troubleshooting](#troubleshooting)
- [License](#license)

## 📖 Overview
This project is an IoT system integrating multiple services using Docker Compose. It includes:

- **Node-RED**: Flow-based programming tool for wiring together hardware devices, APIs, and online services.
- **MariaDB**: Relational database service for storing application data.
- **Mosquitto**: MQTT broker for lightweight messaging between IoT devices.
- **Python API Service**: Flask-based API service that connects to the MQTT broker and provides REST endpoints.
- **MinIO**: Object storage service compatible with Amazon S3 APIs.

## 🛠️ Services

### <details><summary>🌐 Node-RED</summary>

- Runs on port `1881` (mapped to container port `1880`).
- Stores data in the `node-red-data` directory.
- [Access Node-RED](http://localhost:1881)
- Features: Visual programming, extensive node library, real-time data flow.

</details>

### <details><summary>🗄️ MariaDB</summary>

- Runs on port `3308` (mapped to container port `3306`).
- Uses environment variables for credentials.
- Data persisted in Docker volume `db_data`.
- Compatible with MySQL syntax.

</details>

### <details><summary>📡 Mosquitto</summary>

- MQTT broker running on ports `1883` (MQTT) and `9001` (WebSockets).
- Configuration, data, and logs stored in `mosquitto` directory.
- Lightweight and efficient for IoT messaging.

</details>

### <details><summary>🐍 Python API Service</summary>

- Flask API running on port `5000`.
- Connects to MQTT broker at `mosquitto`.
- Provides REST endpoints for IoT data management.

</details>

### <details><summary>📦 MinIO</summary>

- Object storage service running on ports `9010` (API) and `9011` (Console).
- Uses environment variables for access credentials.
- [Access MinIO Console](http://localhost:9011)
- Data persisted in Docker volume `minio_data`.

</details>

## 📋 Prerequisites
- ✅ Docker and Docker Compose installed on your machine.
- ✅ Basic knowledge of IoT concepts and MQTT.

## ▶️ Running the Project
1. Clone the repository.
2. Create a `.env` file with necessary environment variables for MariaDB and MinIO.
3. Run the following command to start all services:
   ```bash
   docker-compose up -d
   ```
4. Access services via their respective ports.

## 🔗 API Endpoints

The Python API Service provides the following endpoints:

### GET /
Basic health check.
```bash
curl http://localhost:5000/
```
Response: `{"message": "Aeroponik IoT API is running!"}`

### GET /status
Returns service status and MQTT broker info.
```bash
curl http://localhost:5000/status
```
Response: `{"status": "running", "mqtt_broker": "mosquitto"}`

## 📡 MQTT Integration
- The Python API service subscribes to the MQTT topic `iot/cctv`.
- MQTT broker is accessible at `mosquitto` hostname within the Docker network.
- Use MQTT clients like [MQTT Explorer](https://mqtt-explorer.com/) to monitor topics.

## 📁 Directory Structure
```
aeroponik/
├── node-red-data/     # Node-RED data and configuration
├── mosquitto/         # Mosquitto configuration, data, and logs
├── python/            # Python API service source code and Dockerfile
├── docker-compose.yml # Docker Compose configuration
└── README.md          # This file
```

## 🔧 Troubleshooting

### Common Issues
- **Port conflicts**: Ensure ports 1881, 3308, 1883, 5000, 9010, 9011 are available.
- **Environment variables**: Check `.env` file for correct MariaDB and MinIO credentials.
- **Docker issues**: Run `docker-compose logs` to view service logs.

### Useful Commands
- View running containers: `docker ps`
- Stop services: `docker-compose down`
- Rebuild and restart: `docker-compose up --build -d`

## 📄 License
This project is licensed under the MIT License. See [LICENSE](LICENSE) for details.

---

⭐ If you find this project helpful, please give it a star!

[Report Issues](https://github.com/your-repo/issues) | [Contribute](https://github.com/your-repo/contributing)
