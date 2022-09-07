#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#include <QMainWindow>

namespace Ui {
class Addressbook;
}

class Addressbook : public QMainWindow
{
    Q_OBJECT

public:
    explicit Addressbook(QWidget *parent = nullptr);
    ~Addressbook();



private slots:
    void display_dateAndtime();
    void btn1_clicked();
    void btn2_clicked();
    void btn3_clicked();
    void btn4_clicked();
    void AddSqlite();
    void ListSqlite();
    void QuerySqlite();


private:
    Ui::Addressbook *ui;
};

#endif // ADDRESSBOOK_H
