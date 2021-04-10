#ifndef STATISTICS_DLG_H
#define STATISTICS_DLG_H

#include <QDialog>

namespace Ui {
class statistics_dlg;
}

class statistics_dlg : public QDialog
{
    Q_OBJECT

public:
    explicit statistics_dlg(QWidget *parent = 0);
    ~statistics_dlg();

private:
    Ui::statistics_dlg *ui;
};

#endif // STATISTICS_DLG_H
