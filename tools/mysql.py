#!/usr/bin/env python3
# -*- coding=utf-8 -*-
import time
import pymysql
import datetime

class Mysql:
    def __init__(self, ip, port, db, user, passwd):
        self.__ip = ip
        self.__port = port
        self.__db = db
        self.__user = user
        self.__passwd = passwd
        self.__conn = None
        self.__time = []

    def connect(self):
        self.__conn = pymysql.connect(self.__ip, self.__user, self.__passwd, self.__db)
        if None is self.__conn:
            print ('连接数据库失败')
            return False
        return True

    def close(self):
        self.__conn.close()


if __name__ == '__main__':
    mysql = Mysql ('172.30.50.200', 'root', 'dingjing123', 'spider_online')
    print (mysql.connect())
    print ("ok")
