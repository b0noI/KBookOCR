#ifndef KERNELDIALOG_H
#define KERNELDIALOG_H

#include <QDialog>

namespace Ui {
    class KernelDialog;
}

class KernelDialog : public QDialog
{
    Q_OBJECT

public:
    explicit KernelDialog(QWidget *parent = 0);
    ~KernelDialog();

private:
    Ui::KernelDialog *ui;
};

#endif // KERNELDIALOG_H
