-- Adminer 5.2.1 MariaDB 10.6.23-MariaDB-ubu2204 dump

SET NAMES utf8;
SET time_zone = '+00:00';
SET foreign_key_checks = 0;
SET sql_mode = 'NO_AUTO_VALUE_ON_ZERO';

SET NAMES utf8mb4;

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


-- 2025-08-31 04:50:13 UTC
