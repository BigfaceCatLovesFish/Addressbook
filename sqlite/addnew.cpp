#include "addnew.h"
#include "ui_addnew.h"
#include "mainwindow.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTimer>

extern QTimer *timer;

AddNew::AddNew(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddNew)
{
    ui->setupUi(this);
    display_dateAndtime();
    ui->pushButton->setShortcut(Qt::Key_Return);
    connect(timer,SIGNAL(timeout()),this,SLOT(display_dateAndtime()));
    timer->start(1000);
}

AddNew::~AddNew()
{
    delete ui;
}

void AddNew::display_dateAndtime()
{
    MainWindow e1;
    QString date,time;
    e1.get_dateAndtime(date, time);
    ui->label_6->setText(QString("Date: %1").arg(date));
    ui->lcdNumber->display(time);
}

void AddNew::AddSqlite(QString &s1)
{
    QString contact = s1;
    QStringList d1 = contact.split(",");

    QSqlDatabase a1;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        a1 = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        a1 = QSqlDatabase::addDatabase("SQLITECIPHER");

    }
    a1.setDatabaseName("Login.sqlite3");
    a1.setPassword("sa");   
    a1.open();

    QSqlQuery b1(a1);

    if(!b1.exec("Select * From Contact"))
    {
        b1.exec("Create Table Contact(name text primary key, phone text, email text, address text)");
    }

    if(b1.exec(QString("Select * "
                       "From Contact "
                       "Where name = %1 And phone = %2").arg(d1.at(0), d1.at(1))))
    {
        ui->label_5->setText("userName and phone exists!!");
        ui->label_5->setStyleSheet("background: green");

    }
    else
    {
        b1.exec(QString("Insert Into Contact"
                       "(name, phone, email, address)"
                        "Values(%1)").arg(contact));

        ui->label_5->setText("successfully added!");
    }

    a1.close();
}

void AddNew::on_pushButton_2_clicked()
{   
    this->close();
}

void AddNew::on_pushButton_clicked()
{
    QString name = ui->lineEdit->text();
    QString phone = ui->lineEdit_2->text();
    QString email = ui->lineEdit_3->text();
    QString address = ui->lineEdit_4->text();

    QString contact = QString("'%1', '%2', '%3', '%4'").arg(name, phone, email, address);

    if(name == "" || phone == "")
    {
        ui->label_5->setText("name or phone can't be null!!");
        ui->label_5->setStyleSheet("background: red");
    }
    else
    {
        AddSqlite(contact);
    }


}


