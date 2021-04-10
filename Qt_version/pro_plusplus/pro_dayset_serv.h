#ifndef PRO_DAYSET_SERV_H
#define PRO_DAYSET_SERV_H

#include <QDateTime>
#include "pro.h"
#include "sqlite_utils.h"


class pro_dayset_serv
{
private:
    pro_dayset_serv()
    {

    }

public:
    //获取唯一可用的对象
    static pro_dayset_serv& get_inst()
    {
        static pro_dayset_serv instance;
        return instance;
    }

    pro_dayset_serv(const pro_dayset_serv&) = delete;

    pro_dayset_serv& operator=(const pro_dayset_serv&) = delete;

    int add_pro(pro tmp_pro,QString strdate);

    int update_pro(pro tmp_pro,QString strdate);

    int day_set_pro(pro tmp_pro,QString strdate);
};

#endif // PRO_DAYSET_SERV_H
