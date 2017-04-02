#include "employeeupdatewindow.h"
#include "ui_employeeupdatewindow.h"

EmployeeUpdateWindow::EmployeeUpdateWindow(QWidget *parent, EmployeeDAO *dao, long id, QStandardItemModel *employeeModel) :
    QMainWindow(parent),
    ui(new Ui::EmployeeUpdateWindow),
    dao(dao),
    id(id),
    employeeModel(employeeModel)
{
    ui->setupUi(this);
    addWidgets();
    registerEvents();
}

EmployeeUpdateWindow::~EmployeeUpdateWindow()
{
    delete ui;
}

//id, name, age, address, role and salary
void EmployeeUpdateWindow::addWidgets()
{
    shared_ptr<Employee> emp = dao->findById(id);
    QStringList fields = utils.convertEmployeeToFields(emp);
    ui->editId->setText(fields.at(0));
    ui->editName->setText(fields.at(1));
    ui->editAge->setText(fields.at(2));
    ui->editAddress->setText(fields.at(3));
    ui->editRole->setText(fields.at(4));
    ui->editSalary->setText(fields.at(5));
}

void EmployeeUpdateWindow::registerEvents()
{
  QObject::connect(ui->btnUpdate, SIGNAL(clicked(bool)), this, SLOT(onUpdate()));
  QObject::connect(ui->btnCancel, SIGNAL(clicked(bool)), this, SLOT(onCancel()));
}

void EmployeeUpdateWindow::onUpdate()
{
    QString errorMsg ;
    QStringList fields ;
    fields << ui->editId->text()
           << ui->editName->text()
           << ui->editAge->text()
           << ui->editAddress->text()
           << ui->editRole->text()
           << ui->editSalary->text();
    QVector<shared_ptr<Employee>> employees = dao->findAll();
    bool res = utils.verifyFields(errorMsg , fields, employees, false);
  if(res) {
      dao->update(ui->editId->text().toLong(), utils.convertFieldsToEmployee(fields));
      utils.fillEmployeeModel(employeeModel, dao->findAll());
      this->close();
  } else {
        QMessageBox *msgBox = new QMessageBox(this);
        msgBox->setWindowTitle("Error happened");
        msgBox->setText(errorMsg);
        msgBox->show();
  }
}

void EmployeeUpdateWindow::onCancel()
{
    ui->editId->clear();
    ui->editName->clear();
    ui->editAge->clear();
    ui->editAddress->clear();
    ui->editRole->clear();
    ui->editSalary->clear();
    close();
}
