#include "convertingtoimgwite.h"
#include "ui_convertingtoimgwite.h"

convertingToImgWite::convertingToImgWite(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::convertingToImgWite)
{
    ui->setupUi(this);
}

convertingToImgWite::~convertingToImgWite()
{
    delete ui;
}

void convertingToImgWite::setProgress(int cur, int all)
{
    ui->progressBar->setMaximum(all);
    ui->progressBar->setValue(cur);
}
