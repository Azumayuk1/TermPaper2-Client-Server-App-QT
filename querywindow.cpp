#include "querywindow.h"
#include "ui_querywindow.h"

QueryWindow::QueryWindow(QWidget *parent, QSqlDatabase DB,QString ReturnDate) :
    QDialog(parent),
    ui(new Ui::QueryWindow)
{
    ui->setupUi(this);
    this->DB = DB;
    this->ReturnDate = ReturnDate;
}

QueryWindow::~QueryWindow()
{
    delete ui;
}

void QueryWindow::on_pushButton_queryCASE_clicked()
{
    ui->tableView->setModel(newQueries.queryCASE(DB));
}


void QueryWindow::on_pushButton_clicked()
{
    ui->tableView->setModel(newQueries.queryMultitableVIEW(DB));
}


void QueryWindow::on_pushButton_2_clicked()
{
    ui->tableView->setModel(newQueries.querySubquerySelect(DB));
}


void QueryWindow::on_pushButton_corrsubq1_clicked()
{
    ui->tableView->setModel(newQueries.queryCorrelatedSQ1(DB));
}


void QueryWindow::on_pushButton_corrsubq2_clicked()
{
    ui->tableView->setModel(newQueries.queryCorrelatedSQ2(DB));
}


void QueryWindow::on_pushButton_corrsubq3_clicked()
{
    ui->tableView->setModel(newQueries.queryCorrelatedSQ3(DB));
}


void QueryWindow::on_pushButton_anyall_clicked()
{
    ui->tableView->setModel(newQueries.queryAnyAllView(DB));
}


void QueryWindow::on_pushButton_queryHaving_clicked()
{
    ui->tableView->setModel(newQueries.queryHaving(DB));
}


void QueryWindow::on_pushButton_queryScalar_clicked()
{
    ui->tableView->setModel(newQueries.queryScalarFunc_TotalOrders(DB));
}


void QueryWindow::on_pushButton_queryVector_clicked()
{
    QString searchDate = ui->lineEdit_date->text();
    ui->tableView->setModel(newQueries.queryVectorFunc_OrdersByDate(DB, searchDate));
}

