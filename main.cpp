#include "mainwindow.h"
#include <QApplication>
#include "employeedaoflatimpl.h"
#include <QtSql>
#include <QDebug>
#include "employeedaomysql.h"

void testEmployeeDaoFlatImpl()  {
EmployeeDAOFlatImpl impl("employees.txt") ;
// Employee(long id, QString name, int age, QString address, QString role, double salary);
impl.save(make_shared<Employee>(1, "foo", 10 , "Main Street", "FrontEnd", 100.0));
impl.save(make_shared<Employee>(2, "bar", 20 , "Second Street", "BackEnd", 200.0));
impl.save(make_shared<Employee>(3, "bim", 30 , "Third Street", "Designer", 300.0));

}

void testEmployeeDaoFlatImpl2()  {
EmployeeDAOFlatImpl impl("employees.txt") ;
auto  employees = impl.findAll();
 qDebug() << "all employees" ;
 for(auto &emp: employees)
     qDebug() << emp->toString();
}


void testEmployeeDaoFlatImpl3() {
    EmployeeDAO *dao = new EmployeeDAOFlatImpl("employees.txt");
    auto  employees = dao-> findAll();
     qDebug() << "all employees" ;
     for(auto &emp: employees)
         qDebug() << emp->toString();

}


void testSQL()  {
 QSqlDatabase db ;
 db = QSqlDatabase::addDatabase("QMYSQL3");
 db.setHostName("localhost");
 db.setPort(3306);
 db.setUserName("root");
 db.setPassword("");
  db.setDatabaseName("test");
 try {
     if(!db.open())  {
        qDebug() << "connection error.";
        return ;
     }
     QSqlQuery query;
     query.prepare("select * from worker");
     qDebug() << "connection success." ;


      query.exec();
         while(query.next())  {
            qDebug() << query.value(0).toString() << ", " << query.value(1).toString() << ", "
                     << query.value(2).toString() << ", " << query.value(3).toString() << ", "
                     << query.value(4).toString();
         }

 } catch(exception &ex) {
     qDebug() << ex.what();
 }
}



void testEmployeeDAOysql() {
EmployeeDAOMysql impl;
 impl.save(make_shared<Employee>(1, "foo", 10 , "Bochum", "Manager", 100.0));
  impl.save(make_shared<Employee>(2, "bar", 20 , "Koeln", "FrontEnd", 200.0));
   impl.save(make_shared<Employee>(3, "bim", 30 , "Berlin", "Designer", 300.0));

auto all = impl.findAll();
for(auto &emp: all) {
    qDebug() << emp->toString() ;
}

auto one = impl.findById(1);
qDebug() << "one = " << one->toString();
impl.update(1, make_shared<Employee>(1, "newFoo", 30, "Berlin", "BackEnd", 400.0));
one = impl.findById(1);
qDebug() << "one after update = " << one->toString();
impl.remove(1);
 all = impl.findAll();
 qDebug() << "employee count after remove = " << all.count();
}

int main(int argc, char *argv[])
{
//     testEmployeeDaoFlatImpl3();
//     return 0;

//    testEmployeeDAOysql();
//    return 0;
        QApplication a(argc, argv);
    //EmployeeDAOFlatImpl impl("employees.txt");
    EmployeeDAOMysql impl;
    MainWindow w(0, &impl);
    w.show();

    return a.exec();

}
