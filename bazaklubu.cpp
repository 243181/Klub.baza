#include "bazaklubu.h"
#include "ui_bazaklubu.h"
#include <QMessageBox>

Bazaklubu::Bazaklubu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Bazaklubu)
{
    ui->setupUi(this);
    MainWindow conn;
            if(!conn.connOpen())
                ui->label_sec_status->setText("Nie udało sie połączyć");
            else
                ui->label_sec_status->setText("Połączono");
}

Bazaklubu::~Bazaklubu()
{
    delete ui;
}

void Bazaklubu::on_pushButton_clicked()
{
    MainWindow conn;
    QString id,imie,nazwisko,wiek,wzrost,pozycja,numer,lepsza_noga;
    id=ui->lineEdit_id->text();
    imie=ui->lineEdit_imie->text();
    nazwisko=ui->lineEdit_nazwisko->text();
    wiek=ui->lineEdit_wiek->text();
    wzrost=ui->lineEdit_wzrost->text();
    pozycja=ui->lineEdit_pozycja->text();
    numer=ui->lineEdit_numer->text();
    lepsza_noga=ui->lineEdit_lnoga->text();

    if(!conn.connOpen()){

        qDebug()<<"Nie udało się połączyć";
        return;
    }

    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("insert into logowanie (ID,Imie,Nazwisko,Wiek,Wzrost,Pozycja,Numer,Lepsza_noga) values ('"+id+"','"+imie+"','"+nazwisko+"','"+wiek+"','"+wzrost+"','"+pozycja+"','"+numer+"','"+lepsza_noga+"')");

    if(qry.exec()){
        QMessageBox::critical(this,tr("Zapisz"),tr("Zapisano"));
        conn.connClose();
    }
    else{
        QMessageBox::critical(this,tr("Błąd"),qry.lastError().text());
    }
}

void Bazaklubu::on_pushButton_usun_clicked()
{
    MainWindow conn;
    QString id,imie,nazwisko,wiek,wzrost,pozycja,numer,lepsza_noga;
    id=ui->lineEdit_id->text();
    //imie=ui->lineEdit_imie->text();
    //nazwisko=ui->lineEdit_nazwisko->text();
    //wiek=ui->lineEdit_wiek->text();
    //wzrost=ui->lineEdit_wzrost->text();
    //pozycja=ui->lineEdit_pozycja->text();
    //numer=ui->lineEdit_numer->text();
    //lepsza_noga=ui->lineEdit_lnoga->text();

    if(!conn.connOpen()){

        qDebug()<<"Nie udało się połączyć";
        return;
    }

    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("Delete from logowanie where ID='"+id+"'");

    if(qry.exec()){
        QMessageBox::critical(this,tr("Usuń"),tr("Usunięto"));
        conn.connClose();
    }
    else{
        QMessageBox::critical(this,tr("Błąd"),qry.lastError().text());
    }
}

void Bazaklubu::on_pushButton_tabela_clicked()
{
    MainWindow conn;
    QSqlQueryModel * modal=new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery* qry=new QSqlQuery(conn.mydb);

    qry->prepare("select * from logowanie");

    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);

    conn.connClose();
    qDebug() <<(modal->rowCount());

}
