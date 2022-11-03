#ifndef DBSQLQUERIES_H
#define DBSQLQUERIES_H

#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlDatabase>

#include "qtableview.h"

class dbSqlQueries : public QSqlQuery
{
public:
    dbSqlQueries();

    QString FetchIDSelectedInTable(QTableView *tableview);

    QSqlQueryModel* loadMovieLibraryFromDb(QSqlDatabase db);
    void addNewMovieToLibrary(QSqlDatabase db, QString mTitle, QString mAuthor, QString mCost);
    void deleteMovieFromLibrary(QSqlDatabase db, QTableView *tableview);
    void updateMovieInLibrary(QSqlDatabase db, QTableView *tableview, QString mTitle, QString mAuthor, QString mCost);
    float selectMoviePrice(QSqlDatabase db, QTableView *tableview);

    QSqlQueryModel* loadCustomersFromDb(QSqlDatabase db);
    void addNewCustomerToDb(QSqlDatabase db, QString cName, QString cAdress, QString cPhoneNumber);
    void deleteCustomerFromDb(QSqlDatabase db, QTableView *tableview);
    void updateCustomerInDb(QSqlDatabase db, QTableView *tableview, QString cName, QString cAdress, QString cPhoneNumber);


    QSqlQueryModel* loadPaymentsFromDb(QSqlDatabase db);
    void addNewPaymentToDb(QSqlDatabase db, QString pMethodName, bool pIsCompleted, QString pAmount, QString pDeposit);
    void addNewPaymentToDbTRANSACTION(QSqlDatabase db, QString pMethodName, bool pIsCompleted, QString pAmount, QString pDeposit);
    void deletePaymentFromDb(QSqlDatabase db, QTableView *tableview);
    void updatePaymentInDb(QSqlDatabase db, QTableView *tableview, QString pMethodName, bool pIsCompleted, QString pAmount, QString pDeposit);


    QSqlQueryModel* loadOrdersFromDb(QSqlDatabase db);
    void createNewOrder(QSqlDatabase db, QTableView *tableview_Customer, QTableView *tableview_Movie, QTableView *tableview_Payment,
                        QString dateCreation, QString daysRented);
    void deleteOrderFromDb(QSqlDatabase db, QTableView *tableview);

    QSqlQueryModel* loadReturnsFromDb(QSqlDatabase db);
    void createNewReturn(QSqlDatabase db, QTableView *tableview_Orders, QString dateCreation);
    void deleteReturnFromDb(QSqlDatabase db, QTableView *tableview);

    QSqlQueryModel* queryCASE(QSqlDatabase db);
    QSqlQueryModel* queryMultitableVIEW(QSqlDatabase db);
    QSqlQueryModel* querySubquerySelect(QSqlDatabase db);
    QSqlQueryModel* queryCorrelatedSQ1(QSqlDatabase db);
    QSqlQueryModel* queryCorrelatedSQ2(QSqlDatabase db);
    QSqlQueryModel* queryCorrelatedSQ3(QSqlDatabase db);
    QSqlQueryModel* queryAnyAllView(QSqlDatabase db);
    QSqlQueryModel* queryHaving(QSqlDatabase db);
    QSqlQueryModel* queryScalarFunc_TotalOrders(QSqlDatabase db);
    QSqlQueryModel* queryVectorFunc_OrdersByDate(QSqlDatabase db, QString date);
};

#endif // DBSQLQUERIES_H
