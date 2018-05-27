#-------------------------------------------------
#
# Project created by QtCreator 2018-05-06T20:46:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lab11
TEMPLATE = app
CONFIG += c++14\




SOURCES += main.cpp\
            Controller/Controller.cpp\
            Repository/Repository.cpp\
            Repository/ListSaver.cpp\
            Repository/AdoptionList.cpp\
            Repository/FileRepository.cpp\
            Domain/Dog.cpp\
            Tests\Tests.cpp\
            UI/UI.cpp\
            mywindow.cpp \
            Validators/AppError.cpp \
    listformatdialog.cpp \
    Domain/adoptionlistmodel.cpp \
    adoptionlistview.cpp \
    undo.cpp

HEADERS  +=\
            Controller/Controller.h\
            Repository/Repository.h\
            Repository/ListSaver.h\
            Repository/AdoptionList.h\
            Repository/FileRepository.h\
            Domain/Dog.h\
            Tests\Tests.h\
            UI/UI.h\
            mywindow.h \
            Validators/AppError.h \
    listformatdialog.h \
    Domain/adoptionlistmodel.h \
    adoptionlistview.h \
    undo.h

FORMS    += \
    mywindow.ui \
    listformatdialog.ui \
    adoptionlistview.ui
