#include "pro_sel_dlg.h"
#include "ui_pro_sel_dlg.h"

pro_sel_dlg::pro_sel_dlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pro_sel_dlg)
{
    ui->setupUi(this);
    ui->date_sel_edit->setDisplayFormat("yyyy-MM-dd");
    QDate qdate;
    ui->date_sel_edit->setDate(qdate.currentDate());
}

pro_sel_dlg::~pro_sel_dlg()
{
    delete ui;
}

void pro_sel_dlg::on_sel_btn_clicked()
{
    QString date_str = ui->date_sel_edit->text();
    pro pro;
    pro_sel_serv::get_inst().sel_pro(date_str,&pro);
    ui->note_sel_edit->setText(pro.get_note());
    ui->wpro_sel_edit->setText(pro.get_writing_pro_str());
    ui->rpro_sel_edit->setText(pro.get_reading_pro_str());
    ui->alpro_sel_edit->setText(pro.get_art_learning_pro_str());
    ui->ctlpro_sel_edit->setText(pro.get_art_learning_pro_str());
}
