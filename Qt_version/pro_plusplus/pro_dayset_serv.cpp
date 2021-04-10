#include "pro_dayset_serv.h"

int pro_dayset_serv::add_pro(pro tmp_pro,QString strdate)
{
    if (strdate == NULL || strdate.compare("")==0)
    {
        return -1;
    }

    QDateTime date = QDateTime::fromString(strdate,"yyyy-MM-dd");
    bool res = date.isValid();
    if(!res)
    {
        qDebug()<<"date format is wrong:"<<date;
        return -1;
    }

    if (!sqlite_utils::get_inst().add_pro(tmp_pro,strdate))
    {
        return -1;
    }

    return 0;
}


int pro_dayset_serv::update_pro(pro tmp_pro,QString strdate)
{
    if (strdate == NULL || strdate.compare("")==0)
    {
        return -1;
    }

    QDateTime date = QDateTime::fromString(strdate,"yyyy-MM-dd");
    bool res = date.isValid();
    if(!res)
    {
        qDebug()<<"date format is wrong:"<<date;
        return -1;
    }

    if (!sqlite_utils::get_inst().update_pro(tmp_pro,strdate))
    {
        return -1;
    }

    return 0;
}


int pro_dayset_serv::day_set_pro(pro tmp_pro,QString strdate)
{
    if (!sqlite_utils::get_inst().check_if_pro_of_date_exist(strdate))
    {
        if(this->add_pro(tmp_pro,strdate)<0)
        {
            return -1;
        }
    }
    else
    {
        if(this->update_pro(tmp_pro,strdate)<0)
        {
            return -1;
        }
    }
    return 0;
}
