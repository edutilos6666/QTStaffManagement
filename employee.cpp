#include "employee.h"

Employee::Employee(long id, QString name, int age, QString address, QString role, double salary):
    id(id), name(name), age(age), address(address), role(role), salary(salary)
{

}

Employee::Employee():
     id(0), name(""), age(0), address(""), role(""), salary(0)
{

}

Employee::~Employee()
{
   qDebug() << "Employee instance was destroyed.";
}

QString Employee::toString() const
{
   QString str ;
   QTextStream out(&str);
   out << "[" << id << ", " << name << ", " << age << ", " << address << ", " << role << ", " << salary << "]";
   return str ;
}
