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
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(pointSelectorWidget));
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
//    QImage newImg(":/Images/stackoverflow_Qt_dimmensios_question.png");
//    myOpenglWidget->updateTexture(newImg);
    myOpenglWidget->updateTexture(img);
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(myOpenglWidget));
}


void MainWindow::on_restartBtn_clicked()
{
    pointSelectorWidget->restart();
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(pointSelectorWidget));
}


void MainWindow::on_undoBtn_clicked()
{
    pointSelectorWidget->deletePoint();
    pointSelectorWidget->setFocusPolicy(Qt::StrongFocus);
}


/*
 How to load a user image they pick!!!!!!!!!!

 #include <QFileDialog>
 ...

 QString filename = QFileDialog::GetOpenFileName(this, tr("Choose"), "", tr("Images (*png ... *jpg)"))  "Images (... part is allowables photo types... opens

 if (QString::compare(filename, QString()) != 0)    // check if user picks an image
{
    //create QImage variable
    QImage image;
    bool valid = image.load(filename);

    //make sure the image is good to use
    if(valid){

    //put image on label
    ui->label->setPixmap(QPixmap::fromImage(image);


    }
    else{
    //error handling done here
    }
}
*/

