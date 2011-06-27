#ifndef VIEWWIDGET_H
#define VIEWWIDGET_H

#include <QWidget>
#include "view.h"

namespace Ui {
    class ViewWidget;
}

class ViewWidget : public QWidget, public View
{
    Q_OBJECT

public:
    //explicit ViewWidget(int, QWidget *parent, QString);
    explicit ViewWidget(int, QWidget *parent, Document*, int);
    explicit ViewWidget(int, QWidget *parent, QImage, int, Document*, int);
    ~ViewWidget();
    bool set_Id(int);
    int get_Id();
    bool setPageNumber(int);
    int getPageNumber();
    bool isChecked();
    bool saveImg(QString);
    bool setChecked(bool);
    bool rotateLeft();
    bool rotateRight();

signals:
    void deleted(int);
    void selected(int);

private slots:
    void on_pushButton_clicked();

    void on_label_view1_clicked();

    void on_pushButton_4_clicked();

    void on_label_view_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::ViewWidget *ui;
    int __ID;
    int pageNumber;
    bool setImg(QImage);
    bool setImg();

    void icoLoad();
};

#endif // VIEWWIDGET_H
