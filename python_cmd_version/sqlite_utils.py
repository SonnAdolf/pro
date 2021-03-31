#!/usr/bin/python
# -*- coding: UTF-8 -*-
import sys

import sqlite3
from pro_entity import pro

reload(sys)
sys.setdefaultencoding( "utf-8" )

class sqlite_utils:
    
    conn = None
    
    def conn_sqlite(self): 
        self.conn = sqlite3.connect('data.db')
        #print "Opend db successfully"
        
    def close_sqlite(self):
        self.conn.close()   
        
    def create_tables(self):
        self.conn = sqlite3.connect('data.db')
        c = self.conn.cursor()
        c.execute('''CREATE TABLE IF NOT EXISTS  pro(id integer  primary key autoincrement,writing_pro integer,reading_pro integer,art_learning_pro integer,computer_science_tech_pro integer,total_pro integer,note varchar(500),date date NOT NULL);''')  
        #print "Table created successfully"
        self.conn.close()   
    
    def add_pro(self,pro,date):
        self.conn = sqlite3.connect('data.db')
        c = self.conn.cursor()
        sql_str="INSERT INTO pro(writing_pro, reading_pro, art_learning_pro, computer_science_tech_pro, total_pro, note, date) VALUES ('"
        sql_str = sql_str + pro.get_writing_pro_str() + "','" + pro.get_reading_pro_str() + "','" + pro.get_art_learning_pro_str() + "','" + pro.get_computer_learning_pro_str() + "','" + pro.get_total_pro_str() + "','" + pro.get_note() + "','" + date+ "');"
        self.conn.execute(sql_str)
        self.conn.commit()
        #print("sql is"+sql_str)
        self.conn.close()   

    def sel_pro_by_date(self,str_date):
        self.conn = sqlite3.connect('data.db')
        c = self.conn.cursor()
        sql_str="select writing_pro,reading_pro,art_learning_pro,computer_science_tech_pro,note from pro where date='"
        sql_str = sql_str + str_date + "';"
        #print('sql:'+sql_str)
        cursor = self.conn.execute(sql_str)
        cursor_list = list(cursor)
        if len(cursor_list)<1:
            return None
        row = cursor_list[0]
        
        row_list = list(row)
        if row[0] == None or row[0] == '':
            row_list.append('0')
        else:
            row_list.append(row[0])
        if row[1] == None or row[1] == '':
            row_list.append('0')
        else:
            row_list.append(row[1])
        if row[2] == None or row[2] == '':
            row_list.append('0')
        else:
            row_list.append(row[2])
        if row[3] == None or row[3] == '':
            row_list.append('0')
        else:
            row_list.append(row[3])
        if row[4] == None or row[4] == '':
            row_list.append('')
        else:
            row_list.append(row[4])
            
        #print(row)
        pro_sel = pro(float(row_list[0]),float(row_list[2]),float(row_list[1]),float(row_list[3]),row_list[4])
        self.conn.close()   
        return pro_sel
        
    def update_pro(self,pro,date):
        self.conn = sqlite3.connect('data.db')
        c = self.conn.cursor()
        sql_str = "update pro set writing_pro='"
        sql_str = sql_str+pro.get_writing_pro_str() +"',reading_pro='"+pro.get_reading_pro_str()+"',art_learning_pro='"+pro.get_art_learning_pro_str()+"',computer_science_tech_pro='"+pro.get_computer_learning_pro_str()+"',total_pro='"+pro.get_total_pro_str()+"',note='"+pro.get_note()+"' where date='"+date+"';"
        self.conn.execute(sql_str)
        self.conn.commit()
        #print("sql is"+sql_str)
        self.conn.close() 
        
    def check_if_pro_of_date_exist(self,date):
        self.conn = sqlite3.connect('data.db')
        c = self.conn.cursor()
        sql_str="select count(*) from pro where date='"+date+"';"
        cursor = self.conn.execute(sql_str)
        cursor_list = list(cursor)
        if len(cursor_list)<1:
            return None
        row = cursor_list[0]
        #print(row)
        self.conn.close()  
        if int(row[0]) > 0:
            return True
        return False    
        
    def get_pro_sum_by_month(self,year,month):
        ret_sum_nums = []
        self.conn = sqlite3.connect('data.db')
        c = self.conn.cursor()
        sql_str = "select sum(writing_pro),sum(reading_pro),sum(art_learning_pro),sum(computer_science_tech_pro),sum(total_pro) from pro where strftime('%Y-%m',date)='";
        if month<10:
            sql_str = sql_str + str(year) + "-0" + str(month) + "';"
        else:
            sql_str = sql_str + str(year) + "-" + str(month) + "';"
        cursor = self.conn.execute(sql_str)
        cursor_list = list(cursor)
        if len(cursor_list)<1:
            return None
        row = cursor_list[0]
        #print(row)
        if row[0] == None or row[0] == '':
            ret_sum_nums.append(0.00)
        else:
            ret_sum_nums.append(float(row[0]))
        if row[1] == None or row[1] == '':
            ret_sum_nums.append(0.00)
        else:
            ret_sum_nums.append(float(row[1]))
        if row[2] == None or row[2] == '':
            ret_sum_nums.append(0.00)
        else:
            ret_sum_nums.append(float(row[2]))
        if row[3] == None or row[3] == '':
            ret_sum_nums.append(0.00)
        else:
            ret_sum_nums.append(float(row[3]))
        if row[4] == None or row[4] == '':
            ret_sum_nums.append(0.00)
        else:
            ret_sum_nums.append(float(row[4]))
        #print(ret_sum_nums)
        self.conn.close()     
        return ret_sum_nums        

    def count_pro_by_month(self,year,month):
        self.conn = sqlite3.connect('data.db')
        c = self.conn.cursor()
        sql_str="select count(*) from pro where strftime('%Y-%m',date)='"
        if month < 10:
            sql_str = sql_str + str(year) +  '-' +  '0' + str(month)+ "';"
        else:
            sql_str = sql_str + str(year) +  '-'  + str(month) +"';"
        cursor = self.conn.execute(sql_str)
        if cursor == None:
            return 0
        cursor_list = list(cursor)
        if len(cursor_list)<1:
            return 0
        row = cursor_list[0]
        #print(row)
        self.conn.close()  
        return float(row[0])
        
    def get_pro_sum_by_year(self,year):
        ret_sum_nums = []
        self.conn = sqlite3.connect('data.db')
        c = self.conn.cursor()
        sql_str = "select sum(writing_pro),sum(reading_pro),sum(art_learning_pro),sum(computer_science_tech_pro),sum(total_pro) from pro where strftime('%Y',date)='"  + str(year) + "';";
        #print('sql:'+sql_str)
        cursor = self.conn.execute(sql_str)
        cursor_list = list(cursor)
        if len(cursor_list)<1:
            return None
        row = cursor_list[0]
        #print(row)
        if row[0] == None or row[0] == '':
            ret_sum_nums.append(0.00)
        else:
            ret_sum_nums.append(float(row[0]))
        if row[1] == None or row[1] == '':
            ret_sum_nums.append(0.00)
        else:
            ret_sum_nums.append(float(row[1]))
        if row[2] == None or row[2] == '':
            ret_sum_nums.append(0.00)
        else:
            ret_sum_nums.append(float(row[2]))
        if row[3] == None or row[3] == '':
            ret_sum_nums.append(0.00)
        else:
            ret_sum_nums.append(float(row[3]))
        if row[4] == None or row[4] == '':
            ret_sum_nums.append(0.00)
        else:
            ret_sum_nums.append(float(row[4]))
        #print(ret_sum_nums)
        self.conn.close()     
        return ret_sum_nums        

    def count_pro_by_year(self,year):
        self.conn = sqlite3.connect('data.db')
        c = self.conn.cursor()
        sql_str="select count(*) from pro where strftime('%Y',date)='" + str(year) + "';"
        cursor = self.conn.execute(sql_str)
        if cursor == None:
            return 0
        cursor_list = list(cursor)
        if len(cursor_list)<1:
            return 0
        row = cursor_list[0]
        #print(row)
        self.conn.close()  
        return float(row[0])
        
    def get_pro_sum(self):
        ret_sum_nums = []
        self.conn = sqlite3.connect('data.db')
        c = self.conn.cursor()
        sql_str = "select sum(writing_pro),sum(reading_pro),sum(art_learning_pro),sum(computer_science_tech_pro),sum(total_pro) from pro;";
        #print('sql:'+sql_str)
        cursor = self.conn.execute(sql_str)
        cursor_list = list(cursor)
        if len(cursor_list)<1:
            return None
        row = cursor_list[0]
        #print(row)
        if row[0] == None or row[0] == '':
            ret_sum_nums.append(0.00)
        else:
            ret_sum_nums.append(float(row[0]))
        if row[1] == None or row[1] == '':
            ret_sum_nums.append(0.00)
        else:
            ret_sum_nums.append(float(row[1]))
        if row[2] == None or row[2] == '':
            ret_sum_nums.append(0.00)
        else:
            ret_sum_nums.append(float(row[2]))
        if row[3] == None or row[3] == '':
            ret_sum_nums.append(0.00)
        else:
            ret_sum_nums.append(float(row[3]))
        if row[4] == None or row[4] == '':
            ret_sum_nums.append(0.00)
        else:
            ret_sum_nums.append(float(row[4]))
        #print(ret_sum_nums)
        self.conn.close()     
        return ret_sum_nums        

    def count_pro(self):
        self.conn = sqlite3.connect('data.db')
        c = self.conn.cursor()
        sql_str="select count(*) from pro;"
        cursor = self.conn.execute(sql_str)
        if cursor == None:
            return 0
        cursor_list = list(cursor)
        if len(cursor_list)<1:
            return 0
        row = cursor_list[0]
        #print(row)
        self.conn.close()  
        return float(row[0])
        