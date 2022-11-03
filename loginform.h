#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QDialog>
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlRecord>

//#include "mainwindow.h"

namespace Ui {
class LoginForm;
}

class LoginForm : public QDialog
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = nullptr);
    ~LoginForm();
    QString loginUsername = "";
    QString loginPassword = "";
    QSqlDatabase DB;

private slots:
    void on_pushButton_Login_clicked();

private:
    Ui::LoginForm *ui;
};

#endif // LOGINFORM_H
