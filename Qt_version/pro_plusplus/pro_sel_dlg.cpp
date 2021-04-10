#include "pro_sel_dlg.h"
#include "ui_pro_sel_dlg.h"

pro_sel_dlg::pro_sel_dlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pro_sel_dlg)
{
    ui->setupUi(this);
}

pro_sel_dlg::~pro_sel_dlg()
{
    delete ui;
}
