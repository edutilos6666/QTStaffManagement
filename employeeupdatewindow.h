#ifndef EMPLOYEEUPDATEWINDOW_H
#define EMPLOYEEUPDATEWINDOW_H

#include <QMainWindow>
#include "employeedao.h"
#include <QStandardItemModel>
#include "employeeutils.h"
#include <QMessageBox>

namespace Ui {
class EmployeeUpdateWindow;
}

class EmployeeUpdateWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit EmployeeUpdateWindow(QWidget *parent = 0, EmployeeDAO *dao = 0, long id = 0, QStandardItemModel *employeeModel= 0);
    ~EmployeeUpdateWindow();
   void addWidgets();
   void registerEvents();

public slots:
   void onUpdate();
   void onCancel();

private:
    Ui::EmployeeUpdateWindow *ui;
    EmployeeDAO *dao;
    long id;
    QStandardItemModel *employeeModel;
    EmployeeUtils utils;
};

#endif // EMPLOYEEUPDATEWINDOW_H
