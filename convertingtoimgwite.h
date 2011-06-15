#ifndef CONVERTINGTOIMGWITE_H
#define CONVERTINGTOIMGWITE_H

#include <QDialog>

namespace Ui {
    class convertingToImgWite;
}

class convertingToImgWite : public QDialog
{
    Q_OBJECT

public:
    explicit convertingToImgWite(QWidget *parent = 0);
    ~convertingToImgWite();
    void setProgress(int,int);

private:
    Ui::convertingToImgWite *ui;
};

#endif // CONVERTINGTOIMGWITE_H
