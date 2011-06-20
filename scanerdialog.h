#ifndef SCANERDIALOG_H
#define SCANERDIALOG_H

#include <QDialog>
#include <libksane/ksane.h>
//#include <libksane/

namespace Ui {
    class ScanerDialog;
}

using namespace KSaneIface;

class ScanerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ScanerDialog(QWidget *parent = 0);
    ~ScanerDialog();

private:
    Ui::ScanerDialog *ui;
    KSaneWidget scanerWidget;
};

#endif // SCANERDIALOG_H
