#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "studenttablemodel.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_push_btn_union_clicked();

    void on_push_btn_intersection_clicked();

    void on_push_btn_difference_clicked();

private:
    Ui::MainWindow *ui;
    StudentTableModel* model_1;
    StudentTableModel* model_2;
};
#endif // MAINWINDOW_H
