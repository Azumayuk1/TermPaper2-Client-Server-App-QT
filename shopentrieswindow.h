#ifndef SHOPENTRIESWINDOW_H
#define SHOPENTRIESWINDOW_H

#include <QDialog>
#include "dbsqlqueries.h"

namespace Ui {
class ShopEntriesWindow;
}

class ShopEntriesWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ShopEntriesWindow(QWidget *parent = nullptr, QSqlDatabase DB = QSqlDatabase(),QString OrderDate = "2022-03-02");
    ~ShopEntriesWindow();
    QSqlDatabase DB;
    dbSqlQueries orderQueries;
    QString OrderDate;
    int daysRented;

private slots:
    void on_pushButton_pConfirm_clicked();

    void on_pushButton_finishOrder_clicked();

    void on_tableView_orderSelectMovie_clicked(const QModelIndex &index);

private:
    Ui::ShopEntriesWindow *ui;
};

#endif // SHOPENTRIESWINDOW_H
