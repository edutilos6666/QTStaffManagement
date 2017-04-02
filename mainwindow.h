#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "employeedao.h"
#include <QStandardItemModel>
#include <QStandardItem>
#include <QDebug>
#include <iostream>
#include <string>
#include <memory>
#include "employeeaddwindow.h"
#include "employeeupdatewindow.h"
#include "employeedetailswindow.h"
#include <QItemSelectionModel>
#include "employeeutils.h"
#include <QLabel>
//#include <QtCharts/QChartView>
//#include <QtCharts/QPieSeries>
//#include <QtCharts/QPieSlice>
//#include <QtCharts/QChart>
#include <QVBoxLayout>
#include <QtCharts>
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0, EmployeeDAO *dao= 0);
    ~MainWindow();
    void addWidgets();
     void registerEvents();
    long getSelectedEmployeeId();


 signals:
     void completed();

public slots:
     void onAddEmployee();
     void onUpdateEmployee();
     void onRemoveEmployee();
     void onEmployeeDetails();
     void onPieCharts();
    // void fillEmployeeModel();
private:
    Ui::MainWindow *ui;
    QStandardItemModel *employeeModel;
    EmployeeDAO *dao;
    EmployeeUtils utils;
};

#endif // MAINWINDOW_H
