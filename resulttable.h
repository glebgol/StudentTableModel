#ifndef RESULTTABLE_H
#define RESULTTABLE_H

#include "studenttablemodel.h"
#include <QDialog>

namespace Ui {
class ResultTable;
}

class ResultTable : public QDialog
{
    Q_OBJECT

public:
    explicit ResultTable(QWidget *parent = nullptr);
    ResultTable(StudentTableModel* model, QWidget *parent = nullptr);
    ~ResultTable();

private:
    Ui::ResultTable *ui;
};

#endif // RESULTTABLE_H
