#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "resulttable.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString file_name_1 = "D:/2sem/StudentTableModel/input_1.txt";
    model_1 = new StudentTableModel(file_name_1);
    ui->tableView_1->setModel(model_1);
    ui->tableView_1->setSortingEnabled(true);

    QString file_name_2 = "D:/2sem/StudentTableModel/input_2.txt";
    model_2 = new StudentTableModel(file_name_2);
    ui->tableView_2->setModel(model_2);
    ui->tableView_2->setSortingEnabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_push_btn_union_clicked()
{
    StudentTableModel* model = StudentTableModel::Union(model_1, model_2);
    ResultTable table(model, this);
    table.exec();
}


void MainWindow::on_push_btn_intersection_clicked()
{
    StudentTableModel* model = StudentTableModel::Intersection(model_1, model_2);
    ResultTable table(model, this);
    table.exec();
}


void MainWindow::on_push_btn_difference_clicked()
{
    StudentTableModel* model = StudentTableModel::Difference(model_1, model_2);
    ResultTable table(model, this);
    table.exec();
}

