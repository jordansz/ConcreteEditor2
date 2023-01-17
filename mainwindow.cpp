#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tutorialdialog.h"

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


void MainWindow::on_tutorialBtn_clicked()
{
    this->hide();
    TutorialDialog tutorialDialog(this);
    tutorialDialog.exec();
    this->show();
}

void MainWindow::recieveTutorialDialogSize(QSize newSize, QPoint newPos)
{
    resize(newSize);
    move(newPos);
}

