#include "pro_dayset_dlg.h"
#include "ui_pro_dayset_dlg.h"

pro_dayset_dlg::pro_dayset_dlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pro_dayset_dlg)
{
    ui->setupUi(this);
    ui->date_edit->setDisplayFormat("yyyy-MM-dd");
    QDate qdate;
    ui->date_edit->setDate(qdate.currentDate());
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
    if (write_pro_str.compare("")==0||write_pro_str==NULL)
    {
        write_pro_str = "0";
    }
    if (read_pro_str.compare("")==0||read_pro_str==NULL)
    {
        read_pro_str = "0";
    }
    if (art_pro_str.compare("")==0||art_pro_str==NULL)
    {
        art_pro_str = "0";
    }
    if (ctl_pro_str.compare("")==0||ctl_pro_str==NULL)
    {
        ctl_pro_str = "0";
    }
    bool ret;
    write_pro_str.toFloat(&ret);
    if (!ret)
    {
        QMessageBox::about(NULL,  "錯誤",  "輸入信息有誤");
        return;
    }
    read_pro_str.toFloat(&ret);
    if (!ret)
    {
        QMessageBox::about(NULL,  "錯誤",  "輸入信息有誤");
        return;
    }
    art_pro_str.toFloat(&ret);
    if (!ret)
    {
        QMessageBox::about(NULL,  "錯誤",  "輸入信息有誤");
        return;
    }
    ctl_pro_str.toFloat(&ret);
    if (!ret)
    {
        QMessageBox::about(NULL,  "錯誤",  "輸入信息有誤");
        return;
    }
    pro tmp_pro(write_pro_str,art_pro_str,read_pro_str,ctl_pro_str,note_str);
    if (pro_dayset_serv::get_inst().day_set_pro(tmp_pro,date_str) < 0)
    {
        qDebug()<<"Add pro error...";
        QMessageBox::about(NULL,  "錯誤",  "輸入信息有誤");
    }
    else
    {
        QMessageBox::about(NULL,  "成功",  "pro++");
    }
}

