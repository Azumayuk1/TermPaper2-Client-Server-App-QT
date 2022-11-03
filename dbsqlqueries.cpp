#include "dbsqlqueries.h"

dbSqlQueries::dbSqlQueries()
{

}

QString dbSqlQueries::FetchIDSelectedInTable(QTableView *tableview)
{
    return QString("%1").arg(tableview
                             ->model()
                             ->data(tableview
                             ->model()
                             ->index(tableview->
                             currentIndex().row(),0)).toInt());
}

QSqlQueryModel* dbSqlQueries::loadMovieLibraryFromDb(QSqlDatabase db)
{

    QSqlQueryModel *modelMovies = new QSqlQueryModel();
    QSqlQuery *query = new QSqlQuery(db);

    query->prepare("SELECT * FROM public.Movies");
    query->exec();
    modelMovies->setQuery(std::move(*query));
    delete query;

    //qDebug() << (modelMovies->rowCount());
    return modelMovies;
}

void dbSqlQueries::addNewMovieToLibrary(QSqlDatabase db, QString mTitle, QString mAuthor, QString mCost)
{
    QSqlQuery *query = new QSqlQuery(db);
    query->exec("SELECT public.add_movie('"+ mTitle +"','"+ mAuthor +"','"+ mCost +"');");
}

void dbSqlQueries::deleteMovieFromLibrary(QSqlDatabase db, QTableView *tableview)
{
    QSqlQuery *query = new QSqlQuery(db);
    query->exec("SELECT public.delete_movie("+ FetchIDSelectedInTable(tableview) +");");
}

void dbSqlQueries::updateMovieInLibrary(QSqlDatabase db, QTableView *tableview, QString mTitle, QString mAuthor, QString mCost)
{
    QString FetchedID = FetchIDSelectedInTable(tableview);
    QSqlQuery *query = new QSqlQuery(db);
    query->exec("SELECT public.update_movie('"+ FetchedID +"','"+ mTitle +"','"+ mAuthor +"','"+ mCost +"')");
}

float dbSqlQueries::selectMoviePrice(QSqlDatabase db, QTableView *tableview)
{
    float priceValue;
    QString FetchedID = FetchIDSelectedInTable(tableview);
    //qDebug() << "MovieID"<<FetchedID;

    QSqlQuery *query = new QSqlQuery(db);
    query->prepare("SELECT rentcostperday FROM public.Movies WHERE movieid = :movieid");
    query->bindValue(":movieid", FetchedID);
    query->exec();
    qDebug()<<query->size();

    query->next();
    priceValue = query->value(0).toFloat();

    //qDebug() <<"Selected price:"<< priceValue;
    return priceValue;
}

QSqlQueryModel *dbSqlQueries::loadCustomersFromDb(QSqlDatabase db)
{
    QSqlQueryModel *modelCustomers = new QSqlQueryModel();
    QSqlQuery *query = new QSqlQuery(db);

    query->prepare("SELECT * FROM public.Customers");//
    query->exec();
    modelCustomers->setQuery(std::move(*query));
    delete query;

    //qDebug() << (modelCustomers->rowCount());
    return modelCustomers;
}

void dbSqlQueries::addNewCustomerToDb(QSqlDatabase db, QString cName, QString cAdress, QString cPhoneNumber)
{
    QSqlQuery *queryAddC = new QSqlQuery(db);

    queryAddC->exec("SELECT public.add_customer('"+ cName +"','"+ cAdress +"','"+ cPhoneNumber +"');");
}

void dbSqlQueries::deleteCustomerFromDb(QSqlDatabase db, QTableView *tableview)
{
    QSqlQuery *query = new QSqlQuery(db);
    query->exec("SELECT public.delete_customer("+ FetchIDSelectedInTable(tableview) +");");
}

void dbSqlQueries::updateCustomerInDb(QSqlDatabase db, QTableView *tableview, QString cName, QString cAdress, QString cPhoneNumber)
{
    QString FetchedID = FetchIDSelectedInTable(tableview);
    QSqlQuery *query = new QSqlQuery(db);
    query->exec("SELECT public.update_customer('"+ FetchedID +"','"+ cName +"','"+ cAdress +"','"+ cPhoneNumber +"')");
}

QSqlQueryModel *dbSqlQueries::loadPaymentsFromDb(QSqlDatabase db)
{
    QSqlQueryModel *modelPayments = new QSqlQueryModel();
    QSqlQuery *query = new QSqlQuery(db);

    query->prepare("SELECT * FROM public.Payments");//
    query->exec();
    modelPayments->setQuery(std::move(*query));
    delete query;

    //qDebug() << (modelPayments->rowCount());
    return modelPayments;

}

