#include "shopentrieswindow.h"
#include "ui_shopentrieswindow.h"

ShopEntriesWindow::ShopEntriesWindow(QWidget *parent, QSqlDatabase DB, QString OrderDate) :
    QWidget(parent,Qt::Window),
    ui(new Ui::ShopEntriesWindow)
{
    this->DB = DB;
    this->OrderDate = OrderDate;

    ui->setupUi(this);
    ui->tableView_orderSelectMovie->setModel(orderQueries.loadMovieLibraryFromDb(this->DB));
    ui->tableView_orderSelectCustomer->setModel(orderQueries.loadCustomersFromDb(this->DB));
    ui->tableView_orderSelectPayment->setModel(orderQueries.loadPaymentsFromDb(this->DB));

    int daysRented = ui->spinBox_Days->value();
}

ShopEntriesWindow::~ShopEntriesWindow()
{
    delete ui;
}

void ShopEntriesWindow::on_pushButton_pConfirm_clicked()
{
    orderQueries.addNewPaymentToDbTRANSACTION(DB,ui->lineEdit_pMethod->text(),
                                 ui->checkBox_pIsCompleted->isChecked(),
                                 ui->lineEdit_pAmount->text(),
                                 ui->lineEdit_pDeposit->text());
    ui->tableView_orderSelectPayment->setModel(orderQueries.loadPaymentsFromDb(DB));
    qDebug()<<"New payment ADDED";
}


void ShopEntriesWindow::on_pushButton_finishOrder_clicked()
{
    orderQueries.createNewOrder(DB, ui->tableView_orderSelectCustomer, ui->tableView_orderSelectMovie,
                                ui->tableView_orderSelectPayment, OrderDate,
                                ui->spinBox_Days->text());
    qDebug()<<"New Order CREATED";
}


void ShopEntriesWindow::on_tableView_orderSelectMovie_clicked(const QModelIndex &index)
{
    float fetchedMoviePrice = orderQueries.selectMoviePrice(DB, ui->tableView_orderSelectMovie);
    daysRented = ui->spinBox_Days->value();

    float totalCost = fetchedMoviePrice*daysRented;
    float depositSize = fetchedMoviePrice * 3;

    ui->lineEdit_pAmount->text() = QString::number(totalCost);
    ui->lineEdit_pDeposit->text() = QString::number(depositSize);

}

