#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, EmployeeDAO *dao) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    dao(dao)
{
    ui->setupUi(this);
    addWidgets();
    registerEvents();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addWidgets()
{
    //id, name, age, address, role and salary
    employeeModel = new QStandardItemModel();
    ui->tvEmployees->setModel(employeeModel);
    ui->tvEmployees->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tvEmployees->setSelectionBehavior(QAbstractItemView::SelectRows);
   utils.fillEmployeeModel(employeeModel, dao->findAll());
}

void MainWindow::registerEvents()
{
  QObject::connect(ui->btnAdd, SIGNAL(clicked(bool)), this, SLOT(onAddEmployee()));
  QObject::connect(ui->btnDetails, SIGNAL(clicked(bool)), this , SLOT(onEmployeeDetails()));
  QObject::connect(ui->btnRemove, SIGNAL(clicked(bool)), this, SLOT(onRemoveEmployee()));
  QObject::connect(ui->btnUpdate, SIGNAL(clicked(bool)), this, SLOT(onUpdateEmployee()));
  //QObject::connect(this, SIGNAL(completed()), this, SLOT(fillEmployeeModel()));
  QObject::connect(employeeModel, &QStandardItemModel::dataChanged, [this](const QModelIndex &topLeft, const QModelIndex &bottomRight){
    long id = getSelectedEmployeeId();
    if(id == -1) return ;
    shared_ptr<Employee> emp = dao->findById(id);
     int col = topLeft.column();
    //id, name, age, address, role and salary
     switch(col) {
       case 0:
         emp->id = employeeModel->data(topLeft).toLongLong();
         break;
     case 1:
         emp->name = employeeModel->data(topLeft).toString();
         break;
     case 2:
         emp->age = employeeModel->data(topLeft).toInt();
         break;
     case 3:
         emp->address = employeeModel->data(topLeft).toString();
         break;
     case 4:
         emp->role = employeeModel->data(topLeft).toString();
         break;
     case 5:
         emp->salary = employeeModel->data(topLeft).toDouble();
         break;
     }
     dao->update(id, emp);
      utils.fillEmployeeModel(employeeModel, dao->findAll());
  });


  QObject::connect(ui->btnPieCharts, SIGNAL(clicked(bool)), this, SLOT(onPieCharts()));
}

long MainWindow::getSelectedEmployeeId()
{
    QItemSelectionModel *selectionModel = ui->tvEmployees->selectionModel();
    QModelIndexList selectedRows =  selectionModel->selectedRows();
    if(selectedRows.count() != 1) {
      qDebug() << "invalid selection" ;
    QItemSelectionModel *selectionModel = ui->tvEmployees->selectionModel();
      return -1;
    }
  QModelIndex index = selectedRows.at(0);
    int row = index.row();
    QStandardItem *item = employeeModel->item(row, 0);
    return item->text().toLong();
}


void MainWindow::onAddEmployee()
{
   EmployeeAddWindow *addWindow = new EmployeeAddWindow(this, dao, employeeModel);
   addWindow->show();

}

void MainWindow::onUpdateEmployee()
{
   long id = getSelectedEmployeeId();
   if(id == -1) return ;
   EmployeeUpdateWindow *updateWindow = new EmployeeUpdateWindow(this, dao,id, employeeModel);
   updateWindow->show();
}

void MainWindow::onRemoveEmployee()
{
  long id = getSelectedEmployeeId();
  if(id == -1) return ;
  dao->remove(id);
  utils.fillEmployeeModel(employeeModel, dao->findAll());
}

void MainWindow::onEmployeeDetails()
{
    long id = getSelectedEmployeeId();
    if(id == -1) return ;
    EmployeeDetailsWindow *detailsWindow = new EmployeeDetailsWindow(this, dao, id);
    detailsWindow->show();
}

void MainWindow::onPieCharts()
{
   QMainWindow *window = new QMainWindow();
   window->resize(500, 500);
   window->setWindowTitle("Pie Charts");
   window->setWindowModality(Qt::WindowModal);
   QVBoxLayout *layout = new QVBoxLayout();
   QWidget *widget = new QWidget(window);
   window->setCentralWidget(widget);
   widget->setLayout(layout);
   auto emps = dao->findAll();
   //age
   QLabel *lblPieAge  = new QLabel("Pie Chart for Employees Age");
   QPieSeries *seriesAge = new QPieSeries();
   for(auto &emp: emps) {
       QString name = emp->name;
       int age = emp->age;
        seriesAge->append(name, age);
   }


   QChart *chartAge = new QChart();
   chartAge->setAnimationOptions(QChart::AllAnimations);
   chartAge->addSeries(seriesAge);
   chartAge->setTitle("Employees Age");
   QChartView *viewChartAge = new QChartView(chartAge);
   layout->addWidget(lblPieAge);
   layout->addWidget(viewChartAge);


   //wage
   QLabel *lblSalary = new QLabel("Pie Chart for Employees Salary");
   QPieSeries *seriesSalary = new QPieSeries();
   for(auto &emp: emps) {
       QString name = emp->name;
       double salary = emp->salary;
       seriesSalary->append(name, salary);
   }

   QChart *chartSalary = new QChart();
   chartSalary->setAnimationOptions(QChart::AllAnimations);
   chartSalary->addSeries(seriesSalary);
   chartSalary->setTitle("Employees Wage");
   QChartView *viewChartSalary = new QChartView(chartSalary);
   layout->addWidget(lblSalary);
   layout->addWidget(viewChartSalary);
   window->show();
}

