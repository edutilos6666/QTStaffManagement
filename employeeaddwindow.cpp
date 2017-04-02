#include "employeeaddwindow.h"
#include "ui_employeeaddwindow.h"

EmployeeAddWindow::EmployeeAddWindow(QWidget *parent, EmployeeDAO *dao, QStandardItemModel *employeeModel) :
    QMainWindow(parent),
    ui(new Ui::EmployeeAddWindow),
    dao(dao),
    employeeModel(employeeModel)
{
    ui->setupUi(this);
    addWidgets();
    registerEvents();
}


EmployeeAddWindow::~EmployeeAddWindow()
{
    delete ui;
}

void EmployeeAddWindow::addWidgets()
{

}

void EmployeeAddWindow::registerEvents()
{
   QObject::connect(ui->btnAdd, SIGNAL(clicked(bool)), this, SLOT(onSave()));
   QObject::connect(ui->btnCancel, SIGNAL(clicked(bool)), this, SLOT(onCancel()));
}


//id, name, age, address, role and salary
void EmployeeAddWindow::onSave()
{
   QString idStr = ui->editId->text(),
           nameStr = ui->editName->text(),
           ageStr = ui->editAge->text(),
           addressStr = ui->editAddress->text(),
           roleStr = ui->editRole->text(),
           salaryStr = ui->editSalary->text();
   QStringList fields ;
   fields << idStr << nameStr << ageStr << addressStr << roleStr << salaryStr ;
    auto employees = dao->findAll();
    QString errorMsg ;
    bool res =utils.verifyFields(errorMsg, fields, employees, true);
    if(res) {
       dao->save(utils.convertFieldsToEmployee(fields));
       utils.fillEmployeeModel(employeeModel, dao->findAll());
        this->close();
    } else {
       QMessageBox *msgBox = new QMessageBox(this);
       msgBox->setWindowTitle("Error happened");
       msgBox->setText(errorMsg);
       msgBox->show();
    }


}

void EmployeeAddWindow::onCancel()
{
  ui->editId->clear();
  ui->editName->clear();
  ui->editAge->clear();
  ui->editAddress->clear();
  ui->editRole->clear();
  ui->editSalary->clear();
  this->close();
}
