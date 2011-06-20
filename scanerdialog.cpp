#include "scanerdialog.h"
#include "ui_scanerdialog.h"

ScanerDialog::ScanerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScanerDialog)
{
    ui->setupUi(this);
    //this->scanerWidget.show();
    //ui->verticalLayout->addWidget((QWidget)this->scanerWidget);
}

ScanerDialog::~ScanerDialog()
{
    delete ui;
}
