#ifndef SCANERDIALOG_H
#define SCANERDIALOG_H

#include <QDialog>
//#include <

namespace Ui {
    class ScanerDialog;
}

class ScanerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ScanerDialog(QWidget *parent = 0);
    ~ScanerDialog();

private:
    Ui::ScanerDialog *ui;
};

#endif // SCANERDIALOG_H
