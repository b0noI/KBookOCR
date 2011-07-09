#include "rangedialog.h"
#include "ui_rangedialog.h"

RangeDialog::RangeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RangeDialog)
{
    ui->setupUi(this);
}

RangeDialog::~RangeDialog()
{
    delete ui;
}

bool RangeDialog::clear()
{
    ui->spinBox->setValue(0);
    ui->spinBox_2->setValue(0);
}

int RangeDialog::getMaximum() const
{
    return this->maximum;
}

bool RangeDialog::setMaximum(int max)
{
    if (max >= 0)
    {
        this->maximum = max;
        return true;
    }
    return false;
}

void RangeDialog::on_spinBox_valueChanged(int arg1)
{

    if (ui->spinBox->value() > this->getMaximum())
        ui->spinBox->setValue(arg1);

    if (ui->spinBox->value() > ui->spinBox_2->value())
        ui->spinBox_2->setValue(arg1);

}

bool RangeDialog::validData() const
{
    if (ui->spinBox->value() <= ui->spinBox_2->value() &&
            ui->spinBox_2->value() <= this->getMaximum())
        return true;
    return false;
}

void RangeDialog::on_buttonBox_accepted()
{
    if (this->validData())
    {
        emit this->rangeReady(ui->spinBox->value(),
                              ui->spinBox_2->value());
    }
    this->close();
}

void RangeDialog::on_spinBox_2_valueChanged(int arg1)
{
    if (ui->spinBox_2->value() > this->getMaximum())
        ui->spinBox_2->setValue(this->getMaximum());

    if (ui->spinBox_2->value() < ui->spinBox->value())
        ui->spinBox->setValue(arg1);
}
