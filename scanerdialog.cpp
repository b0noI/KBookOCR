#include "scanerdialog.h"
#include "ui_scanerdialog.h"

ScanerDialog::ScanerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScanerDialog)
{
    ui->setupUi(this);
}

ScanerDialog::~ScanerDialog()
{
    delete ui;
}
