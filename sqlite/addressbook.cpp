#include "addressbook.h"
#include "ui_addressbook.h"
#include "addnew.h"
#include "mainwindow.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTimer>

extern QString name;
extern QTimer *timer;

Addressbook::Addressbook(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Addressbook)
{
    ui->setupUi(this);
    this->setWindowTitle(QString("Hello! Welcome to %1's addressbook").arg(name));
    display_dateAndtime();
    ListSqlite();

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(btn1_clicked()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(btn2_clicked()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(btn3_clicked()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(btn4_clicked()));

    connect(timer,SIGNAL(timeout()),this,SLOT(display_dateAndtime()));
    connect(timer,SIGNAL(timeout()),this,SLOT(ListSqlite()));
    timer->start(1000);

}

Addressbook::~Addressbook()
{
    delete ui;
}

void Addressbook::display_dateAndtime()
{
    MainWindow e1;
    QString date,time;
    e1.get_dateAndtime(date, time);
    ui->label->setText(QString("Date: %1").arg(date));
    ui->lcdNumber->display(time);
}

void Addressbook::AddSqlite()
{
    QString name;
    QString pwd;
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

    b1.exec(QString("Select UserName, Password "
                        "From Login "
                        "Where UserName = '%1' ").arg(name));

    while(b1.next())
    {
        pwd = b1.value(1).toString();

    }

    a1.close();

}

void Addressbook::ListSqlite()
{
    ui->listWidget->clear();
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
    b1.exec("Select * From Contact");

    while(b1.next())
    {
        QString name = b1.value(0).toString();
        QString phone = b1.value(1).toString();
        QString email = b1.value(2).toString();
        QString address = b1.value(3).toString();

        QString a = QString("name: %1   ").arg(name) + '\n'
                   +QString("phone: %2 ").arg(phone) + '\n'
                   +QString("e-mail: %3").arg(email) + '\n'
                   +QString("address: %4").arg(address);

        QListWidgetItem *add_item = new QListWidgetItem(ui->listWidget);
        add_item->setSizeHint(QSize(400,100));
        add_item->setFont(QFont("Source Code Pro",14));
        add_item->setIcon(QIcon("a.png"));
        ui->listWidget->setIconSize(QSize(100,90));
        add_item->setText(a);
        ui->listWidget->addItem(add_item);
    }

    a1.close();

}

void Addressbook::QuerySqlite()
{

}

void Addressbook::btn1_clicked()
{
    AddNew *w3 = new AddNew;
    w3->show();
}

void Addressbook::btn2_clicked()
{
    QuerySqlite();

}

void Addressbook::btn3_clicked()
{
    this->close();
}

void Addressbook::btn4_clicked()
{
    MainWindow *w = new MainWindow;
    w->show();
    this->close();
}
