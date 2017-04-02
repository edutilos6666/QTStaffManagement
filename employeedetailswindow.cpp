#include "employeedetailswindow.h"
#include "ui_employeedetailswindow.h"

EmployeeDetailsWindow::EmployeeDetailsWindow(QWidget *parent, EmployeeDAO *dao, long id) :
    QMainWindow(parent),
    ui(new Ui::EmployeeDetailsWindow),
    dao(dao),
    id(id)
{
    ui->setupUi(this);
    addWidgets();
    registerEvents();
}


EmployeeDetailsWindow::~EmployeeDetailsWindow()
{
    delete ui;
}

void EmployeeDetailsWindow::addWidgets()
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

void EmployeeDetailsWindow::registerEvents()
{
    QObject::connect(ui->btnClose, &QPushButton::clicked , [this](){
        this->close();
    });
}
