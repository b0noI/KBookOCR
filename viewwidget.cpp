#include "viewwidget.h"
#include <QPixmap>
#include <QIcon>
#include <QFileDialog>
#include <QMessageBox>
#include "ui_viewwidget.h"

/*ViewWidget::ViewWidget(int _id, QWidget *parent, QString path) :
    QWidget(parent),
    ui(new Ui::ViewWidget),
    pageNumber(-1),
    View(path)
{
    ui->setupUi(this);
    ui->label->setText("1");
    this->setId(_id);
    this->setImg();
}*/

ViewWidget::ViewWidget(int _id, QWidget *parent, QImage img, int n) :
    QWidget(parent),
    ui(new Ui::ViewWidget),
    pageNumber(-1),
    View(img)
{

    ui->setupUi(this);
    ui->label->setText(QString::number(n));
    this->set_Id(_id);
    this->setImg(img);
    //this->setImg()

}

ViewWidget::ViewWidget(int _id, QWidget *parent, Document *doc, int n) :
    QWidget(parent),
    ui(new Ui::ViewWidget),
    pageNumber(-1),
    View(doc, n)
{

    ui->setupUi(this);
    ui->label->setText(QString::number(n));
    this->set_Id(_id);
    this->setImg(doc->getPreview(n));
    //this->setImg()

}

ViewWidget::~ViewWidget()
{
    delete ui;
}

bool ViewWidget::isChecked()
{
    return ui->label_view->isChecked();
}

bool ViewWidget::saveImg(QString path)
{
    if (this->getView().width() > 20)
    {
        this->getView().save(path);
        return true;
    }
    return false;
}

bool ViewWidget::setImg(QImage img)
{
    if (img.width() > 50 && img.height() > 50)
    {
        QSize size(70,110);
        QPixmap pm;
        pm = QPixmap::fromImage(img);
        QIcon ico(pm);
        ui->label_view->setIcon(ico);
        ui->label_view->setIconSize(size);
        return true;
    }
    return false;
}

//int ViewWidget::

bool ViewWidget::setImg()
{
    return this->setImg(this->getView());
}

int ViewWidget::get_Id()
{
    return this->__ID;
}

bool ViewWidget::set_Id(int id)
{
    if (id > 0)
    {
        this->__ID = id;
        return true;
    }
    return false;
}

void ViewWidget::on_pushButton_clicked()
{
    emit this->deleted(this->get_Id());
}

bool ViewWidget::setPageNumber(int num)
{
    if (num > 0 && num != this->getPageNumber())
    {
        this->pageNumber = num;
        ui->label->setText(QString::number(num));
        return true;
    }
    return false;
}

int ViewWidget::getPageNumber()
{
    return this->pageNumber;
}

void ViewWidget::on_label_view1_clicked()
{

}

void ViewWidget::on_pushButton_4_clicked()
{
    QString path = QFileDialog::getSaveFileName();
    if (!path.isEmpty())
    {
        //this->getView().save(path);
        this->saveImg(path);
        QMessageBox::information(0,"KBookOCR","saved to: "+path);
    }
}

void ViewWidget::on_label_view_clicked()
{
    if (ui->label_view->isChecked())
    {
        emit this->selected(this->get_Id());
    }
}
