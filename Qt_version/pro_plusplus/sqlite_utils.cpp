#include "sqlite_utils.h"


int sqlite_utils::sqlite_conn()
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("data.db");
    if (!database.open())
    {
        return -1;
    }
    return 0;
}

void sqlite_utils::sqlite_close()
{
    database.close();
}

bool sqlite_utils::create_tables()
{
    QString str_sql = "create table if not exists  pro(id integer  primary key autoincrement,writing_pro integer,reading_pro integer,art_learning_pro integer,computer_science_tech_pro integer,total_pro integer,note varchar(500),date date NOT NULL); ";
    QSqlQuery sql_query;
    sql_query.prepare(str_sql);
    qDebug() << str_sql;
    if(!sql_query.exec(str_sql))
    {
        return false;
    }
    return true;
}

bool sqlite_utils::add_pro(pro pro, QString date)
{
    QString sql = "INSERT INTO pro(writing_pro, reading_pro, art_learning_pro, computer_science_tech_pro, total_pro, note, date) VALUES ('";
    sql.append(pro.get_writing_pro_str()).append("','").append(pro.get_reading_pro_str()).append("','").append(pro.get_art_learning_pro_str());
    sql.append("','").append(pro.get_computer_learning_pro_str()).append("','").append(pro.get_total_pro_str()).append("','");
    sql.append(pro.get_note()).append("','").append(date).append("');");
    qDebug() << sql;
    QSqlQuery sql_query;
    sql_query.prepare(sql);
    if(!sql_query.exec())
    {
        return false;
    }
    return true;
}

bool sqlite_utils::check_if_pro_of_date_exist(QString date)
{
    QString sql = "select count(*) from pro where date='";
    sql.append(date);
    sql.append("';");
    qDebug() << sql;
    QSqlQuery sql_query;
    sql_query.prepare(sql);
    if(!sql_query.exec())
    {
        return false;
    }
    if(sql_query.next())
     {
         int num = sql_query.value(0).toInt();
         qDebug()<<QString("num:%1").arg(num);
         if (num > 0)
         {
             return true;
         }
     }
    return false;
}


bool sqlite_utils::update_pro(pro pro, QString date)
{
    QString sql = "update pro set writing_pro='";
    sql.append(pro.get_writing_pro_str()).append("',reading_pro='").append(pro.get_reading_pro_str()).append("',art_learning_pro='")
        .append(pro.get_art_learning_pro_str()).append("',computer_science_tech_pro='")
        .append(pro.get_computer_learning_pro_str()).append("',total_pro='").append(pro.get_total_pro_str()).append("',note='")
        .append(pro.get_note()).append("' where date='");
    sql.append(date);
    sql.append("';");

    qDebug() << sql;
    QSqlQuery sql_query;
    sql_query.prepare(sql);
    if(!sql_query.exec())
    {
        return false;
    }
    return true;
}


bool sqlite_utils::get_pro(QString date, pro* pro)
{
    return true;
}
