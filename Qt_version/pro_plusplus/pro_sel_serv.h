#ifndef PRO_SEL_SERV_H
#define PRO_SEL_SERV_H

#include "pro.h"
#include "sqlite_utils.h"

class pro_sel_serv
{
private:
    pro_sel_serv()
    {

    }

public:
    //获取唯一可用的对象
    static pro_sel_serv& get_inst()
    {
        static pro_sel_serv instance;
        return instance;
    }

    pro_sel_serv(const pro_sel_serv&) = delete;

    pro_sel_serv& operator=(const pro_sel_serv&) = delete;

    int sel_pro(QString strdate,pro* selpro);
};

#endif // PRO_SEL_SERV_H
