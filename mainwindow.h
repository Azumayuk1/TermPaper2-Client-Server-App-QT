#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>

#include "dbsqlqueries.h"
#include "loginform.h"
#include "qdebug.h"
#include "shopentrieswindow.h"
#include "returnformwindow.h"
#include "querywindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    LoginForm *newLogin;
    QSqlDatabase DB;
    dbSqlQueries newQueries;
    ShopEntriesWindow *newShopOrdersWindow;
    ReturnFormWindow *newReturnWindow;
    QueryWindow *newQueryWindow;

    QString currentProgramDate;
    QString dbUsername, dbPassword;


private slots:
    void on_pushButton_LoadMovieLibrary_clicked();

    void on_pushButton_addNewMovie_clicked();

    void on_pushButton_LoadCustomers_clicked();

    void on_pushButton_AddNewCustomer_clicked();

    void on_pushButton_LoadPayments_clicked();

    void on_pushButton_addNewPayment_clicked();

    void on_pushButton_movieDeleteSelected_clicked();

    void on_pushButton_DeleteCustomer_clicked();

    void on_pushButton_deletePayment_clicked();

    void on_pushButton_movieUpdateSelected_clicked();

    void on_pushButton_UpdateCustomer_clicked();

    void on_pushButton_updatePaymentInfo_clicked();

    void on_pushButton_connectToDb_clicked();

    void on_pushButton_openOrdersReturnsWindow_clicked();

    void on_pushButton_setCurrentDate_clicked();

    void on_pushButton_openReturnWindow_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
