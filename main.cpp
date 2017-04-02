#include "mainwindow.h"
#include <QApplication>
#include "employeedaoflatimpl.h"


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

int main(int argc, char *argv[])
{
//     testEmployeeDaoFlatImpl3();
//     return 0;
    QApplication a(argc, argv);
    EmployeeDAOFlatImpl impl("employees.txt");
    MainWindow w(0, &impl);
    w.show();

    return a.exec();


}
