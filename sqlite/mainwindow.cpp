#include "mainwindow.h"
#include "qtimer.h"
#include "ui_mainwindow.h"
#include "register.h"
#include "addressbook.h"


#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDateTime>


QString name;
QTimer *timer = new QTimer;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    display_dateAndtime();
    this->setWindowFlags(Qt::Dialog);

    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(btn1_clicked()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(btn2_clicked()));
    ui->pushButton_2->setShortcut(Qt::Key_Return);

    connect(timer,SIGNAL(timeout()),this,SLOT(display_dateAndtime()));
    timer->start(1000);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::get_dateAndtime(QString &date, QString &time)
{
    QDateTime t1 = QDateTime::currentDateTime();

    date = t1.date().toString();
    time = t1.time().toString();
}

void MainWindow::display_dateAndtime()
{
    QString date,time;
    get_dateAndtime(date, time);

    ui->label_3->setText(QString("Date: %1").arg(date));
    ui->lcdNumber->display(time);
}

int MainWindow::connectsqlite(QString &UserName, QString &Password)
{
    name = UserName;

    if(name == "")
    {
        return 0;
    }

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

    if(!(pwd == Password))
    {
        return 0;
    }

    return 1;
}

void MainWindow::btn1_clicked()
{
    Register *w1 = new Register;
    w1->show();
}

void MainWindow::btn2_clicked()
{
    QString UserName = ui->lineEdit->text();
    QString Password = ui->lineEdit_2->text();

    if(connectsqlite(UserName, Password))
    {
        Addressbook *w2 = new Addressbook;
        w2->show();
        this->close();
    }

}





