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
        //model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        model->select();//Запросили данные
        ui->tableView->setModel(model);//Передали модель в табличное представление

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

