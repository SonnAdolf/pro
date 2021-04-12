#include "statistics_dlg.h"
#include "ui_statistics_dlg.h"

statistics_dlg::statistics_dlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::statistics_dlg)
{
    ui->setupUi(this);
    QString txt = statistics_serv::get_inst().get_statistics_inf();
    ui->statistics_text->setText(txt);
}

statistics_dlg::~statistics_dlg()
{
    delete ui;
}

void statistics_dlg::on_restatistics_btn_clicked()
{
    QString txt = statistics_serv::get_inst().get_statistics_inf();
    ui->statistics_text->setText(txt);
}
