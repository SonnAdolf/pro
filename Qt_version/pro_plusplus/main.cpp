#include "main_window.h"
#include "sqlite_utils.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    int ret = 0;
    if (sqlite_utils::get_inst().sqlite_conn()<0) {
        return -1;
    }
    if (!sqlite_utils::get_inst().create_tables()) {
        return -1;
    }
    QApplication a(argc, argv);
    main_window w;
    w.show();
    ret = a.exec();
    sqlite_utils::get_inst().sqlite_close();
    return ret;
}
