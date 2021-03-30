#!/usr/bin/python
# -*- coding: UTF-8 -*-
import sys
import time
from order import order
from sqlite_utils import sqlite_utils
from pro_entity import pro

reload(sys)
sys.setdefaultencoding( "utf-8" )

class pro_search(order):
    __date = ''

    def __init__(self,date):
        self.__date = date        

    def execute(self):
        self.__search()

    def __search(self):
        db_utils = sqlite_utils()
        sel_pro = db_utils.sel_pro_by_date(self.__date)
        if sel_pro != None:
            sel_pro.print_self()
        else:
            print("got nothing")
