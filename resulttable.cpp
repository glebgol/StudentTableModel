#include "resulttable.h"
#include "ui_resulttable.h"

ResultTable::ResultTable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResultTable)
{
    ui->setupUi(this);
}

ResultTable::ResultTable(StudentTableModel* model, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResultTable)
{
    ui->setupUi(this);
    ui->tableView->setModel(model);
    ui->tableView->setSortingEnabled(true);
}

ResultTable::~ResultTable()
{
    delete ui;
}
