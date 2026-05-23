-- ============================================================
-- CamMatch - setup complet baza de date MySQL
-- Acest script recreeaza baza de date cammatch_final de la zero.
-- ATENTIE: sterge baza cammatch_final existenta si o creeaza din nou.
--
-- Cum se foloseste:
-- 1) Opreste aplicatia Spring Boot daca ruleaza.
-- 2) Deschide MySQL Workbench si conecteaza-te ca root.
-- 3) Ruleaza tot acest fisier SQL.
-- 4) In application.properties foloseste:
--      spring.datasource.url=jdbc:mysql://localhost:3306/cammatch_final?createDatabaseIfNotExist=true
--      spring.datasource.username=cammatch_user
--      spring.datasource.password=cammatch123
-- 5) Porneste proiectul cu:
--      mvn spring-boot:run
-- ============================================================

DROP DATABASE IF EXISTS cammatch_final;

CREATE DATABASE cammatch_final
  CHARACTER SET utf8mb4
  COLLATE utf8mb4_unicode_ci;

USE cammatch_final;

-- User MySQL dedicat aplicatiei.
-- Daca folosesti root fara parola in application.properties, aceasta sectiune nu este obligatorie,
-- dar este recomandata pentru un proiect mai curat.
CREATE USER IF NOT EXISTS 'cammatch_user'@'localhost' IDENTIFIED BY 'cammatch123';
ALTER USER 'cammatch_user'@'localhost' IDENTIFIED BY 'cammatch123';

CREATE USER IF NOT EXISTS 'cammatch_user'@'127.0.0.1' IDENTIFIED BY 'cammatch123';
ALTER USER 'cammatch_user'@'127.0.0.1' IDENTIFIED BY 'cammatch123';

GRANT ALL PRIVILEGES ON cammatch_final.* TO 'cammatch_user'@'localhost';
GRANT ALL PRIVILEGES ON cammatch_final.* TO 'cammatch_user'@'127.0.0.1';
FLUSH PRIVILEGES;


-- ============================================================
-- Structura tabelelor si date initiale exportate din baza existenta
-- ============================================================

-- MySQL dump 10.13  Distrib 8.0.42, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: cammatch_final
-- ------------------------------------------------------
-- Server version	8.0.42

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `camera_ratings`
--

DROP TABLE IF EXISTS `camera_ratings`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `camera_ratings` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `created_at` datetime(6) DEFAULT NULL,
  `stars` int NOT NULL,
  `updated_at` datetime(6) DEFAULT NULL,
  `camera_id` bigint NOT NULL,
  `user_id` bigint NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `UKh16w5a4wb9hthdhtbbd32e1gf` (`camera_id`,`user_id`),
  KEY `FKdp0sgpo13qteu77edc7p0c5hn` (`user_id`),
  CONSTRAINT `FKdp0sgpo13qteu77edc7p0c5hn` FOREIGN KEY (`user_id`) REFERENCES `users` (`id`),
  CONSTRAINT `FKm48sxu62lcutx5xyicl72suuf` FOREIGN KEY (`camera_id`) REFERENCES `cameras` (`id`),
  CONSTRAINT `camera_ratings_chk_1` CHECK (((`stars` <= 5) and (`stars` >= 1)))
) ENGINE=InnoDB AUTO_INCREMENT=224 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `camera_ratings`
--

