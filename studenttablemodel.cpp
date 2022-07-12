#include "studenttablemodel.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

StudentTableModel::StudentTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    students << Student("Vanya", 101, 11, 8)
             << Student("Gleb", 100, 10, 7);
}

StudentTableModel::StudentTableModel(const QString& file_name, QObject *parent)
    : QAbstractTableModel(parent)
{
    QFile file(file_name);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "File : " << file.fileName() << " isn't open!!!";
    }

    QTextStream in(&file);
    in.setCodec("UTF-8");

    Student temp;
    while (!in.atEnd()) {
        in >> temp.num >> temp.name >> temp.group >> temp.grade;
        if (temp.name != "") {
            students.push_back(temp);
        }
    }
}

StudentTableModel::StudentTableModel(const QVector<Student>& _students, QObject *parent)
    : QAbstractTableModel(parent)
{
    students = _students;
}

int StudentTableModel::rowCount(const QModelIndex &/*parent*/) const
{
    return students.count();
}

int StudentTableModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 4;
}

QVariant StudentTableModel::data(const QModelIndex &index, int role) const
{
    if(role != Qt::DisplayRole)
    {
        return QVariant();
    }
    switch(index.column())
    {
    case 0: return students[index.row()].num;
    case 1: return students[index.row()].name;
    case 2: return students[index.row()].group;
    case 3: return students[index.row()].grade;
    default: return QVariant();
    }

    return QVariant();
}


QVariant StudentTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
    {
        return QVariant();
    }

    if(orientation == Qt::Horizontal)
    {
        switch(section)
        {
        case 0: return tr("Номер зачетки");
        case 1: return tr("Имя");
        case 2: return tr("Номер Группы");
        case 3: return tr("Средний балл");
        default: return QVariant();
        }
    }
    else
    {
        return QString("%1").arg(section + 1);
    }
}

bool StudentTableModel::insertRows(int position, int rows, const QModelIndex& /*parent*/)
{
    beginInsertRows(QModelIndex(), position, position+rows-1);

    for (int row = 0; row < rows; row++) {
        students.insert(position, Student());
    }

    endInsertRows();
    return true;
}

void StudentTableModel::sort(int column, Qt::SortOrder order)
{
    emit layoutAboutToBeChanged();
    if (order == Qt::AscendingOrder) {
        switch(column) {
        case 0: std::sort(students.begin(), students.end(), [](const Student& a, const Student& b){
                return a.num < b.num;
            });
            break;
        case 1: std::sort(students.begin(), students.end(), [](const Student& a, const Student& b){
                return a.name < b.name;
            });
            break;
        case 2: std::sort(students.begin(), students.end(), [](const Student& a, const Student& b){
                return a.group < b.group;
            });
            break;
        case 3: std::sort(students.begin(), students.end(), [](const Student& a, const Student& b){
                return a.grade < b.grade;
            });
            break;
        }
    }
    else {
        switch(column) {
        case 0: std::sort(students.begin(), students.end(), [](const Student& a, const Student& b){
                return a.num > b.num;
            });
            break;
        case 1: std::sort(students.begin(), students.end(), [](const Student& a, const Student& b){
                return a.name > b.name;
            });
            break;
        case 2: std::sort(students.begin(), students.end(), [](const Student& a, const Student& b){
                return a.group > b.group;
            });
            break;
        case 3: std::sort(students.begin(), students.end(), [](const Student& a, const Student& b){
                return a.grade > b.grade;
            });
            break;
        }
    }
    emit layoutChanged();
}

StudentTableModel* StudentTableModel::Union(StudentTableModel* model_1, StudentTableModel* model_2)
{
    QVector<Student> first(model_1->students);
    QVector<Student> second(model_2->students);

    QVector<Student> result;
    std::sort(first.begin(), first.end());
    std::sort(second.begin(), second.end());

    int i = 0, j = 0;
    while (i < first.count() && j < second.count()) {
        if (first[i] < second[j]) {
            result << first[i++];
        }
        else if (first[i] > second[j]) {
            result << second[j++];
        }
        else {
            result << first[i++];
            j++;
        }
    }
    while (i < first.count()) {
        result << first[i++];
    }
    while (j < second.count()) {
        result << second[j++];
    }
    return new StudentTableModel(result);
}

StudentTableModel* StudentTableModel::Intersection(StudentTableModel* model_1, StudentTableModel* model_2)
{
    QVector<Student> first(model_1->students);
    QVector<Student> second(model_2->students);

    QVector<Student> result;
    std::sort(first.begin(), first.end());
    std::sort(second.begin(), second.end());

    int i = 0, j = 0;
    while (i < first.count() && j < second.count()) {
        if (first[i] == second[j]) {
            result << first[i++];
            j++;
        }
        else if (first[i] > second[j]) {
           j++;
        }
        else {
            i++;
        }
    }
    return new StudentTableModel(result);
}

StudentTableModel* StudentTableModel::Difference(StudentTableModel* model_1, StudentTableModel* model_2)
{
    QVector<Student> first(model_1->students);
    QVector<Student> second(model_2->students);

    QVector<Student> result;
    std::sort(first.begin(), first.end());
    std::sort(second.begin(), second.end());

    int i = 0, j = 0;
    while (i < first.count() && j < second.count()) {
        if (first[i] == second[j]) {
            i++;
            j++;
        }
        else if (first[i] > second[j]) {
            j++;
        }
        else {
            result << first[i++];
        }
    }
    while (i < first.count()) {
        result << first[i++];
    }
    return new StudentTableModel(result);
}
