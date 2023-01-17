#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , pointSelectorWidget(new PointSelectorWidget(this))
{
    ui->setupUi(this);
    ui->stackedWidget->addWidget(pointSelectorWidget);
    ui->stackedWidget->setCurrentIndex(2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