void dbSqlQueries::addNewPaymentToDb(QSqlDatabase db, QString pMethodName, bool pIsCompleted, QString pAmount, QString pDeposit)
{
    QSqlQuery *queryAddC = new QSqlQuery(db);
    QString pIsCompletedString;
    if(pIsCompleted == true){pIsCompletedString = "true";}
    else{pIsCompletedString = "false";}

    queryAddC->exec("SELECT public.add_payment('"+ pMethodName +"','"+ pIsCompletedString +"','"+ pAmount +"','" + pDeposit + "');");
}

void dbSqlQueries::addNewPaymentToDbTRANSACTION(QSqlDatabase db, QString pMethodName, bool pIsCompleted, QString pAmount, QString pDeposit)
{
    QSqlQuery *queryAddC = new QSqlQuery(db);
    QString pIsCompletedString;
    if(pIsCompleted == true){pIsCompletedString = "true";}
    else{pIsCompletedString = "false";}

    queryAddC->exec(QString("CALL public.add_payment_transact('%1','%2','%3','%4');").arg(pMethodName).arg(pIsCompleted).arg(pAmount).arg(pDeposit));

}

void dbSqlQueries::deletePaymentFromDb(QSqlDatabase db, QTableView *tableview)
{
    QSqlQuery *query = new QSqlQuery(db);
    query->exec("SELECT public.delete_payment("+ FetchIDSelectedInTable(tableview)+");");
}

void dbSqlQueries::updatePaymentInDb(QSqlDatabase db, QTableView *tableview, QString pMethodName, bool pIsCompleted, QString pAmount, QString pDeposit)
{
    QString FetchedID = FetchIDSelectedInTable(tableview);
    QString pIsCompletedString;
    if(pIsCompleted == true){pIsCompletedString = "true";}
    else{pIsCompletedString = "false";}
    QSqlQuery *query = new QSqlQuery(db);
    query->exec("SELECT public.update_payment('"+ FetchedID +"','"+ pMethodName +"','"+ pIsCompletedString +"','"+ pAmount +"','"+ pDeposit +"')");
}

void dbSqlQueries::createNewOrder(QSqlDatabase db, QTableView *tableview_Customer,
                                  QTableView *tableview_Movie, QTableView *tableview_Payment,
                                  QString dateCreation, QString daysRented)
{
    QString FetchedCustomerID = FetchIDSelectedInTable(tableview_Customer);
    QString FetchedMovieID = FetchIDSelectedInTable(tableview_Movie);
    QString FetchedPaymentID = FetchIDSelectedInTable(tableview_Payment);

    QSqlQuery *query = new QSqlQuery(db);
    query->exec("SELECT public.add_order('"+dateCreation+"','"+daysRented+"','"+ "false" +"','"+FetchedCustomerID+"','"+FetchedMovieID+"','"+FetchedPaymentID+"')");
}

void dbSqlQueries::deleteOrderFromDb(QSqlDatabase db, QTableView *tableview)
{
    QSqlQuery *query = new QSqlQuery(db);
    query->exec("SELECT public.delete_order("+ FetchIDSelectedInTable(tableview)+");");
}

QSqlQueryModel *dbSqlQueries::loadOrdersFromDb(QSqlDatabase db)
{
    QSqlQueryModel *modelOrders = new QSqlQueryModel();
    QSqlQuery *query = new QSqlQuery(db);

    query->prepare("SELECT * FROM public.shoporders");//
    query->exec();
    modelOrders->setQuery(std::move(*query));
    delete query;

    return modelOrders;

}

QSqlQueryModel *dbSqlQueries::loadReturnsFromDb(QSqlDatabase db)
{
    QSqlQueryModel *modelReturns = new QSqlQueryModel();
    QSqlQuery *query = new QSqlQuery(db);

    query->prepare("SELECT * FROM public.shopreturns");//
    query->exec();
    modelReturns->setQuery(std::move(*query));
    delete query;

    return modelReturns;
}

void dbSqlQueries::createNewReturn(QSqlDatabase db, QTableView *tableview_Orders, QString dateCreation)
{
    QString FetchedOrderID = FetchIDSelectedInTable(tableview_Orders);
    QSqlQuery *query = new QSqlQuery(db);
    query->exec("SELECT public.add_return('"+dateCreation+"','"+FetchedOrderID+"')");
}

