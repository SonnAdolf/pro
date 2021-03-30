#!/usr/bin/python
# -*- coding: UTF-8 -*-
import sys
import time
from order import order
from sqlite_utils import sqlite_utils
from pro_entity import pro

reload(sys)
sys.setdefaultencoding( "utf-8" )

class pro_set(order):
    __pro = None
    __date = ''

    def __init__(self,pro,date):
        self.__pro = pro 
        self.__date = date

    def execute(self):
        self.__set_pro()
        
    def __set_pro(self):
        if self.__date == None or self.__date == '':
            self.__date = time.strftime('%Y-%m-%d')
            self.__add_pro()
            return
        db_utils = sqlite_utils()
        if db_utils.check_if_pro_of_date_exist(self.__date) == True:
            self.__update_pro()
        else:
            self.__add_pro()
        return

    def __add_pro(self):
        #print date
        db_utils = sqlite_utils()
        db_utils.add_pro(self.__pro,self.__date)

    def __update_pro(self):
        db_utils = sqlite_utils()
        db_utils.update_pro(self.__pro,self.__date)
