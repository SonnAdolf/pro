#ifndef SQLITE_UTILS_H
#define SQLITE_UTILS_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include "pro.h"
#include"iostream"

class sqlite_utils
{
private:
    sqlite_utils() {}

public:
    //获取唯一可用的对象
    static sqlite_utils& get_inst() {
        static sqlite_utils instance;
        return instance;
    }

    sqlite_utils(const sqlite_utils&) = delete;

    sqlite_utils& operator=(const sqlite_utils&) = delete;

    /*
    *  author: 无名
    *  date  :
    *  note  : close sqlite connection
    */
    void sqlite_close();


    /*
    *  author: 无名
    *  date  :
    *  note  : connect to sqlite
    */
    int sqlite_conn();


    /*
    *  author: 无名
    *  date  :
    *  note  : create tables if not exists
    */
    bool create_tables();

    bool add_pro(pro pro, QString date);


    bool get_pro_sum_by_month(float* const writing_pro_sum, float* const reading_pro_sum,
        float* const art_learning_pro_sum, float* const computer_learning_pro, float* const total_pro_sum, const int year, const int month);


    bool get_pro_sum_by_year(float* const writing_pro_sum, float* const reading_pro_sum,
        float* const art_learning_pro_sum, float* const computer_learning_pro, float* const total_pro_sum, const int year);


    bool check_if_pro_of_date_exist(QString date);


    bool update_pro(pro pro, QString date);


    bool get_pro(QString date, pro* selpro);


    bool get_pro_sum(float* const writing_pro_sum, float* const reading_pro_sum,
        float* const art_learning_pro_sum, float* const computer_learning_pro, float* const total_pro_sum);

    bool count_pro_by_month(int* const num, const int year, const int month);

    bool count_pro_by_year(int* const num, const int year);

    bool count_pro(int* const num);
private:
     QSqlDatabase database;
};

#endif // SQLITE_UTILS_H
