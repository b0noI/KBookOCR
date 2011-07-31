#ifndef KERNELDIALOG_H
#define KERNELDIALOG_H

#include "ocrkernel.h"

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

    OCRKernel* getOCRKernel();
    bool isLayout() const;

private slots:
    void on_pushButton_clicked();

private:
    Ui::KernelDialog *ui;
};

#endif // KERNELDIALOG_H
