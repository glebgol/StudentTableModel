#include "student.h"

Student::Student()
{
    name = "___";
    num = 0;
    grade = 0.0;
    group = 0;
}

Student::Student(QString _name, int _num, double _grade, int _group)
{
    name = _name;
    num = _num;
    grade = _grade;
    group = _group;
}

bool operator<(const Student& a, const Student b) {
    return a.num < b.num;
}

bool operator>(const Student& a, const Student b) {
    return a.num > b.num;
}

bool operator==(const Student& a, const Student b) {
    return a.num == b.num;
}
