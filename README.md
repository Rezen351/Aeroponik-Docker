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
- [Database Setup](#database-setup)
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

## Database Setup

### Aeroponik Data Table

The project includes a MariaDB table for storing aeroponik sensor data. The table `box_aeroponik` is automatically created during database initialization.

#### Table Structure
```sql
CREATE TABLE `box_aeroponik` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `box` tinyint(4) NOT NULL,
  `temp1` float DEFAULT NULL,
  `temp2` float DEFAULT NULL,
  `temp3` float DEFAULT NULL,
  `hum1` float DEFAULT NULL,
  `hum2` float DEFAULT NULL,
  `ec` float DEFAULT NULL,
  `ph` float DEFAULT NULL,
  `lv` tinyint(4) DEFAULT NULL,
  `time` timestamp NOT NULL DEFAULT current_timestamp(),
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
```

#### Manual Table Creation (if needed)
If you need to recreate or modify the table:

1. **Access the MariaDB container**:
   ```bash
   docker-compose exec mariadb mysql -u root -p
   ```

2. **Execute the SQL script**:
   ```bash
   docker-compose exec mariadb sh -c "mysql -u root -pnodered nodered < /tmp/init_box_aeroponik.sql"
   ```

3. **Verify table creation**:
   ```bash
   docker-compose exec mariadb mysql -u root -p -e "USE nodered; SHOW TABLES; DESCRIBE box_aeroponik;"
   ```

#### Table Fields Description

| Field | Type | Description | Unit |
|-------|------|-------------|------|
| `id` | int(11) | Auto-incrementing primary key | - |
| `box` | tinyint(4) | Box identifier | 1-255 |
| `temp1` | float | Temperature sensor 1 | °C |
| `temp2` | float | Temperature sensor 2 | °C |
| `temp3` | float | Temperature sensor 3 | °C |
| `hum1` | float | Humidity sensor 1 | % |
| `hum2` | float | Humidity sensor 2 | % |
| `ec` | float | Electrical conductivity | μS/cm |
| `ph` | float | pH level | - |
| `lv` | tinyint(4) | Liquid level sensor | - |
| `time` | timestamp | Data collection timestamp | - |

## Services

| Service | Ports | Purpose | Storage/Persistence | Access URL |
|---------|-------|---------|-------------------|------------|
| **Node-RED** | 1881 (1880) | Visual programming interface for IoT workflows | `node-red-data/` directory | [http://localhost:1881](http://localhost:1881) |
| **MariaDB** | 3308 (3306) | Relational database for structured data | Docker volume `db_data` | `mysql -h localhost -P 3308 -u root -p` |
| **Mosquitto** | 1883, 9001 | MQTT message broker for IoT communication | `mosquitto/` directory | MQTT clients connect to `localhost:1883` |
| **Python API** | 5000 | RESTful API for IoT data management | - | [http://localhost:5000](http://localhost:5000) |
| **MinIO** | 9010, 9011 | S3-compatible object storage | Docker volume `minio_data` | [http://localhost:9011](http://localhost:9011) |

### Service Details

#### Node-RED
- **Features**: Extensive node library, real-time data visualization
- **Configuration**: Flows stored in `flows.json`

#### MariaDB
- **Compatibility**: MySQL syntax support
- **Database**: `nodered` (default)
- **Admin Access**: [http://localhost:8080](http://localhost:8080) (Adminer)

#### Mosquitto
- **Protocol**: MQTT 3.1.1 and 5.0
- **WebSocket**: Available on port 9001 for browser clients

#### Python API Service
- **Framework**: Flask
- **Integration**: Connects to MQTT broker for real-time data

#### MinIO
- **API**: S3-compatible REST API on port 9010
- **Console**: Web interface on port 9011

## API Endpoints

The Python API Service exposes the following endpoints:

| Method | Endpoint | Description | Example Request | Response |
|--------|----------|-------------|----------------|----------|
| `GET` | `/` | Health check endpoint | `curl http://localhost:5000/` | `{"message": "Aeroponik IoT API is running!"}` |
| `GET` | `/status` | Service status and MQTT broker information | `curl http://localhost:5000/status` | `{"status": "running", "mqtt_broker": "mosquitto"}` |

## MQTT Integration

- **Broker Hostname**: `mosquitto` (within Docker network)
- **Subscribed Topic**: `iot/cctv`
- **Client Tools**: Use [MQTT Explorer](https://mqtt-explorer.com/) for topic monitoring
- **WebSocket Support**: Available on port 9001 for browser-based clients

## Directory Structure

```
aeroponik/
├── docker-compose.yml          # Docker Compose configuration
├── init_box_aeroponik.sql      # Database initialization script
├── .env                        # Environment variables (create this file)
├── .env.example                # Environment variables template
├── .gitignore                  # Git ignore rules
├── README.md                   # Project documentation
├── TODO.md                     # Project tasks and progress
├── node-red-data/              # Node-RED data and configuration
│   ├── flows.json              # Node-RED flow definitions
│   ├── package.json            # Node-RED dependencies
│   ├── settings.js             # Node-RED configuration
│   └── lib/                    # Node-RED custom libraries
├── mosquitto/                  # Mosquitto MQTT broker
│   ├── config/
│   │   └── mosquitto.conf      # Broker configuration
│   ├── data/                   # Persistent data
│   └── log/                    # Log files
├── python/                     # Python API service
│   ├── app.py                  # Main Flask application
│   ├── requirements.txt        # Python dependencies
│   ├── Dockerfile              # Python service container
│   └── app/                    # Application modules
└── .git/                       # Git repository data
```

### Key Files Description

| File/Directory | Purpose |
|----------------|---------|
| `docker-compose.yml` | Multi-service container orchestration |
| `init_box_aeroponik.sql` | Database table creation script |
| `.env` | Environment variables for services |
| `node-red-data/` | Node-RED flows and configuration |
| `mosquitto/` | MQTT broker configuration and data |
| `python/` | Flask API service source code |

## Troubleshooting

### Common Issues

- **Port Conflicts**: Ensure ports 1881, 3308, 1883, 5000, 9010, 9011 are available
- **Environment Variables**: Verify `.env` file contains correct credentials
- **Docker Issues**: Check service logs with `docker-compose logs`

### Useful Commands

| Command | Description |
|---------|-------------|
| `docker ps` | View running containers |
| `docker-compose down` | Stop all services |
| `docker-compose up -d` | Start all services in background |
| `docker-compose up --build -d` | Start with rebuild of images |
| `docker-compose logs <service-name>` | View logs for specific service |
| `docker-compose logs` | View logs for all services |
| `docker-compose restart <service-name>` | Restart specific service |
| `docker-compose exec <service-name> bash` | Access container shell |

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
