#ifndef STATISTICS_SERV_H
#define STATISTICS_SERV_H

#include <QDate>
#include "sqlite_utils.h"

class statistics_serv
{
private:
    statistics_serv()
    {

    }

public:
    //获取唯一可用的对象
    static statistics_serv& get_inst()
    {
        static statistics_serv instance;
        return instance;
    }

    statistics_serv(const statistics_serv&) = delete;

    statistics_serv& operator=(const statistics_serv&) = delete;

    QString get_statistics_inf();
};

#endif // STATISTICS_SERV_H
