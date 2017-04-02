#include "employeedaomysql.h"

EmployeeDAOMysql::EmployeeDAOMysql()
{
   connect();
   createTableIfNotExists();
}


//id, name, age, address, role ,salary
void EmployeeDAOMysql::save(shared_ptr<Employee> employee)
{
   QString cmd;
   QTextStream out(&cmd);
   out << "insert into Employee VALUES(?, ?, ?, ?, ?, ?)";
   query->prepare(cmd);
   query->bindValue(0, employee->id);
   query->bindValue(1, employee->name);
   query->bindValue(2, employee->age);
   query->bindValue(3, employee->address);
   query->bindValue(4, employee->role);
   query->bindValue(5, employee->salary);
   query->exec();
}

void EmployeeDAOMysql::update(long id, shared_ptr<Employee> newEmp)
{
 QString cmd ;
 QTextStream out(&cmd);
 out << "update Employee set name = ? , age = ? , address = ? , role = ?, salary = ? where id = ?";
 query->prepare(cmd);
 query->bindValue(0, newEmp->name);
 query->bindValue(1, newEmp->age);
 query->bindValue(2, newEmp->address);
 query->bindValue(3, newEmp->role);
 query->bindValue(4, newEmp->salary);
query->bindValue(5, id);
query->exec();
}

void EmployeeDAOMysql::remove(long id)
{
  QString cmd;
  QTextStream out(&cmd);
  out << "delete from Employee where id = ?";
   query->prepare(cmd);
   query->bindValue(0, id);
   query->exec();
}

shared_ptr<Employee> EmployeeDAOMysql::findById(long id)
{
  shared_ptr<Employee> emp  {new Employee() };
  QString cmd ;
  QTextStream out(&cmd);
  out << "select * from Employee where id = ?";
   query->prepare(cmd);
   query->bindValue(0, id);
   if(query->exec() && query->next())
       return EmployeeMapper::mapQueryToEmployee(query);
   return emp;
}

QVector<shared_ptr<Employee> > EmployeeDAOMysql::findAll()
{
   QVector<shared_ptr<Employee>> list;
   QString cmd;
   QTextStream out(&cmd);
   out << "select * from Employee";
   //qDebug() << "inside while" ;
   query->prepare(cmd);
   query->exec();
   while(query->next()) {

       list.append(EmployeeMapper::mapQueryToEmployee(query));
   }

   return list ;
}

void EmployeeDAOMysql::connect()
{
    db = &(QSqlDatabase::addDatabase(DRIVER_NAME));
    db->setHostName(HOSTNAME);
    db->setPort(PORT);
    db->setUserName(USERNAME);
    db->setPassword(PASSWORD);
    db->setDatabaseName(DB_NAME);
    db->open();
    query = new QSqlQuery();
}

void EmployeeDAOMysql::disconnect()
{
    db->close();
}


//id, name, age, address, role ,salary
void EmployeeDAOMysql::createTableIfNotExists()
{
    QString cmd ;
    QTextStream out(&cmd);
   out << "create table if not exists Employee ("
       <<  "id bigint primary key, "
        << "name varchar(50) not null, "
        << "age int not null, "
        << "address varchar(50) not null, "
        << "role varchar(50) not null, "
        << "salary double not null"
        << ")";

   query->prepare(cmd);
   query->exec();
}

shared_ptr<Employee> EmployeeMapper::mapQueryToEmployee(QSqlQuery *query)
{
   shared_ptr<Employee> emp {new Employee() };
    try {
      long id = query->value(0).toLongLong();
      QString name = query->value(1).toString();
      int age = query->value(2).toInt();
      QString address = query->value(3).toString();
      QString role = query->value(4).toString();
      double salary = query->value(5).toDouble();
      emp->id = id ;
      emp->name = name;
      emp->age = age ;
      emp->address = address;
      emp->role = role;
      emp->salary = salary ;
   } catch(exception &ex) {
       qDebug() << ex.what();
   }
 // qDebug() << "here" ;
   return emp;
}
