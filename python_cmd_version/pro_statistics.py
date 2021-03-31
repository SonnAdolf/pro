#!/usr/bin/python
# -*- coding: UTF-8 -*-
import sys
import time
from order import order
from sqlite_utils import sqlite_utils
from pro_entity import pro

reload(sys)
sys.setdefaultencoding( "utf-8" )

class pro_statistics(order):
    #def __init__(self):      
    def execute(self):
        self.__statistics()
        
    def __get_english_month_word(self, imonth):
        if imonth == 1:
            return 'January'
        elif imonth == 2:
            return 'February'
        elif imonth == 3:
            return 'March'
        elif imonth == 4:
            return 'April'
        elif imonth == 5:
            return 'May'
        elif imonth == 6:
            return 'June' 
        elif imonth == 7:
            return 'July'
        elif imonth == 8:
            return 'August'
        elif imonth == 9:
            return 'September'
        elif imonth == 10:
            return 'October'
        elif imonth == 11:
            return 'November'
        elif imonth == 12:    
            return 'December'  
        else:
            return ''

    def __statistics(self):
        str_statistics_info = ''
        db_utils = sqlite_utils()
        date_now = time.strftime('%Y-%m-%d')
        date_inf_list = date_now.split("-")
        
        year_now = int(date_inf_list[0])
        month_now = int(date_inf_list[1])
        
        average_t_pro = 0.00
        average_w_pro = 0.00
        average_a_pro = 0.00
        average_c_pro = 0.00
        average_r_pro = 0.00
        
        month_num=0
        for i_year in range(2019,year_now+1):
            month_num = 12
            #print("i_year:"+str(i_year)+"\n")
            if i_year == year_now:
                month_num = month_now
            #print("month_num:"+str(month_num)+"\n")
            j_month = 1
            if i_year == 2019:
                j_month = 12
            for j_month in range(j_month,month_num+1):
                #print("j_month:"+str(j_month)+"\n")
                pro_month_sum = []
                pro_month_sum = db_utils.get_pro_sum_by_month(i_year,j_month)
                #print(pro_month_sum)
                #print('\n')
                str_statistics_info = str_statistics_info + self.__get_english_month_word(j_month) + ':\n writing time:'  + str(pro_month_sum[0])+ ' reading time:'
                str_statistics_info = str_statistics_info + str(pro_month_sum[1])+ ' art learning time:' + str(pro_month_sum[2]) + ' cst:' + str(pro_month_sum[3]) + ' total time:'+str(pro_month_sum[4])
                month_day_total = db_utils.count_pro_by_month(i_year,j_month)
                average_t_pro = pro_month_sum[4] / month_day_total
                average_w_pro = pro_month_sum[0] / month_day_total
                average_a_pro = pro_month_sum[2] / month_day_total
                average_c_pro = pro_month_sum[3] / month_day_total
                average_r_pro = pro_month_sum[1] / month_day_total
                str_statistics_info = str_statistics_info + '\navg(W-R-A-C-T):'+str(average_w_pro)+'-'+str(average_r_pro)+'-'+str(average_a_pro)+'-'+str(average_c_pro)+'-'+str(average_t_pro)+'\n\n'
                #print(str_statistics_info)
            str_statistics_info = str_statistics_info +'\n'
            pro_year_sum = []
            pro_year_sum = db_utils.get_pro_sum_by_year(i_year)
            str_statistics_info = str_statistics_info + str(i_year) + ':\n writing time:'  + str(pro_year_sum[0])+ ' reading time:'
            str_statistics_info = str_statistics_info + str(pro_year_sum[1])+ ' art learning time:' + str(pro_year_sum[2]) + ' cst:' + str(pro_year_sum[3]) + ' total time:'+str(pro_year_sum[4])
            year_day_total = db_utils.count_pro_by_year(i_year)
            average_t_pro = pro_year_sum[4] / year_day_total;
            average_w_pro = pro_year_sum[0] / year_day_total;
            average_a_pro = pro_year_sum[2] / year_day_total;
            average_c_pro = pro_year_sum[3] / year_day_total;
            average_r_pro = pro_year_sum[1] / year_day_total;
            str_statistics_info = str_statistics_info + '\navg(W-R-A-C-T):'+str(average_w_pro)+'-'+str(average_r_pro)+'-'+str(average_a_pro)+'-'+str(average_c_pro)+'-'+str(average_t_pro)+'\n'
            #print(str_statistics_info)
            str_statistics_info = str_statistics_info + '\n\n'
        str_statistics_info = str_statistics_info + '\nTotal:\n'
        pro_total_sum = []
        pro_total_sum = db_utils.get_pro_sum()
        str_statistics_info = str_statistics_info + 'writing time:'  + str(pro_total_sum[0])+ ' reading time:'
        str_statistics_info = str_statistics_info + str(pro_total_sum[1])+ ' art learning time:' + str(pro_total_sum[2]) + ' cst:' + str(pro_total_sum[3]) + ' total time:'+str(pro_total_sum[4])
        day_total = db_utils.count_pro()
        average_t_pro = pro_total_sum[4] / day_total;
        average_w_pro = pro_total_sum[0] / day_total;
        average_a_pro = pro_total_sum[2] / day_total;
        average_c_pro = pro_total_sum[3] / day_total;
        average_r_pro = pro_total_sum[1] / day_total;
        str_statistics_info = str_statistics_info + '\navg(W-R-A-C-T):'+str(average_w_pro)+'-'+str(average_r_pro)+'-'+str(average_a_pro)+'-'+str(average_c_pro)+'-'+str(average_t_pro)+'\n'
        str_statistics_info = str_statistics_info + '\n\n'
        
        print(str_statistics_info)
        
