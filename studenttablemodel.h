#ifndef STUDENTTABLEMODEL_H
#define STUDENTTABLEMODEL_H

#include <QMainWindow>
#include <QAbstractTableModel>
#include "student.h"

class StudentTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    StudentTableModel(QObject *parent = nullptr);
    StudentTableModel(const QString& file_name, QObject *parent = nullptr);
    StudentTableModel(const QVector<Student>& _students, QObject *parent = nullptr);

    virtual int rowCount(const QModelIndex &parent) const override;
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    virtual bool insertRows(int row, int count, const QModelIndex &parent) override;
    virtual void sort(int column, Qt::SortOrder order) override;

    static StudentTableModel* Union(StudentTableModel* model_1, StudentTableModel* model_2);
    static StudentTableModel* Intersection(StudentTableModel* model_1, StudentTableModel* model_2);
    static StudentTableModel* Difference(StudentTableModel* model_1, StudentTableModel* model_2);
protected:
    QVector<Student> students;
};

#endif // STUDENTTABLEMODEL_H
