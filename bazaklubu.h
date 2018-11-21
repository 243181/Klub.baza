#ifndef BAZAKLUBU_H
#define BAZAKLUBU_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class Bazaklubu;
}

class Bazaklubu : public QDialog
{
    Q_OBJECT

public:
    explicit Bazaklubu(QWidget *parent = nullptr);
    ~Bazaklubu();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_usun_clicked();

    void on_pushButton_tabela_clicked();

private:
    Ui::Bazaklubu *ui;
};

#endif // BAZAKLUBU_H
