#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStatusBar>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap pix("C:/Users/kubam/OneDrive/Pulpit/logowanie.jpg");
    ui->label_pic->setPixmap(pix);


    if(!connOpen())
        ui->label->setText("Nie udało sie połączyć");
    else
        ui->label->setText("Połączono");
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString login,haslo;
    login=ui->lineEdit_login->text();
    haslo=ui->lineEdit_haslo->text();

    if(!connOpen()){

        qDebug()<<"Nie udało się połączyć";
        return;
    }

    connOpen();
    QSqlQuery qry;
    qry.prepare("select * from Dane where login='"+login+"' and haslo='"+haslo+"'");

    if(qry.exec()){
        if(qry.next()){
            qDebug()<<"Udało się zalogować";
            QMessageBox::information(this,"Zapraszam","Dane poprawne");
            connClose();
            this->hide();
            Bazaklubu bazaklubu;
            bazaklubu.setModal(true);
            bazaklubu.exec();

        }
        else{
            qDebug()<<"Dane niepoprawne";
            ui->statusBar->showMessage("Dane niepoprawne");
            close();
            qDebug()<<"Zakończono";
        }
    }

}