LOCK TABLES `camera_ratings` WRITE;
/*!40000 ALTER TABLE `camera_ratings` DISABLE KEYS */;
INSERT INTO `camera_ratings` VALUES (114,'2026-05-23 19:11:02.442851',4,'2026-05-23 19:11:02.442851',2,5),(115,'2026-05-23 19:11:02.468544',3,'2026-05-23 19:11:02.468544',1,5),(116,'2026-05-23 19:11:02.470564',4,'2026-05-23 19:11:02.470564',1,6),(117,'2026-05-23 19:11:02.473590',2,'2026-05-23 19:11:02.473590',4,5),(118,'2026-05-23 19:11:02.474599',3,'2026-05-23 19:11:02.474599',4,6),(119,'2026-05-23 19:11:02.475621',2,'2026-05-23 19:11:02.475621',4,7),(120,'2026-05-23 19:11:02.479390',5,'2026-05-23 19:11:02.479390',3,5),(121,'2026-05-23 19:11:02.480415',5,'2026-05-23 19:11:02.480415',3,6),(122,'2026-05-23 19:11:02.481437',4,'2026-05-23 19:11:02.481437',3,7),(123,'2026-05-23 19:11:02.482596',5,'2026-05-23 19:11:02.482596',3,8),(124,'2026-05-23 19:11:02.485634',1,'2026-05-23 19:11:02.485634',6,5),(125,'2026-05-23 19:11:02.485634',2,'2026-05-23 19:11:02.485634',6,6),(126,'2026-05-23 19:11:02.487140',2,'2026-05-23 19:11:02.487140',6,7),(127,'2026-05-23 19:11:02.488179',1,'2026-05-23 19:11:02.488179',6,8),(128,'2026-05-23 19:11:02.489286',3,'2026-05-23 19:11:02.489286',6,9),(129,'2026-05-23 19:11:02.491921',4,'2026-05-23 19:11:02.491921',37,5),(130,'2026-05-23 19:11:02.494179',3,'2026-05-23 19:11:02.494179',37,6),(131,'2026-05-23 19:11:02.495568',5,'2026-05-23 19:11:02.495568',37,7),(132,'2026-05-23 19:11:02.497075',4,'2026-05-23 19:11:02.497075',37,8),(133,'2026-05-23 19:11:02.498091',4,'2026-05-23 19:11:02.498091',37,9),(134,'2026-05-23 19:11:02.501846',3,'2026-05-23 19:11:02.501846',24,5),(135,'2026-05-23 19:11:02.502850',3,'2026-05-23 19:11:02.502850',24,6),(136,'2026-05-23 19:11:02.503853',4,'2026-05-23 19:11:02.503853',24,7),(137,'2026-05-23 19:11:02.503853',2,'2026-05-23 19:11:02.503853',24,8),(138,'2026-05-23 19:11:02.504875',3,'2026-05-23 19:11:02.504875',24,9),(139,'2026-05-23 19:11:02.510166',2,'2026-05-23 19:11:02.510166',20,5),(140,'2026-05-23 19:11:02.513325',5,'2026-05-23 19:11:02.513325',19,5),(141,'2026-05-23 19:11:02.514349',4,'2026-05-23 19:11:02.514349',19,6),(142,'2026-05-23 19:11:02.516430',4,'2026-05-23 19:11:02.516430',21,5),(143,'2026-05-23 19:11:02.517419',4,'2026-05-23 19:11:02.517419',21,6),(144,'2026-05-23 19:11:02.517938',5,'2026-05-23 19:11:02.517938',21,7),(145,'2026-05-23 19:11:02.521591',3,'2026-05-23 19:11:02.521591',23,5),(146,'2026-05-23 19:11:02.521591',4,'2026-05-23 19:11:02.521591',23,6),(147,'2026-05-23 19:11:02.522597',3,'2026-05-23 19:11:02.522597',23,7),(148,'2026-05-23 19:11:02.524618',4,'2026-05-23 19:11:02.524618',23,8),(149,'2026-05-23 19:11:02.527004',2,'2026-05-23 19:11:02.527004',36,5),(150,'2026-05-23 19:11:02.527004',3,'2026-05-23 19:11:02.527004',36,6),(151,'2026-05-23 19:11:02.528434',2,'2026-05-23 19:11:02.528434',36,7),(152,'2026-05-23 19:11:02.529434',3,'2026-05-23 19:11:02.529434',36,8),(153,'2026-05-23 19:11:02.530451',1,'2026-05-23 19:11:02.530451',36,9),(154,'2026-05-23 19:11:02.533485',5,'2026-05-23 19:11:02.533485',33,5),(155,'2026-05-23 19:11:02.534497',5,'2026-05-23 19:11:02.534497',33,6),(156,'2026-05-23 19:11:02.535500',4,'2026-05-23 19:11:02.535500',33,7),(157,'2026-05-23 19:11:02.537007',5,'2026-05-23 19:11:02.537007',33,8),(158,'2026-05-23 19:11:02.537007',4,'2026-05-23 19:11:02.537007',33,9),(159,'2026-05-23 19:11:02.540062',1,'2026-05-23 19:11:02.540062',12,5),(160,'2026-05-23 19:11:02.541179',2,'2026-05-23 19:11:02.541179',12,6),(161,'2026-05-23 19:11:02.542194',2,'2026-05-23 19:11:02.542194',12,7),(162,'2026-05-23 19:11:02.542194',1,'2026-05-23 19:11:02.542194',12,8),(163,'2026-05-23 19:11:02.543206',3,'2026-05-23 19:11:02.543206',12,9),(164,'2026-05-23 19:11:02.547437',3,'2026-05-23 19:11:02.547437',7,5),(165,'2026-05-23 19:11:02.549955',5,'2026-05-23 19:11:02.549955',10,5),(166,'2026-05-23 19:11:02.550959',4,'2026-05-23 19:11:02.550959',10,6),(167,'2026-05-23 19:11:02.553003',2,'2026-05-23 19:11:02.553003',8,5),(168,'2026-05-23 19:11:02.554074',2,'2026-05-23 19:11:02.554074',8,6),(169,'2026-05-23 19:11:02.555079',3,'2026-05-23 19:11:02.555079',8,7),(170,'2026-05-23 19:11:02.558120',5,'2026-05-23 19:11:02.558120',11,5),(171,'2026-05-23 19:11:02.559189',4,'2026-05-23 19:11:02.559189',11,6),(172,'2026-05-23 19:11:02.559189',5,'2026-05-23 19:11:02.559189',11,7),(173,'2026-05-23 19:11:02.560646',4,'2026-05-23 19:11:02.560646',11,8),(174,'2026-05-23 19:11:02.563822',4,'2026-05-23 19:11:02.563822',29,5),(175,'2026-05-23 19:11:02.564839',4,'2026-05-23 19:11:02.564839',29,6),(176,'2026-05-23 19:11:02.565946',5,'2026-05-23 19:11:02.565946',29,7),(177,'2026-05-23 19:11:02.565946',3,'2026-05-23 19:11:02.565946',29,8),(178,'2026-05-23 19:11:02.567439',4,'2026-05-23 19:11:02.567439',29,9),(179,'2026-05-23 19:11:02.570574',3,'2026-05-23 19:11:02.570574',30,5),(180,'2026-05-23 19:11:02.571690',4,'2026-05-23 19:11:02.571690',30,6),(181,'2026-05-23 19:11:02.572859',3,'2026-05-23 19:11:02.572859',30,7),(182,'2026-05-23 19:11:02.573872',4,'2026-05-23 19:11:02.573872',30,8),(183,'2026-05-23 19:11:02.574890',2,'2026-05-23 19:11:02.574890',30,9),(184,'2026-05-23 19:11:02.577407',2,'2026-05-23 19:11:02.577407',32,5),(185,'2026-05-23 19:11:02.577407',3,'2026-05-23 19:11:02.577407',32,6),(186,'2026-05-23 19:11:02.578521',2,'2026-05-23 19:11:02.578521',32,7),(187,'2026-05-23 19:11:02.578521',3,'2026-05-23 19:11:02.578521',32,8),(188,'2026-05-23 19:11:02.580595',1,'2026-05-23 19:11:02.580595',32,9),(189,'2026-05-23 19:11:02.584677',1,'2026-05-23 19:11:02.584677',25,5),(190,'2026-05-23 19:11:02.587196',4,'2026-05-23 19:11:02.587196',26,5),(191,'2026-05-23 19:11:02.588322',3,'2026-05-23 19:11:02.588322',26,6),(192,'2026-05-23 19:11:02.590678',3,'2026-05-23 19:11:02.590678',27,5),(193,'2026-05-23 19:11:02.590678',3,'2026-05-23 19:11:02.590678',27,6),(194,'2026-05-23 19:11:02.591703',4,'2026-05-23 19:11:02.591703',27,7),(195,'2026-05-23 19:11:02.593726',5,'2026-05-23 19:11:02.593726',28,5),(196,'2026-05-23 19:11:02.594739',4,'2026-05-23 19:11:02.594739',28,6),(197,'2026-05-23 19:11:02.595751',4,'2026-05-23 19:11:02.595751',28,7),(198,'2026-05-23 19:11:02.595751',3,'2026-05-23 19:11:02.595751',28,8),(199,'2026-05-23 19:11:02.598303',2,'2026-05-23 19:11:02.598303',34,5),(200,'2026-05-23 19:11:02.599307',2,'2026-05-23 19:11:02.599307',34,6),(201,'2026-05-23 19:11:02.599307',3,'2026-05-23 19:11:02.599307',34,7),(202,'2026-05-23 19:11:02.601449',2,'2026-05-23 19:11:02.601449',34,8),(203,'2026-05-23 19:11:02.602608',1,'2026-05-23 19:11:02.602608',34,9),(204,'2026-05-23 19:11:02.604996',5,'2026-05-23 19:11:02.604996',35,5),(205,'2026-05-23 19:11:02.606021',4,'2026-05-23 19:11:02.606021',35,6),(206,'2026-05-23 19:11:02.607012',5,'2026-05-23 19:11:02.607012',35,7),(207,'2026-05-23 19:11:02.608506',4,'2026-05-23 19:11:02.608506',35,8),(208,'2026-05-23 19:11:02.608506',5,'2026-05-23 19:11:02.608506',35,9),(209,'2026-05-23 19:11:02.611733',4,'2026-05-23 19:11:02.611733',13,5),(210,'2026-05-23 19:11:02.612755',4,'2026-05-23 19:11:02.612755',13,6),(211,'2026-05-23 19:11:02.613776',5,'2026-05-23 19:11:02.613776',13,7),(212,'2026-05-23 19:11:02.613776',3,'2026-05-23 19:11:02.613776',13,8),(213,'2026-05-23 19:11:02.614786',4,'2026-05-23 19:11:02.614786',13,9),(214,'2026-05-23 19:11:02.618379',2,'2026-05-23 19:11:02.618379',16,5),(215,'2026-05-23 19:11:02.622183',5,'2026-05-23 19:11:02.622183',17,5),(216,'2026-05-23 19:11:02.623343',5,'2026-05-23 19:11:02.623343',17,6),(217,'2026-05-23 19:11:02.626376',1,'2026-05-23 19:11:02.626376',18,5),(218,'2026-05-23 19:11:02.626376',2,'2026-05-23 19:11:02.626376',18,6),(219,'2026-05-23 19:11:02.627883',2,'2026-05-23 19:11:02.627883',18,7),(220,'2026-05-23 19:11:02.630385',4,'2026-05-23 19:11:02.630385',15,5),(221,'2026-05-23 19:11:02.631442',3,'2026-05-23 19:11:02.631442',15,6),(222,'2026-05-23 19:11:02.632559',5,'2026-05-23 19:11:02.632559',15,7),(223,'2026-05-23 19:11:02.633574',4,'2026-05-23 19:11:02.633574',15,8);
/*!40000 ALTER TABLE `camera_ratings` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `cameras`
--

DROP TABLE IF EXISTS `cameras`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `cameras` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `average_rating` double NOT NULL,
  `battery_shots` int NOT NULL,
  `brand` varchar(80) COLLATE utf8mb4_unicode_ci NOT NULL,
  `created_at` datetime(6) DEFAULT NULL,
  `description` varchar(1500) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `image_url` varchar(500) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `model` varchar(120) COLLATE utf8mb4_unicode_ci NOT NULL,
  `photography_type` varchar(80) COLLATE utf8mb4_unicode_ci NOT NULL,
  `price` decimal(10,2) NOT NULL,
  `rating_count` int NOT NULL,
  `resolution_mp` double NOT NULL,
  `sensor` varchar(80) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `type` varchar(80) COLLATE utf8mb4_unicode_ci NOT NULL,
  `video` varchar(80) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`id`),
  CONSTRAINT `cameras_chk_1` CHECK ((`battery_shots` >= 1))
) ENGINE=InnoDB AUTO_INCREMENT=42 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `cameras`
--

LOCK TABLES `cameras` WRITE;
/*!40000 ALTER TABLE `cameras` DISABLE KEYS */;
INSERT INTO `cameras` VALUES (1,3.5,370,'Canon','2026-05-22 19:19:39.993186','Camera usoara pentru incepatori si creatori de continut.','/images/brands/canon.svg','EOS R50','portret',3799.00,2,24.2,'APS-C','Mirrorless','4K'),(2,4,430,'Canon','2026-05-22 19:19:40.016898','Autofocus rapid si rafala buna pentru actiune.','/images/brands/canon.svg','EOS R10','sport',4999.00,1,24.2,'APS-C','Mirrorless','4K'),(3,4.75,370,'Canon','2026-05-22 19:19:40.034491','Full frame compact, potrivit pentru portrete si evenimente.','/images/brands/canon.svg','EOS R8','portret',7999.00,4,24.2,'Full Frame','Mirrorless','4K'),(4,2.33,580,'Canon','2026-05-22 19:19:40.050600','Model avansat pentru nunti, evenimente si fotografie profesionala.','/images/brands/canon.svg','EOS R6 Mark II','eveniment',12999.00,3,24.2,'Full Frame','Mirrorless','4K'),(6,1.8,235,'Canon','2026-05-22 19:19:40.084206','Camera compacta pentru vlogging si continut online.','/images/brands/canon.svg','PowerShot G7 X III','vlogging',3699.00,5,20.1,'1 inch','Compact','4K'),(7,3,330,'Nikon','2026-05-22 19:19:40.099313','Camera compacta pentru video, vlog si social media.','/images/brands/nikon.svg','Z30','vlogging',3499.00,1,20.9,'APS-C','Mirrorless','4K'),(8,2.33,320,'Nikon','2026-05-22 19:19:40.117978','Model compact pentru fotografie urbana si calatorii.','/images/brands/nikon.svg','Z50','street',4299.00,3,20.9,'APS-C','Mirrorless','4K'),(9,0,300,'Nikon','2026-05-22 19:19:40.134028','Design retro si controale manuale pentru fotografie creativa.','/images/brands/nikon.svg','Z fc','street',4999.00,0,20.9,'APS-C','Mirrorless','4K'),(10,4.5,470,'Nikon','2026-05-22 19:19:40.151506','Full frame accesibil pentru portrete si peisaje.','/images/brands/nikon.svg','Z5','portret',6799.00,2,24.3,'Full Frame','Mirrorless','4K'),(11,4.5,410,'Nikon','2026-05-22 19:19:40.170473','Camera full frame echilibrata pentru evenimente si fotografie generala.','/images/brands/nikon.svg','Z6 II','eveniment',8999.00,4,24.5,'Full Frame','Mirrorless','4K'),(12,1.8,950,'Nikon','2026-05-22 19:19:40.191490','DSLR robust cu autonomie ridicata pentru natura si sport.','/images/brands/nikon.svg','D7500','wildlife',5499.00,5,20.9,'APS-C','DSLR','4K'),(13,4,420,'Sony','2026-05-22 19:19:40.204462','Mirrorless accesibil cu autofocus foarte bun.','/images/brands/sony.svg','A6100','incepator',3699.00,5,24.2,'APS-C','Mirrorless','4K'),(14,0,410,'Sony','2026-05-22 19:19:40.216833','Autofocus rapid si performanta buna pentru actiune.','/images/brands/sony.svg','A6400','sport',4999.00,0,24.2,'APS-C','Mirrorless','4K'),(15,4,440,'Sony','2026-05-22 19:19:40.232887','Camera pentru creatori video cu obiective interschimbabile.','/images/brands/sony.svg','ZV-E10','vlogging',3899.00,4,24.2,'APS-C','Mirrorless','4K'),(16,2,710,'Sony','2026-05-22 19:19:40.250858','Full frame popular pentru foto si video.','/images/brands/sony.svg','A7 III','eveniment',8499.00,1,24.2,'Full Frame','Mirrorless','4K'),(17,5,580,'Sony','2026-05-22 19:19:40.266448','Model performant pentru fotografi avansati si profesionisti.','/images/brands/sony.svg','A7 IV','profesional',11999.00,2,33,'Full Frame','Mirrorless','4K'),(18,1.67,260,'Sony','2026-05-22 19:19:40.283631','Compact premium cu zoom versatil pentru calatorii.','/images/brands/sony.svg','RX100 VII','calatorie',5999.00,3,20.1,'1 inch','Compact','4K'),(19,4.5,380,'Fujifilm','2026-05-22 19:19:40.301647','Camera mica, rapida si potrivita pentru fotografie urbana.','/images/brands/fujifilm.svg','X-T30 II','street',4699.00,2,26.1,'APS-C','Mirrorless','4K'),(20,2,750,'Fujifilm','2026-05-22 19:19:40.318321','Autonomie foarte buna si functii video avansate.','/images/brands/fujifilm.svg','X-S20','video',6999.00,1,26.1,'APS-C','Mirrorless','6.2K'),(21,4.33,580,'Fujifilm','2026-05-22 19:19:40.335128','Rezolutie mare si controale clasice pentru fotografie avansata.','/images/brands/fujifilm.svg','X-T5','peisaj',8999.00,3,40.2,'APS-C','Mirrorless','6.2K'),(22,0,680,'Fujifilm','2026-05-22 19:19:40.351817','Camera orientata spre rezolutie mare si video performant.','/images/brands/fujifilm.svg','X-H2','profesional',9999.00,0,40.2,'APS-C','Mirrorless','8K'),(23,3.5,420,'Fujifilm','2026-05-22 19:19:40.370058','Compact premium cu obiectiv fix, ideal pentru street photography.','/images/brands/fujifilm.svg','X100V','street',7499.00,4,26.1,'APS-C','Compact','4K'),(24,3,455,'Fujifilm','2026-05-22 19:19:40.389635','Format mediu pentru calitate maxima a imaginii.','/images/brands/fujifilm.svg','GFX 50S II','profesional',16999.00,5,51.4,'Medium Format','Mirrorless','Full HD'),(25,1,270,'Panasonic','2026-05-22 19:19:40.408219','Model usor pentru vlog si fotografie casual.','/images/brands/panasonic.svg','Lumix G100','vlogging',2999.00,1,20.3,'Micro Four Thirds','Mirrorless','4K'),(26,3.5,360,'Panasonic','2026-05-22 19:19:40.425009','Camera orientata spre filmare si continut video.','/images/brands/panasonic.svg','Lumix GH6','video',7499.00,2,25.2,'Micro Four Thirds','Mirrorless','5.7K'),(27,3.33,370,'Panasonic','2026-05-22 19:19:40.442225','Full frame hibrid cu stabilizare si autofocus imbunatatit.','/images/brands/panasonic.svg','Lumix S5 II','video',8999.00,3,24.2,'Full Frame','Mirrorless','6K'),(28,4,370,'Panasonic','2026-05-22 19:19:40.459066','Model video avansat pentru creatori si productie.','/images/brands/panasonic.svg','Lumix S5 IIX','profesional',10999.00,4,24.2,'Full Frame','Mirrorless','6K'),(29,4,360,'Olympus','2026-05-22 19:19:40.474585','Camera compacta si stabilizata pentru calatorii.','/images/brands/olympus.svg','OM-D E-M10 IV','calatorie',3299.00,5,20.3,'Micro Four Thirds','Mirrorless','4K'),(30,3.2,310,'Olympus','2026-05-22 19:19:40.490165','Corp rezistent si stabilizare buna pentru utilizare zilnica.','/images/brands/olympus.svg','OM-D E-M5 III','calatorie',5499.00,5,20.4,'Micro Four Thirds','Mirrorless','4K'),(31,0,310,'OM System','2026-05-22 19:19:40.506077','Camera rezistenta la intemperii pentru natura si drumetii.','/images/brands/om-system.svg','OM-5','wildlife',5999.00,0,20.4,'Micro Four Thirds','Mirrorless','4K'),(32,2.2,520,'OM System','2026-05-22 19:19:40.522133','Model rapid pentru wildlife, sport si fotografie outdoor.','/images/brands/om-system.svg','OM-1 Mark II','wildlife',11999.00,5,20.4,'Micro Four Thirds','Mirrorless','4K'),(33,4.6,350,'Leica','2026-05-22 19:19:40.554399','Compact full frame premium cu obiectiv fix luminos.','/images/brands/leica.svg','Q2','street',24999.00,5,47.3,'Full Frame','Compact','4K'),(34,2,410,'Pentax','2026-05-22 19:19:40.569315','DSLR rezistent la vreme pentru fotografie outdoor.','/images/brands/pentax.svg','K-70','peisaj',3999.00,5,24.2,'APS-C','DSLR','Full HD'),(35,4.6,200,'Ricoh','2026-05-22 19:19:40.584515','Compact discret si rapid pentru fotografie stradala.','/images/brands/ricoh.svg','GR III','street',5299.00,5,24.2,'APS-C','Compact','Full HD'),(36,2.2,180,'GoPro','2026-05-22 19:19:40.596953','Camera action pentru sport, calatorii si filmari dinamice.','/images/brands/gopro.svg','HERO12 Black','sport',2499.00,5,27,'1/1.9 inch','Action','5.3K'),(37,4,166,'DJI','2026-05-22 19:19:40.610230','Camera compacta stabilizata pentru vlog si filmari rapide.','/images/brands/dji.svg','Osmo Pocket 3','vlogging',3199.00,5,9.4,'1 inch','Compact','4K'),(41,0,1070,'Canon','2026-05-22 21:18:44.737121','DSLR accesibil cu autonomie foarte buna.','/images/brands/canon.svg','EOS 250D','incepator',2999.00,0,24.1,'APS-C','DSLR','4K');
/*!40000 ALTER TABLE `cameras` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `favorites`
--

DROP TABLE IF EXISTS `favorites`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `favorites` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `created_at` datetime(6) DEFAULT NULL,
  `camera_id` bigint NOT NULL,
  `user_id` bigint NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `UK7rtuf58p6ei0jimfna9mhkggw` (`user_id`,`camera_id`),
  KEY `FKq6e4nrhuwf86gje8cpgawt631` (`camera_id`),
  CONSTRAINT `FKk7du8b8ewipawnnpg76d55fus` FOREIGN KEY (`user_id`) REFERENCES `users` (`id`),
  CONSTRAINT `FKq6e4nrhuwf86gje8cpgawt631` FOREIGN KEY (`camera_id`) REFERENCES `cameras` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=29 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `favorites`
--

LOCK TABLES `favorites` WRITE;
/*!40000 ALTER TABLE `favorites` DISABLE KEYS */;
INSERT INTO `favorites` VALUES (9,'2026-05-23 19:11:02.650540',33,5),(10,'2026-05-23 19:11:02.652573',10,5),(11,'2026-05-23 19:11:02.654793',28,5),(12,'2026-05-23 19:11:02.655817',1,6),(13,'2026-05-23 19:11:02.659506',4,6),(14,'2026-05-23 19:11:02.661539',19,6),(15,'2026-05-23 19:11:02.662543',12,6),(16,'2026-05-23 19:11:02.664833',6,7),(17,'2026-05-23 19:11:02.667440',33,7),(18,'2026-05-23 19:11:02.670499',8,7),(19,'2026-05-23 19:11:02.673532',15,7),(20,'2026-05-23 19:11:02.675556',21,8),(21,'2026-05-23 19:11:02.679104',35,8),(22,'2026-05-23 19:11:02.681437',13,8),(23,'2026-05-23 19:11:02.684621',18,8),(24,'2026-05-23 19:11:02.687182',2,9),(25,'2026-05-23 19:11:02.690564',7,9),(26,'2026-05-23 19:11:02.694848',32,9),(27,'2026-05-23 19:11:02.699310',17,9),(28,'2026-05-23 19:14:26.150423',41,5);
/*!40000 ALTER TABLE `favorites` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `forum_comments`
--

DROP TABLE IF EXISTS `forum_comments`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `forum_comments` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `approved` bit(1) NOT NULL,
  `content` varchar(2000) COLLATE utf8mb4_unicode_ci NOT NULL,
  `created_at` datetime(6) DEFAULT NULL,
  `author_id` bigint NOT NULL,
  `post_id` bigint NOT NULL,
  PRIMARY KEY (`id`),
  KEY `FKaagdun8roxwogrhpfs97vfcyl` (`author_id`),
  KEY `FKeb7i9uh14fy77papa5wfpfds4` (`post_id`),
  CONSTRAINT `FKaagdun8roxwogrhpfs97vfcyl` FOREIGN KEY (`author_id`) REFERENCES `users` (`id`),
  CONSTRAINT `FKeb7i9uh14fy77papa5wfpfds4` FOREIGN KEY (`post_id`) REFERENCES `forum_posts` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=17 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `forum_comments`
--

LOCK TABLES `forum_comments` WRITE;
/*!40000 ALTER TABLE `forum_comments` DISABLE KEYS */;
INSERT INTO `forum_comments` VALUES (3,_binary '','Da, este foarte buna pentru inceput. Meniurile sunt clare si autofocusul ajuta mult la portrete.','2026-05-17 19:11:02.712564',6,4),(4,_binary '','Am pus-o la favorite pentru ca este usoara si pretul este bun pentru un prim aparat.','2026-05-18 19:11:02.713573',9,4),(5,_binary '','Pentru video casual este ok, dar daca vrei vlogging zilnic m-as uita si la Sony ZV-E10.','2026-05-19 19:11:02.714788',7,4),(6,_binary '','Pentru continut video este foarte potrivita. Imi place ca are ecran rabatabil si imagine buna.','2026-05-18 19:11:02.717556',5,5),(7,_binary '','Pentru sport nu este prima alegere, dar pentru vlog si review-uri este o varianta reusita.','2026-05-19 19:11:02.717556',8,5),(8,_binary '','Am salvat-o la favorite pentru calatorii, mai ales daca folosesti un obiectiv compact.','2026-05-20 19:11:02.719028',9,5),(9,_binary '','Pentru o zi de plimbare este ok, dar as lua o baterie de rezerva.','2026-05-19 19:11:02.721548',5,6),(10,_binary '','Ergonomia este mai buna decat la multe modele compacte. Pentru familie si calatorii mi se pare inspirata.','2026-05-20 19:11:02.723965',6,6),(11,_binary '','Pentru video este una dintre cele mai bune variante APS-C din lista. Autonomia este un avantaj mare.','2026-05-20 19:11:02.726154',7,7),(12,_binary '','Pentru outdoor as verifica si rezistenta la vreme, dar specificatiile sunt foarte bune.','2026-05-21 19:11:02.726154',8,7),(13,_binary '','Culorile Fujifilm sunt un plus daca nu vrei sa editezi foarte mult pozele.','2026-05-22 19:11:02.727160',5,7),(14,_binary '','Pentru drumetii conteaza mult greutatea, iar sistemul Micro Four Thirds are obiective mici.','2026-05-21 19:11:02.728179',9,8),(15,_binary '','As alege-o pentru outdoor, mai ales daca vrei stabilizare buna si kit compact.','2026-05-22 19:11:02.729182',6,8),(16,_binary '','Nu este orientata strict spre video, dar pentru calatorii si natura este foarte practica.','2026-05-23 19:11:02.730451',7,8);
/*!40000 ALTER TABLE `forum_comments` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `forum_posts`
--

DROP TABLE IF EXISTS `forum_posts`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `forum_posts` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `approved` bit(1) NOT NULL,
  `content` varchar(3000) COLLATE utf8mb4_unicode_ci NOT NULL,
  `created_at` datetime(6) DEFAULT NULL,
  `title` varchar(160) COLLATE utf8mb4_unicode_ci NOT NULL,
  `author_id` bigint NOT NULL,
  `camera_id` bigint NOT NULL,
  PRIMARY KEY (`id`),
  KEY `FKpsovhjndrj3obmt1d0p9nhr0u` (`author_id`),
  KEY `FKflt1nkybuxwp8r1f8c3ajwi50` (`camera_id`),
  CONSTRAINT `FKflt1nkybuxwp8r1f8c3ajwi50` FOREIGN KEY (`camera_id`) REFERENCES `cameras` (`id`),
  CONSTRAINT `FKpsovhjndrj3obmt1d0p9nhr0u` FOREIGN KEY (`author_id`) REFERENCES `users` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `forum_posts`
--

LOCK TABLES `forum_posts` WRITE;
/*!40000 ALTER TABLE `forum_posts` DISABLE KEYS */;
INSERT INTO `forum_posts` VALUES (4,_binary '','Vreau o camera pentru portrete si fotografii de vacanta. Ma intereseaza daca este usor de folosit si daca obiectivele sunt accesibile.','2026-05-16 19:11:02.709332','Merita Canon EOS R50 pentru inceput?',5,1),(5,_binary '','Caut un model cu obiective interschimbabile, autofocus bun si calitate video peste telefon. Are sens ZV-E10 in buget mediu?','2026-05-17 19:11:02.716049','Sony ZV-E10 pentru vlog si YouTube',7,15),(6,_binary '','Mi se pare un model echilibrat pentru vacante si fotografie stradala. Cum vi se pare autonomia?','2026-05-18 19:11:02.719028','Nikon Z50 pentru calatorii',9,8),(7,_binary '','Ma intereseaza o camera care sa fie buna si pentru poze, si pentru filmari. X-S20 pare foarte echilibrata.','2026-05-19 19:11:02.725103','Fujifilm X-S20 pentru foto si video',6,20),(8,_binary '','Caut ceva rezistent la vreme, usor de carat si potrivit pentru natura. OM-5 pare interesanta pentru excursii.','2026-05-20 19:11:02.728179','OM-5 pentru wildlife si drumetii',8,31);
/*!40000 ALTER TABLE `forum_posts` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `search_history`
--

DROP TABLE IF EXISTS `search_history`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `search_history` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `brand` varchar(80) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `budget` decimal(10,2) DEFAULT NULL,
  `created_at` datetime(6) DEFAULT NULL,
  `min_battery` int DEFAULT NULL,
  `min_resolution` double DEFAULT NULL,
  `photography_type` varchar(80) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `sort_by` varchar(40) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `user_id` bigint NOT NULL,
  PRIMARY KEY (`id`),
  KEY `FK8ll2cxj6i83mnrcyxrxl4b7dm` (`user_id`),
  CONSTRAINT `FK8ll2cxj6i83mnrcyxrxl4b7dm` FOREIGN KEY (`user_id`) REFERENCES `users` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=14 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `search_history`
--

LOCK TABLES `search_history` WRITE;
/*!40000 ALTER TABLE `search_history` DISABLE KEYS */;
INSERT INTO `search_history` VALUES (10,NULL,NULL,'2026-05-22 20:53:34.296643',NULL,NULL,NULL,'score_desc',4),(11,NULL,NULL,'2026-05-22 21:21:47.280521',NULL,NULL,NULL,'score_desc',4),(12,NULL,NULL,'2026-05-23 18:42:11.847108',NULL,NULL,NULL,'score_desc',4),(13,NULL,NULL,'2026-05-23 19:15:45.316945',NULL,NULL,NULL,'score_desc',5);
/*!40000 ALTER TABLE `search_history` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user_cameras`
--

DROP TABLE IF EXISTS `user_cameras`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `user_cameras` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `brand` varchar(80) COLLATE utf8mb4_unicode_ci NOT NULL,
  `model` varchar(120) COLLATE utf8mb4_unicode_ci NOT NULL,
  `notes` varchar(1000) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `resolution_mp` double DEFAULT NULL,
  `type` varchar(80) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `owner_id` bigint NOT NULL,
  `battery_shots` int DEFAULT NULL,
  `image_url` varchar(500) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `photography_type` varchar(80) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `price` decimal(10,2) DEFAULT NULL,
  `sensor` varchar(80) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `video` varchar(80) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `public_camera_id` bigint DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `UKh96g2obbqme1e497lneyjn16b` (`owner_id`),
  UNIQUE KEY `UKrs5ncwobfp6ido21bdlf4qcvu` (`public_camera_id`),
  CONSTRAINT `FK3mq3c3gwsjsnor6a73o2awugd` FOREIGN KEY (`owner_id`) REFERENCES `users` (`id`),
  CONSTRAINT `FKdin3l1uoxll9kths79gb4inb0` FOREIGN KEY (`public_camera_id`) REFERENCES `cameras` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user_cameras`
--

LOCK TABLES `user_cameras` WRITE;
/*!40000 ALTER TABLE `user_cameras` DISABLE KEYS */;
/*!40000 ALTER TABLE `user_cameras` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `users` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `active` bit(1) NOT NULL,
  `bio` varchar(1000) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `city` varchar(120) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `confirmation_token` varchar(120) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `confirmed` bit(1) NOT NULL,
  `created_at` datetime(6) DEFAULT NULL,
  `email` varchar(120) COLLATE utf8mb4_unicode_ci NOT NULL,
  `experience_level` varchar(80) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `password` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL,
  `reset_token` varchar(120) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `role` enum('ADMIN','USER') COLLATE utf8mb4_unicode_ci NOT NULL,
  `username` varchar(80) COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `UK6dotkott2kjsp8vw4d0m25fb7` (`email`),
  UNIQUE KEY `UKr43af9ap4edm43mmtq01oddj6` (`username`)
) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` VALUES (4,_binary '','Administratorul platformei CamMatch.','Constanta',NULL,_binary '','2026-05-22 20:52:05.032761','admin@cammatch.demo','avansat','$2a$10$T8yeu6D8oBFgQaNHMgc4quCVV1Av1ViTvGpMC22Gu.88p/qFWJ.72',NULL,'ADMIN','admin'),(5,_binary '','Cauta o camera usoara pentru portrete si calatorii.','Bucuresti',NULL,_binary '','2026-05-22 20:52:05.156738','ana.popescu@cammatch.demo','incepator','$2a$10$cJKgvA/aazG0L8wcBYIAyu85Qz/VUK4i54YrMb.qkLjjjVukdBLsy',NULL,'USER','ana.popescu'),(6,_binary '','Interesat de camere pentru evenimente si fotografie de familie.','Cluj-Napoca',NULL,_binary '','2026-05-22 20:52:05.249801','mihai.ionescu@cammatch.demo','mediu','$2a$10$YmGFYhR2mjj8TPbG.Av7jecL1.2viqeXZJ0vKnv3a2GnqblaCIV3S',NULL,'USER','mihai.ionescu'),(7,_binary '','Testeaza camere pentru vlogging si continut video.','Iasi',NULL,_binary '','2026-05-22 20:52:05.341221','maria.stan@cammatch.demo','mediu','$2a$10$wLuE58fwiyh7NztTXL3teeYct5lPvq85Sw6pt8Cwl0gJYh.Fcl2Je',NULL,'USER','maria.stan'),(8,_binary '','Pasionat de wildlife, sport si fotografie outdoor.','Brasov',NULL,_binary '','2026-05-22 20:52:05.433733','andrei.dumitru@cammatch.demo','avansat','$2a$10$5TXxitUxPQ/nAIq9088T6OoUdls7gxMCSJU8IsFz89r7uu1Jc9Hae',NULL,'USER','andrei.dumitru'),(9,_binary '','Compara modele compacte pentru calatorii.','Timisoara',NULL,_binary '','2026-05-22 20:52:05.524554','vlad.marin@cammatch.demo','incepator','$2a$10$BKcA3v/iSqn1OGNBmpLJguq1jvPZY1rZK7wYiSRf4eZk3l/hXrxMu',NULL,'USER','vlad.marin');
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2026-05-23 22:20:33


-- ============================================================
-- Verificari rapide dupa import:
-- USE cammatch_final;
-- SELECT COUNT(*) AS nr_camere FROM cameras;
-- SELECT id, username, email, role FROM users;
-- SELECT brand, model, average_rating, rating_count FROM cameras ORDER BY id;
-- ============================================================
