#include "register.h"
#include "ui_register.h"
#include "mainwindow.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTimer>

extern QTimer *timer;

Register::Register(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    display_dateAndtime();
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(btn1_clicked()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(btn2_clicked()));
    ui->pushButton_1->setShortcut(Qt::Key_Return);

    connect(timer,SIGNAL(timeout()),this,SLOT(display_dateAndtime()));
    timer->start(1000);


}

Register::~Register()
{
    delete ui;
}

void Register::display_dateAndtime()
{
    MainWindow e1;
    QString date,time;
    e1.get_dateAndtime(date, time);
    ui->label_4->setText(date);
    ui->lcdNumber->display(QString("Date: %1").arg(time));

}

void Register::ConnectSqlite(QString &UserName, QString &Password)
{
    QString name = UserName;
    QString pwd = Password;

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

    if(!b1.exec("Select * From Login"))
    {
        b1.exec("create table Login(userName text primary key, Password text)");
    }

    if(b1.exec(QString("Select * "
                       "From Login "
                       "Where userName = '%1'").arg(UserName)))
    {
        ui->label_3->setText("userName exists!!");
        ui->label_3->setStyleSheet("background: green");

    }
    else
    {
        b1.exec(QString("Insert Into Login Values('%1', '%2')").arg(name, pwd));
        ui->label_3->setText("successfully!");
    }


    a1.close();

}

void Register::btn1_clicked()
{

    QString UserName = ui->lineEdit->text();
    QString Password = ui->lineEdit_2->text();

    if(UserName == "" || Password == "")
    {
        ui->label_3->setText("UserName or Password can't be null!");
        ui->label_3->setStyleSheet("background: red");
    }

    else ConnectSqlite(UserName, Password);

}

void Register::btn2_clicked()
{
    this->close();

}

