#include "kerneldialog.h"
#include "ui_kerneldialog.h"

#include "tesseractocr.h"
#include "cuniiformocr.h"

KernelDialog::KernelDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KernelDialog)
{
    ui->setupUi(this);
}

OCRKernel* KernelDialog::getOCRKernel()
{
    switch (ui->comboBox->currentIndex())
    {
        case 0:
        return new CuniIFormOCR();
        break;
    case 1:
        return new TesseractOCR();
        break;
    default:
        return new CuniIFormOCR();
        break;
    };
}

bool KernelDialog::isLayout() const
{
    return ui->checkBox->isChecked();
}

KernelDialog::~KernelDialog()
{
    delete ui;
}

void KernelDialog::on_pushButton_clicked()
{
    this->close();
}

void KernelDialog::on_comboBox_currentIndexChanged(int index)
{
    emit this->newKernel();
}
