#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include "bazaklubu.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QSqlDatabase mydb;
    void connClose()
    {
        mydb.close();
        mydb.removeDatabase(QSqlDatabase::defaultConnection);
    }
    bool connOpen()
    {
       mydb=QSqlDatabase::addDatabase("QSQLITE");
       mydb.setDatabaseName("C:/sqlite2/logowanie.db");

       if(!mydb.open()){
           qDebug()<<("Nie udało sie połączyć");
           return false;
       }
       else{
           qDebug()<<("Połączono");
           return true;
       }
    }

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
