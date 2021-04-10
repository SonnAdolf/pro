#include "pro_dayset_dlg.h"
#include "ui_pro_dayset_dlg.h"

pro_dayset_dlg::pro_dayset_dlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pro_dayset_dlg)
{
    ui->setupUi(this);
    ui->date_edit->setDisplayFormat("yyyy-MM-dd");
}

pro_dayset_dlg::~pro_dayset_dlg()
{
    delete ui;
}

void pro_dayset_dlg::on_inpt_btn_clicked()
{
    QString write_pro_str = ui->wpro_edit->text();
    QString read_pro_str = ui->rpro_edit->text();
    QString art_pro_str = ui->alpro_edit->text();
    QString ctl_pro_str = ui->ctlpro_edit->text();
    QString note_str = ui->note_edit->toPlainText();
    QString date_str = ui->date_edit->text();
    pro tmp_pro(write_pro_str,art_pro_str,read_pro_str,ctl_pro_str,note_str);
    if (pro_dayset_serv::get_inst().day_set_pro(tmp_pro,date_str) < 0)
    {
        qDebug()<<"Add pro error...";
    }
}

