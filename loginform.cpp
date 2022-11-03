#include "loginform.h"
#include "ui_loginform.h"

LoginForm::LoginForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginForm)
{
    //Debug
    loginUsername = "postgres";
    loginPassword = "Sergei";
    //Debug
    ui->setupUi(this);
    ui->lineEdit_EnterPassword->setEchoMode(QLineEdit::Password);
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::on_pushButton_Login_clicked()
{
    loginUsername = ui->lineEdit_EnterUsername->text();
    loginPassword = ui->lineEdit_EnterPassword->text();

    this->close();
}

