#ifndef EMPLOYEEDETAILSWINDOW_H
#define EMPLOYEEDETAILSWINDOW_H

#include <QMainWindow>
#include "employeedao.h"
#include "employeeutils.h"
namespace Ui {
class EmployeeDetailsWindow;
}

class EmployeeDetailsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit EmployeeDetailsWindow(QWidget *parent = 0, EmployeeDAO *dao = 0 , long id= 0);
    ~EmployeeDetailsWindow();
    void addWidgets();
    void registerEvents();


private:
    Ui::EmployeeDetailsWindow *ui;
    EmployeeDAO *dao;
    long id;
    EmployeeUtils utils;
};

#endif // EMPLOYEEDETAILSWINDOW_H
