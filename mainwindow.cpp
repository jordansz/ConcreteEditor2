#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tutorialdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , pointSelectorWidget(new PointSelectorWidget(this))
    , myOpenglWidget(new MyOpenGLWidget(this))
{
    ui->setupUi(this);
    pointSelectorWidget->setFocusPolicy(Qt::StrongFocus);       // needed for backspace cropping selection
    ui->stackedWidget->addWidget(pointSelectorWidget);
    ui->stackedWidget->addWidget(myOpenglWidget);
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

void MainWindow::initMyOpenglWidget(QImage img)
{
    qDebug() << "initializing opengl stuff";
//    myOpenglWidget->changeTexture(img);
    QImage newImg(":/Images/stackoverflow_Qt_dimmensios_question.png");
    myOpenglWidget->changeTexture(newImg);
    ui->stackedWidget->setCurrentIndex(3);
}

