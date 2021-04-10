#include "statistics_dlg.h"
#include "ui_statistics_dlg.h"

statistics_dlg::statistics_dlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::statistics_dlg)
{
    ui->setupUi(this);
}

statistics_dlg::~statistics_dlg()
{
    delete ui;
}
