#ifndef PRO_SEL_DLG_H
#define PRO_SEL_DLG_H

#include <QDialog>

namespace Ui {
class pro_sel_dlg;
}

class pro_sel_dlg : public QDialog
{
    Q_OBJECT

public:
    explicit pro_sel_dlg(QWidget *parent = 0);
    ~pro_sel_dlg();

private:
    Ui::pro_sel_dlg *ui;
};

#endif // PRO_SEL_DLG_H
