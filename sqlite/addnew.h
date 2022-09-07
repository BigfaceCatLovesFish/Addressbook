#ifndef ADDNEW_H
#define ADDNEW_H

#include <QMainWindow>

namespace Ui {
class AddNew;
}

class AddNew : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddNew(QWidget *parent = nullptr);
    ~AddNew();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void AddSqlite(QString &s1);
    void display_dateAndtime();

private:
    Ui::AddNew *ui;
};

#endif // ADDNEW_H
