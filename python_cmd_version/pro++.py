from sqlite_utils import sqlite_utils
from pro_entity import pro
from pro_set import pro_set
from cmd_caller import cmd_caller

LOOP_END = -1
LOOPING = 0
sqlite_op = sqlite_utils()
sqlite_op.conn_sqlite()
sqlite_op.create_tables()
loop_flag = LOOPING

while (loop_flag == LOOPING):
    print('Choose your options:0.end\n')
    user_inpt = input("--")
    if user_inpt == 0:
        loop_flag = LOOP_END
    elif user_inpt == 1:
        print("Input today's pro value\nFormat:\n[CST time]_[writing time]_[reading time]_[art learning time]_[note]_(date):\n")
        inpt_today_pro_str = raw_input("--")
        #print(inpt_today_pro_str)
        ret_pro_str_list = inpt_today_pro_str.split('_')
        print(ret_pro_str_list)
        pro_inpt = pro(ret_pro_str_list[1],ret_pro_str_list[3],ret_pro_str_list[2],ret_pro_str_list[0],ret_pro_str_list[4])
        pro_set_order = pro_set(pro_inpt)
        cmd_caller = cmd_caller()
        cmd_caller.take_order(pro_set_order)
        cmd_caller.place_orders()
