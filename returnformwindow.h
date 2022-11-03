#ifndef RETURNFORMWINDOW_H
#define RETURNFORMWINDOW_H

#include "dbsqlqueries.h"
#include "qsqldatabase.h"
#include <QDialog>

namespace Ui {
class ReturnFormWindow;
}

class ReturnFormWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ReturnFormWindow(QWidget *parent = nullptr, QSqlDatabase DB = QSqlDatabase(),QString ReturnDate = "2022-03-02");
    ~ReturnFormWindow();
    QSqlDatabase DB;
    dbSqlQueries returnQueries;
    QString ReturnDate;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_deleteOrder_clicked();

    void on_pushButton_deleteReturn_clicked();

private:
    Ui::ReturnFormWindow *ui;
};

#endif // RETURNFORMWINDOW_H
