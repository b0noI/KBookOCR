#ifndef RANGEDIALOG_H
#define RANGEDIALOG_H

#include <QDialog>

namespace Ui {
    class RangeDialog;
}

class RangeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RangeDialog(QWidget *parent = 0);
    ~RangeDialog();
    bool setMaximum(int);
    int getMaximum() const;
    bool validData() const;
    bool clear();

signals:
    void rangeReady(int, int);

private slots:
    void on_spinBox_valueChanged(int arg1);

    void on_buttonBox_accepted();

    void on_spinBox_2_valueChanged(int arg1);

private:
    int maximum;
    Ui::RangeDialog *ui;
};

#endif // RANGEDIALOG_H
