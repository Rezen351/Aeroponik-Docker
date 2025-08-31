# Aeroponik IoT Project

[![Docker](https://img.shields.io/badge/Docker-2496ED?style=for-the-badge&logo=docker&logoColor=white)](https://www.docker.com/)
[![Python](https://img.shields.io/badge/Python-3776AB?style=for-the-badge&logo=python&logoColor=white)](https://www.python.org/)
[![Node-RED](https://img.shields.io/badge/Node--RED-8F0000?style=for-the-badge&logo=nodered&logoColor=white)](https://nodered.org/)
[![MQTT](https://img.shields.io/badge/MQTT-3C5280?style=for-the-badge&logo=mqtt&logoColor=white)](https://mqtt.org/)
[![MariaDB](https://img.shields.io/badge/MariaDB-003545?style=for-the-badge&logo=mariadb&logoColor=white)](https://mariadb.org/)
[![MinIO](https://img.shields.io/badge/MinIO-C72E49?style=for-the-badge&logo=minio&logoColor=white)](https://min.io/)

## Overview

The Aeroponik IoT Project is a comprehensive Internet of Things (IoT) system designed for aeroponic applications. This project leverages Docker Compose to orchestrate multiple services, enabling seamless integration of hardware devices, data processing, and storage. It provides a robust platform for monitoring, controlling, and analyzing aeroponic systems through a combination of visual programming, messaging protocols, and RESTful APIs.

## Table of Contents

- [Features](#features)
- [Architecture](#architecture)
- [Prerequisites](#prerequisites)
- [Getting Started](#getting-started)
- [Services](#services)
- [API Endpoints](#api-endpoints)
- [MQTT Integration](#mqtt-integration)
- [Directory Structure](#directory-structure)
- [Troubleshooting](#troubleshooting)
- [Contributing](#contributing)
- [License](#license)

## Features

- **Scalable IoT Architecture**: Modular design supporting easy addition of new devices and services
- **Real-time Data Processing**: MQTT-based messaging for efficient device communication
- **Visual Programming Interface**: Node-RED for intuitive workflow creation
- **Data Persistence**: MariaDB for structured data storage and MinIO for object storage
- **RESTful API**: Flask-based service for external integrations
- **Containerized Deployment**: Docker Compose for consistent and portable environments

## Architecture

The system comprises the following core components:

- **Node-RED**: Flow-based programming tool for wiring hardware devices, APIs, and online services
- **MariaDB**: Relational database for storing application data with MySQL compatibility
- **Mosquitto**: Lightweight MQTT broker for IoT device messaging
- **Python API Service**: Flask-based REST API connecting MQTT broker and providing endpoints
- **MinIO**: S3-compatible object storage for media and large data files

## Prerequisites

- Docker and Docker Compose installed on your system
- Basic understanding of IoT concepts and MQTT protocol
- Git for repository cloning

## Getting Started

1. **Clone the Repository**
   ```bash
   git clone <repository-url>
   cd aeroponik
   ```

2. **Environment Configuration**
   Create a `.env` file in the root directory with the following variables:
   ```env
   # MariaDB Configuration
   MYSQL_ROOT_PASSWORD=your_root_password
   MYSQL_DATABASE=aeroponik_db
   MYSQL_USER=aeroponik_user
   MYSQL_PASSWORD=your_user_password

   # MinIO Configuration
   MINIO_ACCESS_KEY=your_access_key
   MINIO_SECRET_KEY=your_secret_key
   ```

3. **Launch Services**
   ```bash
   docker-compose up -d
   ```

4. **Access Services**
   - Node-RED: [http://localhost:1881](http://localhost:1881)
   - MinIO Console: [http://localhost:9011](http://localhost:9011)
   - Python API: [http://localhost:5000](http://localhost:5000)

## Services

### Node-RED
- **Port**: 1881 (container: 1880)
- **Purpose**: Visual programming interface for IoT workflows
- **Data Storage**: `node-red-data/` directory
- **Features**: Extensive node library, real-time data visualization

### MariaDB
- **Port**: 3308 (container: 3306)
- **Purpose**: Relational database for structured data
- **Persistence**: Docker volume `db_data`
- **Compatibility**: MySQL syntax support

### Mosquitto
- **Ports**: 1883 (MQTT), 9001 (WebSockets)
- **Purpose**: MQTT message broker for IoT communication
- **Storage**: Configuration, data, and logs in `mosquitto/` directory

### Python API Service
- **Port**: 5000
- **Purpose**: RESTful API for IoT data management
- **Integration**: Connects to MQTT broker for real-time data

### MinIO
- **Ports**: 9010 (API), 9011 (Console)
- **Purpose**: S3-compatible object storage
- **Persistence**: Docker volume `minio_data`

## API Endpoints

The Python API Service exposes the following endpoints:

### GET /
Health check endpoint.
```bash
curl http://localhost:5000/
```
**Response**: `{"message": "Aeroponik IoT API is running!"}`

### GET /status
Service status and MQTT broker information.
```bash
curl http://localhost:5000/status
```
**Response**: `{"status": "running", "mqtt_broker": "mosquitto"}`

## MQTT Integration

- **Broker Hostname**: `mosquitto` (within Docker network)
- **Subscribed Topic**: `iot/cctv`
- **Client Tools**: Use [MQTT Explorer](https://mqtt-explorer.com/) for topic monitoring
- **WebSocket Support**: Available on port 9001 for browser-based clients

## Directory Structure

```
aeroponik/
├── docker-compose.yml    # Docker Compose configuration
├── .env                  # Environment variables (create this file)
├── node-red-data/        # Node-RED data and configuration
│   ├── flows.json        # Node-RED flow definitions
│   ├── package.json      # Node-RED dependencies
│   └── settings.js       # Node-RED configuration
├── mosquitto/            # Mosquitto MQTT broker
│   ├── config/           # Broker configuration
│   ├── data/             # Persistent data
│   └── log/              # Log files
├── python/               # Python API service
│   ├── app.py            # Main Flask application
│   ├── requirements.txt  # Python dependencies
│   └── Dockerfile        # Python service container
└── README.md             # Project documentation
```

## Troubleshooting

### Common Issues

- **Port Conflicts**: Ensure ports 1881, 3308, 1883, 5000, 9010, 9011 are available
- **Environment Variables**: Verify `.env` file contains correct credentials
- **Docker Issues**: Check service logs with `docker-compose logs`

### Useful Commands

- View running containers: `docker ps`
- Stop all services: `docker-compose down`
- Restart with rebuild: `docker-compose up --build -d`
- View specific service logs: `docker-compose logs <service-name>`

## Contributing

We welcome contributions to the Aeroponik IoT Project. Please follow these steps:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

**Project Repository**: [GitHub Link]  
**Documentation**: [Wiki Link]  
**Issues**: [Issue Tracker]
