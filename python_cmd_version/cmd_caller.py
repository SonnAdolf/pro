#!/usr/bin/python
# -*- coding: UTF-8 -*-
import sys
reload(sys)
sys.setdefaultencoding( "utf-8" )

class cmd_caller():
    __order_list = []
    def take_order(self,in_order):
        self.__order_list.append(in_order)
    def place_orders(self):
        for one_order in self.__order_list:
            one_order.execute()
        self.__order_list = []