void dbSqlQueries::deleteReturnFromDb(QSqlDatabase db, QTableView *tableview)
{
    QSqlQuery *query = new QSqlQuery(db);
    query->exec("SELECT public.delete_return("+ FetchIDSelectedInTable(tableview)+");");
}

QSqlQueryModel *dbSqlQueries::queryCASE(QSqlDatabase db)
{
    QSqlQueryModel *modelCASE = new QSqlQueryModel();
    QSqlQuery *query = new QSqlQuery(db);

    query->exec("SELECT * FROM public.casequeryview;");
    modelCASE->setQuery(std::move(*query));
    delete query;

    return modelCASE;
}

QSqlQueryModel *dbSqlQueries::queryMultitableVIEW(QSqlDatabase db)
{
    QSqlQueryModel *modelVIEW = new QSqlQueryModel();
    QSqlQuery *query = new QSqlQuery(db);

    query->exec("SELECT * FROM public.multitableview;");
    modelVIEW->setQuery(std::move(*query));
    delete query;

    return modelVIEW;
}

QSqlQueryModel *dbSqlQueries::querySubquerySelect(QSqlDatabase db)
{
    QSqlQueryModel *modelVIEW = new QSqlQueryModel();
        QSqlQuery *query = new QSqlQuery(db);

        query->exec("SELECT * FROM public.subqueryselect;");
        modelVIEW->setQuery(std::move(*query));
        delete query;

        return modelVIEW;
}

QSqlQueryModel *dbSqlQueries::queryCorrelatedSQ1(QSqlDatabase db)
{
    QSqlQueryModel *modelVIEW = new QSqlQueryModel();
        QSqlQuery *query = new QSqlQuery(db);

        query->exec("SELECT * FROM public.corrsubq1;");
        modelVIEW->setQuery(std::move(*query));
        delete query;

        return modelVIEW;
}

QSqlQueryModel *dbSqlQueries::queryCorrelatedSQ2(QSqlDatabase db)
{
    QSqlQueryModel *modelVIEW = new QSqlQueryModel();
        QSqlQuery *query = new QSqlQuery(db);

        query->exec("SELECT * FROM public.corrsubq2;");
        modelVIEW->setQuery(std::move(*query));
        delete query;

        return modelVIEW;
}

QSqlQueryModel *dbSqlQueries::queryCorrelatedSQ3(QSqlDatabase db)
{
    QSqlQueryModel *modelVIEW = new QSqlQueryModel();
        QSqlQuery *query = new QSqlQuery(db);

        query->exec("SELECT * FROM public.corrsubq3;");
        modelVIEW->setQuery(std::move(*query));
        delete query;

        return modelVIEW;
}

QSqlQueryModel *dbSqlQueries::queryAnyAllView(QSqlDatabase db)
{
    QSqlQueryModel *modelVIEW = new QSqlQueryModel();
        QSqlQuery *query = new QSqlQuery(db);

        query->exec("SELECT * FROM public.antallview;");
        modelVIEW->setQuery(std::move(*query));
        delete query;

        return modelVIEW;

}

QSqlQueryModel *dbSqlQueries::queryHaving(QSqlDatabase db)
{
    QSqlQueryModel *modelVIEW = new QSqlQueryModel();
    QSqlQuery *query = new QSqlQuery(db);

    query->exec("SELECT (SELECT COUNT(orderid) FROM public.shoporders), COUNT(customerid), adress FROM public.customers GROUP BY adress HAVING COUNT(customerid) > 2;");
    modelVIEW->setQuery(std::move(*query));
    delete query;

    return modelVIEW;

}

QSqlQueryModel *dbSqlQueries::queryScalarFunc_TotalOrders(QSqlDatabase db)
{
    QSqlQueryModel *modelVIEW = new QSqlQueryModel();
        QSqlQuery *query = new QSqlQuery(db);

        query->exec("SELECT * FROM public.total_orders();");
        modelVIEW->setQuery(std::move(*query));
        delete query;

        return modelVIEW;

}

QSqlQueryModel *dbSqlQueries::queryVectorFunc_OrdersByDate(QSqlDatabase db, QString date)
{
    QSqlQueryModel *modelVIEW = new QSqlQueryModel();
        QSqlQuery *query = new QSqlQuery(db);

        query->exec(QString("SELECT * FROM public.orders_by_date('%1')").arg(date));
        modelVIEW->setQuery(std::move(*query));
        delete query;

        return modelVIEW;
}
