#ifndef QUERYWINDOW_H
#define QUERYWINDOW_H

#include "qsqldatabase.h"
#include "ui_querywindow.h"
#include "dbsqlqueries.h"
#include <QDialog>

namespace Ui {
class QueryWindow;
}

class QueryWindow : public QDialog
{
    Q_OBJECT

public:
    explicit QueryWindow(QWidget *parent = nullptr, QSqlDatabase DB = QSqlDatabase(),QString ReturnDate = "2022-03-02");
    ~QueryWindow();
    QSqlDatabase DB;
    dbSqlQueries newQueries;
    QString ReturnDate;

private slots:
    void on_pushButton_queryCASE_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_corrsubq1_clicked();

    void on_pushButton_corrsubq2_clicked();

    void on_pushButton_corrsubq3_clicked();

    void on_pushButton_anyall_clicked();

    void on_pushButton_queryHaving_clicked();

    void on_pushButton_queryScalar_clicked();

    void on_pushButton_queryVector_clicked();

private:
    Ui::QueryWindow *ui;
};

#endif // QUERYWINDOW_H
