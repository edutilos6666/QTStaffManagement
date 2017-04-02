#include "employeeutils.h"

EmployeeUtils::EmployeeUtils()
{

}

bool EmployeeUtils::verifyFields(QString &errorMsg, QStringList &fields, QVector<shared_ptr<Employee> > &employees, bool isAdd)
{
    //id, name, age, address, role and salary
    bool res = true ;
    QTextStream out(&errorMsg);
    QRegExp regex ;

    //id must be number
     regex.setPattern("\\d+");
      if(!regex.exactMatch(fields.at(0))) {
          res = false;
          out << "id must be number" << endl ;
      }

      //id must be unique
      if(isAdd) {
      for(auto &emp: employees) {
          if(regex.exactMatch(fields.at(0)) && emp->id == fields.at(0).toLong()) {
              res = false ;
              out << "id already exists" << endl ;
              break;
          }
      }
      }

      // name must be string
      regex.setPattern("\\w+");
      if(!regex.exactMatch(fields.at(1))) {
          res = false ;
          out << "name must be string of letters" << endl ;
      }

      //age must be number
      regex.setPattern("\\d+");
      if(!regex.exactMatch(fields.at(2)))  {
          res = false ;
          out << "age must be number" << endl;
      }

        //id, name, age, address, role and salary
        //address must be string of letters and digits and whitespaces
      regex.setPattern("(\\d+|\\w+|\\s+)+");
      if(!regex.exactMatch(fields.at(3))) {
          res = false ;
          out << "address must be string of letters and digits and whitespaces" << endl;
      }

      //role must be string of letters
      regex.setPattern("\\w+");
      if(!regex.exactMatch(fields.at(4))) {
          res = false ;
          out << "role must be string of letters" << endl;
      }

      //salary must be double
      regex.setPattern("\\d+(\\.\\d+)?");
      if(!regex.exactMatch(fields.at(5)))  {
          res = false ;
          out << "salary must be double" << endl ;
      }

      return res ;
}
//id, name, age, address, role and salary
shared_ptr<Employee> EmployeeUtils::convertFieldsToEmployee(QStringList &fields)
{
//    Employee *emp = new Employee();
    shared_ptr<Employee> emp {new Employee()};
      try {
         emp->id = fields.at(0).toLong();
         emp->name = fields.at(1);
         emp->age = fields.at(2).toInt();
         emp->address = fields.at(3);
         emp->role = fields.at(4);
         emp->salary = fields.at(5).toDouble();
    } catch(exception &ex)  {
        qDebug() << ex.what();
    }
    return emp;
}

QStringList EmployeeUtils::convertEmployeeToFields(shared_ptr<Employee> &employee)
{
    QStringList list;
    QString idStr = QString::number(employee->id),
            nameStr = employee->name,
            ageStr = QString::number(employee->age),
            addressStr = employee->address,
            roleStr = employee->role,
            salaryStr = QString::number(employee->salary);
    list << idStr << nameStr << ageStr << addressStr << roleStr << salaryStr ;
    return list;
}

void EmployeeUtils::fillEmployeeModel(QStandardItemModel *employeeModel, QVector<shared_ptr<Employee> > &all)
{
    qDebug() << "fillEmployeeModel was called";
    employeeModel->clear();
   // QVector<shared_ptr<Employee>> all = dao->findAll();
    qDebug() << "all count = " << all.count();
    int i = 0 ;
    for(auto &emp: all) {
        QStringList list = convertEmployeeToFields(emp);
        QStandardItem *itemId = new QStandardItem(list.at(0)),
                *itemName = new QStandardItem(list.at(1)),
                *itemAge = new QStandardItem(list.at(2)),
                *itemAddress = new QStandardItem(list.at(3)),
                *itemRole = new QStandardItem(list.at(4)),
                *itemSalary = new QStandardItem(list.at(5));

        QList<QStandardItem*> listItems;
        listItems << itemId << itemName << itemAge << itemAddress << itemRole << itemSalary ;
        employeeModel->appendRow(listItems);

    }
}
