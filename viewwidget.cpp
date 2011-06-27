#include "viewwidget.h"
#include <QPixmap>
#include <QIcon>
#include <QFileDialog>
#include <QMessageBox>
#include <QTransform>


#include <KDE/KIconLoader>
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

ViewWidget::ViewWidget(int _id, QWidget *parent, QImage img, int n, Document* doc,int n2) :
    QWidget(parent),
    ui(new Ui::ViewWidget),
    pageNumber(-1),
    View(img,doc,n2)
    //rotate(0)
{

    ui->setupUi(this);
    ui->label->setText(QString::number(n));
    this->set_Id(_id);
    this->setImg(img);
    this->icoLoad();
    //this->setImg()

}

ViewWidget::ViewWidget(int _id, QWidget *parent, Document *doc, int n) :
    QWidget(parent),
    ui(new Ui::ViewWidget),
    pageNumber(-1),
    View(doc, n)
    //rotate(0)
{

    ui->setupUi(this);
    ui->label->setText(QString::number(n));
    this->set_Id(_id);
    this->setImg(doc->getPreview(n));
    this->icoLoad();
    //this->setImg()

}

ViewWidget::~ViewWidget()
{
    delete ui;
}

void ViewWidget::icoLoad()
{
    KIconLoader iconLoader;
    QIcon icoLeft(iconLoader.loadIcon(QString("object-rotate-left"),(KIconLoader::Group)4));
    ui->pushButton_2->setIcon(icoLeft);

    QIcon icoRight(iconLoader.loadIcon(QString("object-rotate-right"),(KIconLoader::Group)4));
    ui->pushButton_3->setIcon(icoRight);

    QIcon icoDownload(iconLoader.loadIcon(QString("download"),(KIconLoader::Group)4));
    ui->pushButton_4->setIcon(icoDownload);

    QIcon icoDel(iconLoader.loadIcon(QString("edit-delete"),(KIconLoader::Group)4));
    ui->pushButton->setIcon(icoDel);

}

bool ViewWidget::rotateLeft()
{
    this->rotate -= 1;
    if (this->rotate < 0)
        this->rotate = 3;

    QIcon ico = ui->label_view->icon();
    QPixmap pm = ico.pixmap(100);
    //pm.toImage()
    QImage img = pm.toImage();
    QTransform tr;
    tr.rotate(-90);

    QPixmap pm2;
    pm2 = pm2.fromImage(img.transformed(tr));
    QIcon ico2(pm2);
    ui->label_view->setIcon(ico2);
    emit this->selected(this->get_Id());
    return true;
}

bool ViewWidget::rotateRight()
{
    this->rotate += 1;
    if (this->rotate > 3)
        this->rotate = 0;

    QIcon ico = ui->label_view->icon();
    QPixmap pm = ico.pixmap(100);
    //pm.toImage()
    QImage img = pm.toImage();
    QTransform tr;
    tr.rotate(90);

    QPixmap pm2;
    pm2 = pm2.fromImage(img.transformed(tr));
    QIcon ico2(pm2);
    ui->label_view->setIcon(ico2);

    emit this->selected(this->get_Id());

    return true;
}

bool ViewWidget::setChecked(bool check)
{
    ui->label_view->setChecked(check);
    return ui->label_view->isChecked();
}

bool ViewWidget::isChecked()
{
    return ui->label_view->isChecked();
}



bool ViewWidget::saveImg(QString path)
{
    if (this->getView().width() > 20)
    {
        //this->getView().save(path);
        if (this->getRotateAngel() != 0)
        {
        QImage img = this->doc->getRealPage(this->realPage);
        QTransform tr;
        tr.rotate(this->getRotateAngel());
        img.transformed(tr).save(path);
        }
        else
            this->doc->getRealPage(this->realPage).save(path);



        //QImage img = this->doc->getRealPage(this->realPage);
        //img.save(path);
        return true;
    }
    return false;
}

bool ViewWidget::setImg(QImage img)
{
    if (img.width() > 50 && img.height() > 50)
    {
        QSize size(79,110);
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

void ViewWidget::on_pushButton_2_clicked()
{
    this->rotateLeft();
}

void ViewWidget::on_pushButton_3_clicked()
{
    this->rotateRight();
}
