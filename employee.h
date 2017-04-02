#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QString>
#include <QDebug>
#include <QTextStream>

/*
 *  id, name, age, address, role and salary
 * */
class Employee
{
public:
    Employee(long id, QString name, int age, QString address, QString role, double salary);
    Employee();
    ~Employee();
    QString toString() const;
public:
  long id;
  QString name;
  int age;
  QString address ;
  QString role ;
  double salary ;
};

#endif // EMPLOYEE_H
