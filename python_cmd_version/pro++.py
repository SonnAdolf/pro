#!/usr/bin/python
# -*- coding: UTF-8 -*-
import sys
from sqlite_utils import sqlite_utils
from pro_entity import pro
from pro_set import pro_set
from pro_search import pro_search
from cmd_caller import cmd_caller
from pro_statistics import pro_statistics

reload(sys)
sys.setdefaultencoding( "utf-8" )

LOOP_END = -1
LOOPING = 0
sqlite_op = sqlite_utils()
sqlite_op.conn_sqlite()
sqlite_op.create_tables()
loop_flag = LOOPING
cmd_caller = cmd_caller()
while (loop_flag == LOOPING):
    print('Choose your options:\n0.end\n1.add or update a pro\n2.search a pro\n3.statistics\n')
    user_inpt = raw_input("--")
    if user_inpt!='0' and user_inpt!='1' and user_inpt!='2' and user_inpt!='3':
        continue
    elif user_inpt == '0':
        print("Bye bye~\n")
        loop_flag = LOOP_END
    elif user_inpt == '1':
        print("Input today's pro value\nFormat:\n[CST time]_[writing time]_[reading time]_[art learning time]_[note]_(date):\n")
        inpt_today_pro_str = raw_input("--")
        ret_pro_str_list = inpt_today_pro_str.split('_')
        date_inpt = ''
        if len(ret_pro_str_list)<5 or len(ret_pro_str_list)>6:
            print ('Input information wrong')
        elif len(ret_pro_str_list)==6:
            date_inpt = ret_pro_str_list[5]
        else:
            date_inpt = ''
        #print(ret_pro_str_list)
        pro_inpt = pro(float(ret_pro_str_list[1]),float(ret_pro_str_list[3]),float(ret_pro_str_list[2]),float(ret_pro_str_list[0]),ret_pro_str_list[4])
        pro_inpt.print_self()
        print(pro_inpt.get_total_pro_str())
        pro_set_order = pro_set(pro_inpt,date_inpt)
        cmd_caller.take_order(pro_set_order)
        cmd_caller.place_orders()
    elif user_inpt == '2':
        print("Input which date to search:\n")
        inpt_date_str = raw_input("--")
        pro_search_order = pro_search(inpt_date_str)
        cmd_caller.take_order(pro_search_order)
        cmd_caller.place_orders()        
    elif user_inpt == '3':
        print("Statistics:\n")
        pro_statistics_order = pro_statistics()
        cmd_caller.take_order(pro_statistics_order)
        cmd_caller.place_orders()    
        
