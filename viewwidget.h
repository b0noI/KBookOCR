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
    ~ViewWidget();
    bool setId(int);
    int getId();
    bool setPageNumber(int);
    int getPageNumber();

signals:
    void deleted(int);

private slots:
    void on_pushButton_clicked();

    void on_label_view1_clicked();

private:
    Ui::ViewWidget *ui;
    int id;
    int pageNumber;
    bool setImg(QImage);
    bool setImg();
};

#endif // VIEWWIDGET_H
