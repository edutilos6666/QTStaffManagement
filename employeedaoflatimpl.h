#ifndef EMPLOYEEDAOFLATIMPL_H
#define EMPLOYEEDAOFLATIMPL_H

#include "employeedao.h"
#include <QString>
#include <QMap>
#include <QFile>
#include <QRegExp>
class EmployeeDAOFlatImpl: public EmployeeDAO
{
public:
    EmployeeDAOFlatImpl(QString fileName);
    ~EmployeeDAOFlatImpl();
    void save(shared_ptr<Employee> employee) ;
    void update(long id , shared_ptr<Employee> newEmp) ;
    void remove(long id) ;
    shared_ptr<Employee> findById(long id) ;
    QVector<shared_ptr<Employee>> findAll();
    void finalize();
    void readFromFile();

public:
    QString fileName;
    QMap<long , shared_ptr<Employee>> employeeMap;
};

#endif // EMPLOYEEDAOFLATIMPL_H
