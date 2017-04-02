#-------------------------------------------------
#
# Project created by QtCreator 2017-04-02T15:04:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StaffManagement
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    employee.cpp \
    employeedaoflatimpl.cpp \
    employeeaddwindow.cpp \
    employeeupdatewindow.cpp \
    employeedetailswindow.cpp \
    employeeutils.cpp

HEADERS  += mainwindow.h \
    employee.h \
    employeedao.h \
    employeedaoflatimpl.h \
    employeeaddwindow.h \
    employeeupdatewindow.h \
    employeedetailswindow.h \
    employeeutils.h

FORMS    += mainwindow.ui \
    employeeaddwindow.ui \
    employeeupdatewindow.ui \
    employeedetailswindow.ui
