#ifndef KERNELDIALOG_H
#define KERNELDIALOG_H

#include "ocrkernel.h"

#include <QDialog>
//#include <QObject>

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

signals:
    void newKernel();

private slots:
    void on_pushButton_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::KernelDialog *ui;
};

#endif // KERNELDIALOG_H
