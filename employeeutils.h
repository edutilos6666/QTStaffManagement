#ifndef EMPLOYEEUTILS_H
#define EMPLOYEEUTILS_H

#include <QRegExp>
#include <QString>
#include <QStringList>
#include <QVector>
#include <iostream>
#include <memory>
#include <QTextStream>
#include "employee.h"
#include <QStandardItemModel>

using namespace std;
class EmployeeUtils
{
public:
    EmployeeUtils();
    bool verifyFields(QString &errorMsg, QStringList &fields, QVector<shared_ptr<Employee>> &employees, bool isAdd) ;
    shared_ptr<Employee> convertFieldsToEmployee(QStringList &fields);
    QStringList convertEmployeeToFields(shared_ptr<Employee> &employee);
     void fillEmployeeModel(QStandardItemModel *employeeModel, QVector<shared_ptr<Employee>> &all);
};

#endif // EMPLOYEEUTILS_H
