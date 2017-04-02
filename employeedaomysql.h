#ifndef EMPLOYEEDAOMYSQL_H
#define EMPLOYEEDAOMYSQL_H
#include "employeedao.h"
#include <QtSql>
#include <QString>
#include <QTextStream>
#include <iostream>
#include <memory>

using namespace std;

class EmployeeDAOMysql:public EmployeeDAO
{
public:
    EmployeeDAOMysql();
    void save(shared_ptr<Employee> employee);
    void update(long id , shared_ptr<Employee> newEmp);
    void remove(long id);
    shared_ptr<Employee> findById(long id);
    QVector<shared_ptr<Employee>> findAll();
     void connect() ;
     void disconnect();
     void createTableIfNotExists();
     //void dropTable();
public:
    QSqlDatabase *db ;
    QSqlQuery *query ;
    const QString DRIVER_NAME = "QMYSQL3";
    const QString HOSTNAME = "localhost";
    const int PORT = 3306 ;
    const QString USERNAME = "root";
    const QString PASSWORD = "";
    const QString DB_NAME = "test";
    const QString TABLE_NAME = "employees";
};


class EmployeeMapper {
public:
     static shared_ptr<Employee> mapQueryToEmployee(QSqlQuery *query);
};

#endif // EMPLOYEEDAOMYSQL_H
