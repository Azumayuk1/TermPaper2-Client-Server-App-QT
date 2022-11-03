#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    newLogin = new LoginForm();
    newLogin->show();

    //Debug
    //dbUsername = "postgres";
    //dbPassword = "Sergei";
    //Debug
    currentProgramDate = "2002-02-02";

    dbSqlQueries newQueries;
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    DB.close();
    DB = QSqlDatabase();
    QSqlDatabase::removeDatabase("QtConnection"); //QSqlDatabase::defaultConnection
    qDebug()<<"Database connection CLOSED";
    delete ui;
}

void MainWindow::on_pushButton_LoadMovieLibrary_clicked()
{
    ui->tableView_Movies->setModel(newQueries.loadMovieLibraryFromDb(DB));
    qDebug()<<"Movie library LOADED";
}


void MainWindow::on_pushButton_addNewMovie_clicked()
{
    newQueries.addNewMovieToLibrary(DB, ui->lineEdit_MovieTitle->text(),
                                    ui->lineEdit_MovieAuthor->text(),
                                    ui->lineEdit_RentPrice->text());
    ui->tableView_Movies->setModel(newQueries.loadMovieLibraryFromDb(DB));
    qDebug()<<"New movie ADDED";
}


void MainWindow::on_pushButton_LoadCustomers_clicked()
{
    ui->tableView_Customers->setModel(newQueries.loadCustomersFromDb(DB));
    qDebug()<<"Customers table LOADED";
}


void MainWindow::on_pushButton_AddNewCustomer_clicked()
{
    newQueries.addNewCustomerToDb(DB, ui->lineEdit_CustomerName->text(),
                                  ui->lineEdit_CustomerAdress->text(),
                                  ui->lineEdit_PhoneNumber->text());
    ui->tableView_Customers->setModel(newQueries.loadCustomersFromDb(DB));
    qDebug()<<"New customer ADDED";
}


void MainWindow::on_pushButton_LoadPayments_clicked()
{
    ui->tableView_Payments->setModel(newQueries.loadPaymentsFromDb(DB));
    qDebug()<<"Payments table LOADED";
}


void MainWindow::on_pushButton_addNewPayment_clicked()
{
    newQueries.addNewPaymentToDb(DB,ui->lineEdit_PaymentMethod->text(),
                                 ui->checkBox_isPaymentCompleted->isChecked(),
                                 ui->lineEdit_PaymentAmount->text(),
                                 ui->lineEdit_PaymentDeposit->text());
    ui->tableView_Payments->setModel(newQueries.loadPaymentsFromDb(DB));
    qDebug()<<"New payment ADDED";
}





void MainWindow::on_pushButton_movieDeleteSelected_clicked()
{
    newQueries.deleteMovieFromLibrary(DB, ui->tableView_Movies);
    qDebug()<<"selected Movie DELETED";
    ui->tableView_Movies->setModel(newQueries.loadMovieLibraryFromDb(DB));
}


void MainWindow::on_pushButton_DeleteCustomer_clicked()
{
    newQueries.deleteCustomerFromDb(DB, ui->tableView_Customers);
    qDebug()<<"selected Customer DELETED";
    ui->tableView_Customers->setModel(newQueries.loadCustomersFromDb(DB));
}


void MainWindow::on_pushButton_deletePayment_clicked()
{
    newQueries.deletePaymentFromDb(DB, ui->tableView_Payments);
    qDebug()<<"selected Payment DELETED";
    ui->tableView_Payments->setModel(newQueries.loadPaymentsFromDb(DB));
}


void MainWindow::on_pushButton_movieUpdateSelected_clicked()
{
    newQueries.updateMovieInLibrary(DB, ui->tableView_Movies,
                                    ui->lineEdit_MovieTitle->text(),
                                    ui->lineEdit_MovieAuthor->text(),
                                    ui->lineEdit_RentPrice->text());
    qDebug()<<"selected Movie UPDATED";
    ui->tableView_Movies->setModel(newQueries.loadMovieLibraryFromDb(DB));
}


void MainWindow::on_pushButton_UpdateCustomer_clicked()
{
    newQueries.updateCustomerInDb(DB, ui->tableView_Customers,
                                  ui->lineEdit_CustomerName->text(),
                                  ui->lineEdit_CustomerAdress->text(),
                                  ui->lineEdit_PhoneNumber->text());
    qDebug()<<"selected Customer UPDATED";
    ui->tableView_Customers->setModel(newQueries.loadCustomersFromDb(DB));
}


void MainWindow::on_pushButton_updatePaymentInfo_clicked()
{
    newQueries.updatePaymentInDb(DB,ui->tableView_Payments,
                                 ui->lineEdit_PaymentMethod->text(),
                                 ui->checkBox_isPaymentCompleted->isChecked(),
                                 ui->lineEdit_PaymentAmount->text(),
                                 ui->lineEdit_PaymentDeposit->text());
    qDebug()<<"selected Payment UPDATED";
    ui->tableView_Payments->setModel(newQueries.loadPaymentsFromDb(DB));
}


void MainWindow::on_pushButton_connectToDb_clicked()
{
    dbUsername = newLogin->loginUsername;
    dbPassword = newLogin->loginPassword;

    DB = QSqlDatabase::addDatabase("QPSQL", "QtConnection");
        DB.setHostName("localhost");
        DB.setDatabaseName("Kursovaya4sem");
        DB.setUserName(dbUsername);
        DB.setPassword(dbPassword);
        DB.setPort(5432);
        bool ok = DB.open();

    if(DB.open())
    {
        ui->label_ConnectionStatus->setText("Successful connection.");
        qDebug()<<"Database connection OPENED";
    }
    else
    {
        ui->label_ConnectionStatus->setText("Wrong username or password. Restart.");
        DB.close();
    }
}

void MainWindow::on_pushButton_openOrdersReturnsWindow_clicked()
{
    newShopOrdersWindow = new ShopEntriesWindow(this, DB, currentProgramDate);
    newShopOrdersWindow->show();

}

void MainWindow::on_pushButton_setCurrentDate_clicked()
{
    int year = ui->dateEdit->date().year(),
        month = ui->dateEdit->date().month(),
        day = ui->dateEdit->date().day();

    currentProgramDate = QString::number(year) + "-"
                        +QString::number(month)+ "-"
                        +QString::number(day);
    qDebug()<<"Program date set:"<<currentProgramDate;

}


void MainWindow::on_pushButton_openReturnWindow_clicked()
{
    newReturnWindow = new ReturnFormWindow(this, DB, currentProgramDate);
    newReturnWindow->show();
}


void MainWindow::on_pushButton_clicked()
{
    newQueryWindow = new QueryWindow(this, DB, currentProgramDate);
    newQueryWindow->show();

}

