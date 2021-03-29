import sqlite3
from pro_entity import pro

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
        print("sql is"+sql_str)
        self.conn.close()   
