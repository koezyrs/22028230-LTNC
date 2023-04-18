-- phpMyAdmin SQL Dump
-- version 5.1.1
-- https://www.phpmyadmin.net/
--
-- Máy chủ: 127.0.0.1
-- Thời gian đã tạo: Th4 18, 2023 lúc 02:03 PM
-- Phiên bản máy phục vụ: 10.4.22-MariaDB
-- Phiên bản PHP: 7.4.27

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Cơ sở dữ liệu: `test`
--

-- --------------------------------------------------------

--
-- Cấu trúc bảng cho bảng `accounts`
--

CREATE TABLE `accounts` (
  `id` int(11) NOT NULL,
  `username` varchar(20) NOT NULL,
  `password` varchar(32) NOT NULL,
  `email` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Đang đổ dữ liệu cho bảng `accounts`
--

INSERT INTO `accounts` (`id`, `username`, `password`, `email`) VALUES
(1, 'Hecklol', '675844', 'duong1@gmail.com'),
(2, 'duongprovip', '675844', 'duong1@gmail.com'),
(3, 'koezyrs', 'X+mdP?10Za', 'safsdjh@gmail.com');

-- --------------------------------------------------------

--
-- Cấu trúc bảng cho bảng `actors`
--

CREATE TABLE `actors` (
  `id` int(11) NOT NULL,
  `account_id` int(11) NOT NULL,
  `character_name` varchar(20) NOT NULL,
  `level` int(11) NOT NULL,
  `experience` int(11) NOT NULL,
  `experience_to_next_level` int(11) NOT NULL,
  `strength` int(11) NOT NULL,
  `dexterity` int(11) NOT NULL,
  `intelligence` int(11) NOT NULL,
  `vitality` int(11) NOT NULL,
  `agility` int(11) NOT NULL,
  `stats_used` int(11) NOT NULL,
  `stats_available` int(11) NOT NULL,
  `map_id` int(11) NOT NULL,
  `x` int(11) NOT NULL,
  `y` int(11) NOT NULL,
  `gold` int(11) NOT NULL,
  `skin` varchar(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Đang đổ dữ liệu cho bảng `actors`
--

INSERT INTO `actors` (`id`, `account_id`, `character_name`, `level`, `experience`, `experience_to_next_level`, `strength`, `dexterity`, `intelligence`, `vitality`, `agility`, `stats_used`, `stats_available`, `map_id`, `x`, `y`, `gold`, `skin`) VALUES
(1, 3, 'abc', 1, 0, 100, 5, 4, 10, 20, 0, 0, 0, 1, 14, 14, 0, 'Sprite-Player');

-- --------------------------------------------------------

--
-- Cấu trúc bảng cho bảng `actor_character_information`
--

CREATE TABLE `actor_character_information` (
  `id` int(11) NOT NULL,
  `actor_id` int(11) NOT NULL,
  `slot_id` int(11) NOT NULL,
  `equipment_id` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Đang đổ dữ liệu cho bảng `actor_character_information`
--

INSERT INTO `actor_character_information` (`id`, `actor_id`, `slot_id`, `equipment_id`) VALUES
(1, 3, 0, 0);

-- --------------------------------------------------------

--
-- Cấu trúc bảng cho bảng `actor_inventory`
--

CREATE TABLE `actor_inventory` (
  `id` int(11) NOT NULL,
  `actor_id` int(11) NOT NULL,
  `slot_id` int(11) NOT NULL,
  `equipment_id` int(11) NOT NULL,
  `item_id` int(11) NOT NULL,
  `item_amount` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Đang đổ dữ liệu cho bảng `actor_inventory`
--

INSERT INTO `actor_inventory` (`id`, `actor_id`, `slot_id`, `equipment_id`, `item_id`, `item_amount`) VALUES
(1, 3, 0, 1, 0, 0),
(2, 3, 1, 0, 1, 20);

--
-- Chỉ mục cho các bảng đã đổ
--

--
-- Chỉ mục cho bảng `accounts`
--
ALTER TABLE `accounts`
  ADD PRIMARY KEY (`id`);

--
-- Chỉ mục cho bảng `actors`
--
ALTER TABLE `actors`
  ADD PRIMARY KEY (`id`);

--
-- Chỉ mục cho bảng `actor_character_information`
--
ALTER TABLE `actor_character_information`
  ADD PRIMARY KEY (`id`);

--
-- Chỉ mục cho bảng `actor_inventory`
--
ALTER TABLE `actor_inventory`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT cho các bảng đã đổ
--

--
-- AUTO_INCREMENT cho bảng `accounts`
--
ALTER TABLE `accounts`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT cho bảng `actors`
--
ALTER TABLE `actors`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT cho bảng `actor_character_information`
--
ALTER TABLE `actor_character_information`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT cho bảng `actor_inventory`
--
ALTER TABLE `actor_inventory`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
