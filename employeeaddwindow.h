#ifndef EMPLOYEEADDWINDOW_H
#define EMPLOYEEADDWINDOW_H

#include <QMainWindow>
#include "employeedaoflatimpl.h"
#include "employeeutils.h"
#include <QMessageBox>
#include <QStandardItemModel>
namespace Ui {
class EmployeeAddWindow;
}

class EmployeeAddWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit EmployeeAddWindow(QWidget *parent = 0, EmployeeDAO *dao = 0, QStandardItemModel *employeeModel= 0);
    ~EmployeeAddWindow();
     void addWidgets();
     void registerEvents();
signals:

public slots:
   void onSave();
   void onCancel();

private:
    Ui::EmployeeAddWindow *ui;
    EmployeeDAO *dao;
    EmployeeUtils utils;
    QStandardItemModel *employeeModel;
};

#endif // EMPLOYEEADDWINDOW_H
