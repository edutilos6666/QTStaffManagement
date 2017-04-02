#include "employeedaoflatimpl.h"


EmployeeDAOFlatImpl::EmployeeDAOFlatImpl(QString fileName):
     fileName(fileName)
{
    readFromFile();
    qDebug() << "map count = " << employeeMap.count() ;
}

EmployeeDAOFlatImpl::~EmployeeDAOFlatImpl()
{
    qDebug() << "EmployeeDAOFlatImpl instance was destroyed." ;
    if(employeeMap.count() > 0)
    finalize();
}

void EmployeeDAOFlatImpl::save(shared_ptr<Employee> employee)
{
  employeeMap.insert(employee->id , employee);
}

void EmployeeDAOFlatImpl::update(long id, shared_ptr<Employee> newEmp)
{
  // employeeMap.remove(id);
   employeeMap.insert(id, newEmp);
}

void EmployeeDAOFlatImpl::remove(long id)
{
     employeeMap.remove(id);
}

shared_ptr<Employee> EmployeeDAOFlatImpl::findById(long id)
{
    return employeeMap.value(id);
}

QVector<shared_ptr<Employee> > EmployeeDAOFlatImpl::findAll()
{
    QList<shared_ptr<Employee>> employees = employeeMap.values();
    QVector<shared_ptr<Employee>> all ;
    for(auto &emp: employees)
        all.append(emp);

    return all ;
 }

void EmployeeDAOFlatImpl::finalize()
{
    QFile file(fileName);
    file.open(QIODevice::WriteOnly| QIODevice::Text);
       QTextStream out(&file);

    for(long k: employeeMap.keys()) {
        shared_ptr<Employee> emp = employeeMap[k];
        out << emp->toString() << endl ;
    }

    file.close();
}

void EmployeeDAOFlatImpl::readFromFile()
{
   QFile file(fileName);
   file.open(QIODevice::ReadOnly | QIODevice::Text);
   QTextStream in(&file);
   QRegExp regex("\\s*,\\s*");
   while(!in.atEnd()) {
       try  {
       QString line = in.readLine();
       // out << "[" << id << ", " << name << ", " << age << ", " << address << ", " << role << ", " << salary << "]";
       // [id, name, age, address, role, salary]
       line = line.trimmed().mid(1, line.count()-2);
        QStringList list = line.split(regex);
        qDebug() << list ;
       // qDebug() << list.count() ;
        if(list.count() < 6) continue ;
     //   qDebug() << "count > 6" ;
        long id = list.at(0).toLong();
        QString name = list.at(1);
        int age = list.at(2).toInt();
        QString address = list.at(3);
        QString role = list.at(4);
        double salary = list.at(5).toDouble();
     //   qDebug() << "salary = " << salary ;
        employeeMap.insert(id, make_shared<Employee>(id, name, age, address,role,salary));
       } catch(exception &ex) {
           qDebug() << ex.what();
       }
   }
}
