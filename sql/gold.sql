-- 抓取黄金报价的表格

-- 取北京时间每天下午6点-7点的交易信息
-- 抓取网址1: https://m.cn.investing.com/commodities/gold-historical-data

-- CREATE DATABASE spider;
-- flush privileges;
alter database `spider` default character set utf8;
use `spider`;

-- 线上数据库
# alter database `spider_online` default character set utf8;
# use `spider_online`;

-- 黄金相关字段: 日期、开盘价格、收盘价格、最高、最低、涨跌幅、区域(中国、美国)
CREATE TABLE IF NOT EXISTS `sp_gold` (
    `id` VARCHAR(320) NOT NULL              COMMENT '主键，时间-信息(gold)-区域()',
    `gold-1` float DEFAULT 0 NOT NULL       COMMENT '黄金开盘价格',
    `gold-2` float DEFAULT 0 NOT NULL       COMMENT '黄金收盘价格',
    `gold-h` float DEFAULT 0 NOT NULL       COMMENT '黄金最高价格',
    `gold-l` float DEFAULT 0 NOT NULL       COMMENT '黄金最低价格',
    `gold-v` float DEFAULT 0 NOT NULL       COMMENT '黄金涨跌幅度',
    `gold-a` INT(3) DEFAULT 0 NOT NULL      COMMENT '黄金区域:0标准, 1上海交易所, 2美国交易所',
    `gold-t` INT(9) DEFAULT 0 NOT NULL      COMMENT '抓取时间戳',
    PRIMARY KEY(`id`)
);

-- 删除旧列
-- alter table `sp_gold` drop column `v1`;

-- 增加新的列
-- alter table `sp_gold` add column `v1` INT(12) default 0;