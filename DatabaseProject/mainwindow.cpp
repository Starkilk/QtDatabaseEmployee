#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)//КОНСТРУКТОР
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Связали БД с проектом
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setDatabaseName("learnfirst");
    db.setHostName("localhost");
    db.setUserName("postgres");
    db.setPassword("22813376914Sql");
    ///

    //Проверка на открытие БД
    if(db.open()){
        ui->statusbar->showMessage("Success"  + db.databaseName());

        model = new QSqlTableModel(this, db);//Связали модель с БД
        model->setTable("users");//Указали какую таблицу присваиваем
        model->select();//Запросили данные

        //Меняем названия столбцов
        model->setHeaderData(1, Qt::Horizontal, "Фамилия", Qt::DisplayRole);
        model->setHeaderData(2, Qt::Horizontal, "Имя", Qt::DisplayRole);
        model->setHeaderData(3, Qt::Horizontal, "Отчество", Qt::DisplayRole);
        model->setHeaderData(4, Qt::Horizontal, "Подразделение", Qt::DisplayRole);
        ///

        ui->tableView->setModel(model);//Передали модель в табличное представление
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);//выравнивание таблицы по содержимому
        ui->tableView->setColumnHidden(0, true);//спрятали стольбец "id"
        ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//ВЫДЕЛЕНИЕ СТРОКИ целеком
        ui->tableView->setSortingEnabled(true);

    }else{
        ui->statusbar->showMessage("Error..." + db.lastError().databaseText());
    }
    ///

}

MainWindow::~MainWindow()
{
    delete ui;
}

//Кнопка добавить User(а)
void MainWindow::on_btnAdd_clicked()
{
    model->insertRow(model->rowCount());//Метод добавления строки в таблицу(передаём ко-во строк таблицы)
}

//Кнопка удаления User(а)
void MainWindow::on_btnRemove_clicked()
{
    model->removeRow(currentRow);//Удаляем сточку
    model->select();
}

//Слушатель нажатия на элементы таблицы
void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    currentRow = index.row();//Сохраняем в переменную номер строки, на которую нажали
}

//Кнопка обновить User(ов)
void MainWindow::on_btnRefrash_clicked()
{
    model->select();
    ui->tableView->selectRow(currentRow);//после обновления оставляем выделение на выбраной строке
}

