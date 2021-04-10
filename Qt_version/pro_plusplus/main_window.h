#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>
#include <QPainter>
#include "pro_sel_dlg.h"
#include "ui_main_window.h"
#include "pro_dayset_dlg.h"
#include "statistics_dlg.h"

namespace Ui {
class main_window;
}

class main_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit main_window(QWidget *parent = 0);
    ~main_window();
    void paintEvent(QPaintEvent *event);

private slots:
    void on_sel_pro_clicked();
    void on_pro_inpt_btn_clicked();
    void on_pro_statistics_clicked();

private:
    Ui::main_window *ui;
};

#endif // MAIN_WINDOW_H
