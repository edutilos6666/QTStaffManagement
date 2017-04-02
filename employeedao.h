#ifndef EMPLOYEEDAO_H
#define EMPLOYEEDAO_H

#include "employee.h"
#include <memory>
#include <iostream>
#include <QVector>

using namespace std ;
class EmployeeDAO
{
public:
    virtual void save(shared_ptr<Employee> employee) = 0 ;
    virtual void update(long id , shared_ptr<Employee> newEmp) = 0 ;
    virtual void remove(long id) = 0 ;
    virtual shared_ptr<Employee> findById(long id) = 0;
    virtual QVector<shared_ptr<Employee>> findAll() = 0;
};

#endif // EMPLOYEEDAO_H
