#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>//Библиотека для работы с БД
#include <QtSql/QSqlError>//Библиотка для выявления ошибок БД
#include <QtSql/QSqlTableModel>//Библиотека для передставления Таблиц бд


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnAdd_clicked();

    void on_btnRemove_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;//переменная для работы с бд
    QSqlTableModel *model;//переменная для работы с таблицей

    int currentRow;//переменная будет хранить номерт текущей строки
};
#endif // MAINWINDOW_H
