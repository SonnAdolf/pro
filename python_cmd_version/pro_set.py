import time
from order import order
from sqlite_utils import sqlite_utils
from pro_entity import pro
class pro_set(order):
    #__pro = None

    def __init__(self,pro):
        self.__pro = pro        

    def execute(self):
        self.__add_pro()

    def __add_pro(self):
        date = time.strftime('%Y-%m-%d')  
        print date
        db_utils = sqlite_utils()
        db_utils.add_pro(self.__pro,date)

    def __update_pro(self):
        print "update"
