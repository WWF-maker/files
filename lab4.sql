SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for goods
-- ----------------------------
CREATE TABLE `goods` (
  `id` int unsigned NOT NULL,
  `name` varchar(32) COLLATE utf8mb4_general_ci DEFAULT NULL,
  `brand_id` varchar(32) COLLATE utf8mb4_general_ci DEFAULT NULL,
  `category_id` varchar(32) COLLATE utf8mb4_general_ci DEFAULT NULL,
  `freight_id` varchar(32) COLLATE utf8mb4_general_ci DEFAULT NULL,
  `shop_id` varchar(32) COLLATE utf8mb4_general_ci DEFAULT NULL,
  `goods_sn` varchar(32) COLLATE utf8mb4_general_ci DEFAULT NULL,
  `detail` varchar(32) COLLATE utf8mb4_general_ci DEFAULT NULL,
  `image_url` varchar(32) COLLATE utf8mb4_general_ci DEFAULT NULL,
  `diabled` tinyint(1) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

insert into `goods`(`id`,`name`,`brand_id`,`category_id`,`freight_id`,`shop_id`,`goods_sn`,`detail`,`image_url`,`diabled`) values
('1','手机','1','1','1','1','1','1','1',0),
('2','电脑','2','2','2','2','2','2','2',0);

-- ----------------------------
-- Table structure for product
-- ----------------------------
CREATE TABLE `product` (
  `id` varchar(32) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL,
  `goods_id` varchar(32) COLLATE utf8mb4_general_ci DEFAULT NULL,
  `product_sn` varchar(32) COLLATE utf8mb4_general_ci DEFAULT NULL,
  `name` varchar(32) COLLATE utf8mb4_general_ci DEFAULT NULL,
  `original_price` double unsigned DEFAULT NULL,
  `weight` double unsigned DEFAULT NULL,
  `image_url` varchar(32) COLLATE utf8mb4_general_ci DEFAULT NULL,
  `state` varchar(32) COLLATE utf8mb4_general_ci DEFAULT NULL,
  `detail` varchar(32) COLLATE utf8mb4_general_ci DEFAULT NULL,
  `disabled` tinyint(1) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

insert into `product`(`id`,`goods_id`,`product_sn`,`name`,`original_price`,`weight`,`image_url`,`state`,`detail`,`disabled`) values
('1','1','1','苹果手机','1000.0','1.0','1','1','1',0),
('10','2','10','华为','21312.0','1.0','1','1','1',0),
('11','2','11','联想','124576.0','1.0','1','1','1',0),
('2','1','2','OnePlus','1455.0','1.0','1','1','1',0),
('3','1','3','华为','2324.0','2.0','1','1','1',0),
('4','1','4','小米','2132.0','1.5','1','1','1',0),
('5','1','5','荣耀','2133.0','1.0','1','1','1',0),
('6','1','6','微软','1232.0','1.0','1','1','1',0),
('7','2','7','外星人','23124.0','1.0','1','1','1',0),
('8','2','8','戴尔','214125.0','1.0','1','1','1',0),
('9','2','9','苹果','12312.0','1.0','1','1','1',0);

SET FOREIGN_KEY_CHECKS = 1;
