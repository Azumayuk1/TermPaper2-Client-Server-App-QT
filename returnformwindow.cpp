#include "returnformwindow.h"
#include "ui_returnformwindow.h"

ReturnFormWindow::ReturnFormWindow(QWidget *parent, QSqlDatabase DB ,QString ReturnDate) :
    QDialog(parent),
    ui(new Ui::ReturnFormWindow)
{
    ui->setupUi(this);
    this->DB = DB;
    this->ReturnDate = ReturnDate;

    ui->tableView_Orders->setModel(returnQueries.loadOrdersFromDb(this->DB));
    ui->tableView_Returns->setModel(returnQueries.loadReturnsFromDb(this->DB));
}

ReturnFormWindow::~ReturnFormWindow()
{
    delete ui;
}

void ReturnFormWindow::on_pushButton_clicked()
{
    returnQueries.createNewReturn(DB, ui->tableView_Orders, ReturnDate);
    ui->tableView_Returns->setModel(returnQueries.loadReturnsFromDb(this->DB));
}


void ReturnFormWindow::on_pushButton_deleteOrder_clicked()
{
    returnQueries.deleteOrderFromDb(DB, ui->tableView_Orders);
    ui->tableView_Orders->setModel(returnQueries.loadOrdersFromDb(this->DB));

}


void ReturnFormWindow::on_pushButton_deleteReturn_clicked()
{
    returnQueries.deleteReturnFromDb(DB, ui->tableView_Returns);
    ui->tableView_Returns->setModel(returnQueries.loadReturnsFromDb(this->DB));
}

