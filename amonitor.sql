-- phpMyAdmin SQL Dump
-- version 4.8.5
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Jun 06, 2020 at 07:51 AM
-- Server version: 10.1.38-MariaDB
-- PHP Version: 7.3.3

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `amonitor`
--

-- --------------------------------------------------------

--
-- Table structure for table `datasensor`
--

CREATE TABLE `datasensor` (
  `id` int(11) UNSIGNED NOT NULL,
  `data` varchar(10) DEFAULT NULL,
  `waktu` timestamp NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `datasensor`
--

INSERT INTO `datasensor` (`id`, `data`, `waktu`) VALUES
(1, '1.03', '2020-05-28 09:59:42'),
(7, '1.33', '2020-05-28 10:01:44'),
(8, '1.49', '2020-05-28 11:01:24'),
(9, '1.86', '2020-05-28 11:05:11'),
(10, '37.84', '2020-05-28 11:32:53'),
(11, '19.29', '2020-05-28 11:34:15'),
(12, '37.63', '2020-05-28 11:50:59'),
(14, '44.13', '2020-05-28 11:55:27'),
(15, '31.22', '2020-05-28 11:56:57'),
(16, '46.09', '2020-05-28 12:05:24'),
(17, '31.44', '2020-05-28 12:06:40'),
(18, '28.38', '2020-05-28 15:51:02'),
(19, '35.21', '2020-05-28 17:00:25'),
(21, '47.41', '2020-05-28 17:03:44'),
(22, '87.00', '2020-05-28 17:13:35'),
(23, '87.13', '2020-05-28 17:14:51'),
(24, '54.05', '2020-05-28 17:28:16'),
(25, '40.16', '2020-05-28 17:29:34'),
(30, '0.11', '2020-05-28 18:28:18'),
(31, '0.10', '2020-05-28 19:24:09'),
(32, '35.21', '2020-05-28 19:48:12'),
(33, '21.39', '2020-05-28 19:53:05'),
(34, '24', '2020-05-28 20:03:55'),
(35, '36', '2020-05-28 20:14:54'),
(36, '36', '2020-05-28 20:15:31'),
(37, '36', '2020-05-28 20:16:55'),
(38, '36', '2020-05-28 20:17:32'),
(39, '28', '2020-05-28 20:22:15'),
(40, '25', '2020-05-28 20:23:15'),
(41, '86', '2020-05-28 20:25:40'),
(42, '84', '2020-05-28 20:26:32'),
(43, '79', '2020-05-28 20:29:53'),
(44, '27.11', '2020-05-28 20:45:55'),
(45, '27.10', '2020-05-28 20:50:49'),
(46, '31.08', '2020-05-28 20:53:51'),
(47, '0.25', '2020-05-28 20:56:49'),
(48, '0.24', '2020-05-28 21:00:00'),
(49, '0.22', '2020-05-28 21:06:07'),
(50, '0.20', '2020-05-28 21:15:32'),
(51, '35.22', '2020-05-28 22:30:42'),
(52, '31.69', '2020-05-28 23:51:16'),
(53, '32.93', '2020-05-28 23:52:48'),
(54, '48.65', '2020-05-28 23:53:31'),
(55, '28.87', '2020-05-28 23:56:48'),
(56, '29.17', '2020-05-28 23:57:25'),
(57, '27.95', '2020-05-28 23:58:11'),
(58, '26.11', '2020-05-29 00:07:58'),
(59, '26.50', '2020-06-02 10:45:39'),
(60, '28.76', '2020-06-02 10:47:24'),
(61, '27.12', '2020-06-02 15:48:31'),
(70, '22.89', '2020-06-02 17:04:53'),
(71, '32.63', '2020-06-05 18:48:16'),
(72, '31.08', '2020-06-05 18:48:50');

-- --------------------------------------------------------

--
-- Table structure for table `dataswiper`
--

CREATE TABLE `dataswiper` (
  `id` int(11) UNSIGNED NOT NULL,
  `data` varchar(10) DEFAULT NULL,
  `data_2` varchar(10) DEFAULT NULL,
  `waktu` timestamp NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `dataswiper`
--

INSERT INTO `dataswiper` (`id`, `data`, `data_2`, `waktu`) VALUES
(8, '24.11', '0', '2020-06-02 18:31:47'),
(15, NULL, '15.83', '2020-06-05 18:50:10'),
(16, '15.83', NULL, '2020-06-05 18:50:21'),
(17, '10', NULL, '2020-06-06 05:42:44'),
(18, NULL, NULL, '2020-06-06 05:50:02'),
(19, NULL, '10', '2020-06-06 05:50:12');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `datasensor`
--
ALTER TABLE `datasensor`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `dataswiper`
--
ALTER TABLE `dataswiper`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `datasensor`
--
ALTER TABLE `datasensor`
  MODIFY `id` int(11) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=73;

--
-- AUTO_INCREMENT for table `dataswiper`
--
ALTER TABLE `dataswiper`
  MODIFY `id` int(11) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=20;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
