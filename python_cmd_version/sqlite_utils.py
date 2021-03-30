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
        print "Opend db successfully"
        
    def close_sqlite(self):
        self.conn.close()   
        
    def create_tables(self):
        self.conn = sqlite3.connect('data.db')
        c = self.conn.cursor()
        c.execute('''CREATE TABLE IF NOT EXISTS  pro(id integer  primary key autoincrement,writing_pro integer,reading_pro integer,art_learning_pro integer,computer_science_tech_pro integer,total_pro integer,note varchar(500),date date NOT NULL);''')  
        print "Table created successfully"
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
        #print(row)
        pro_sel = pro(float(row[0]),float(row[2]),float(row[1]),float(row[3]),row[4].encode('utf-8'))
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
        
