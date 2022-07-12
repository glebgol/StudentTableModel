#ifndef STUDENT_H
#define STUDENT_H

#include <QMainWindow>

class Student
{
public:
    QString name;
    int num;
    double grade;
    int group;

    Student();
    Student(QString _name, int _num, double _grade, int _group);

    friend bool operator<(const Student& a, const Student b);
    friend bool operator>(const Student& a, const Student b);
    friend bool operator==(const Student& a, const Student b);
};

#endif // STUDENT_H
