#include "kerneldialog.h"
#include "ui_kerneldialog.h"

KernelDialog::KernelDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KernelDialog)
{
    ui->setupUi(this);
}

KernelDialog::~KernelDialog()
{
    delete ui;
}
