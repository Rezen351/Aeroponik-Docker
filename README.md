# Aeroponik IoT Project

## Overview
This project is an IoT system integrating multiple services using Docker Compose. It includes:

- **Node-RED**: Flow-based programming tool for wiring together hardware devices, APIs, and online services.
- **MariaDB**: Relational database service for storing application data.
- **Mosquitto**: MQTT broker for lightweight messaging between IoT devices.
- **Python API Service**: Flask-based API service that connects to the MQTT broker and provides REST endpoints.
- **MinIO**: Object storage service compatible with Amazon S3 APIs.

## Services

### Node-RED
- Runs on port `1881` (mapped to container port `1880`).
- Stores data in the `node-red-data` directory.
- Access via `http://localhost:1881`.

### MariaDB
- Runs on port `3308` (mapped to container port `3306`).
- Uses environment variables for credentials.
- Data persisted in Docker volume `db_data`.

### Mosquitto
- MQTT broker running on ports `1883` (MQTT) and `9001` (WebSockets).
- Configuration, data, and logs stored in `mosquitto` directory.

### Python API Service
- Flask API running on port `5000`.
- Connects to MQTT broker at `mosquitto`.
- Provides endpoints:
  - `/` : Basic health check returning a JSON message.
  - `/status` : Returns service status and MQTT broker info.

### MinIO
- Object storage service running on ports `9010` (API) and `9011` (Console).
- Uses environment variables for access credentials.
- Data persisted in Docker volume `minio_data`.

## Prerequisites
- Docker and Docker Compose installed on your machine.

## Running the Project
1. Clone the repository.
2. Create a `.env` file with necessary environment variables for MariaDB and MinIO.
3. Run the following command to start all services:
   ```bash
   docker-compose up -d
   ```
4. Access services via their respective ports.

## MQTT Integration
- The Python API service subscribes to the MQTT topic `iot/cctv`.
- MQTT broker is accessible at `mosquitto` hostname within the Docker network.

## Directory Structure
- `node-red-data/` : Node-RED data and configuration.
- `mosquitto/` : Mosquitto configuration, data, and logs.
- `python/` : Python API service source code and Dockerfile.

## License
This project is licensed under the MIT License.
