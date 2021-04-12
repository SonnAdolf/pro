#ifndef PRO_DAYSET_DLG_H
#define PRO_DAYSET_DLG_H

#include <QString>
#include <QDialog>
#include <QDate>

#include "pro_dayset_serv.h"

namespace Ui {
class pro_dayset_dlg;
}

class pro_dayset_dlg : public QDialog
{
    Q_OBJECT

public:
    explicit pro_dayset_dlg(QWidget *parent = 0);
    ~pro_dayset_dlg();

private slots:
    void on_inpt_btn_clicked();

private:
    Ui::pro_dayset_dlg *ui;
};

#endif // PRO_DAYSET_DLG_H
