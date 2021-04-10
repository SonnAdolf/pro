#include "main_window.h"

main_window::main_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::main_window)
{
    ui->setupUi(this);
}

main_window::~main_window()
{
    delete ui;
}

void main_window::paintEvent(QPaintEvent *event)
{ //绘制窗口背景图片
    Q_UNUSED(event);
    QPainter painter(this);
    QPixmap img;
    img.load(":/images/title.jpg");
    painter.drawPixmap(0,ui->mainToolBar->height(),this->width(),this->height()-ui->mainToolBar->height()-ui->statusBar->height(),img);
}

void main_window::on_pro_inpt_btn_clicked()
{
    pro_dayset_dlg * pro_inpt_dlg = new pro_dayset_dlg();
    pro_inpt_dlg->show();
}

void main_window::on_sel_pro_clicked()
{
    pro_sel_dlg * psel_dlg = new pro_sel_dlg();
    psel_dlg->show();
}

void main_window::on_pro_statistics_clicked()
{
    statistics_dlg * stat_dlg = new statistics_dlg();
    stat_dlg->show();
}
