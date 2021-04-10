#include "pro_sel_serv.h"


int pro_sel_serv::sel_pro(QString strdate,pro* selpro)
{
    if (!sqlite_utils::get_inst().get_pro(strdate, selpro))
    {
        return -1;
    }
    return 0;
}
