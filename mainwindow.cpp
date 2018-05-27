#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Repository/Repository.h"
#include "Repository/FileRepository.h"
#include "Domain/Dog.h"
#include "UI/UI.h"
#include "Tests/Tests.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
