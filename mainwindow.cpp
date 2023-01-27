#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tutorialdialog.h"

#include <QFileDialog>
#include "assert.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , pointSelectorWidget(new PointSelectorWidget(this))
    , myOpenglWidget(new MyOpenGLWidget(this))
{
    ui->setupUi(this);
    QWidget widget(this);
    ui->stackedWidget->addWidget(&widget);
    pointSelectorWidget->setFocusPolicy(Qt::StrongFocus);       // needed for backspace cropping selection
    ui->stackedWidget->addWidget(pointSelectorWidget);
    ui->stackedWidget->addWidget(myOpenglWidget);
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(&widget));
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

void MainWindow::on_selectPicBtn_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Select Image"), "", tr("Images (*png *jpg)"));  //"Images (... part is allowables photo types... opens
    qDebug() << filename;
    // check if user picks an image
    if(!filename.isNull())
   {

        //create QImage variable
        QImage image;
        assert(image.load(filename));
        pointSelectorWidget = NULL;
        delete pointSelectorWidget;
        pointSelectorWidget = new PointSelectorWidget(image, this);
//        pointSelectorWidget->restart();
//        pointSelectorWidget->setImage(image);
        pointSelectorWidget->setFocusPolicy(Qt::StrongFocus);       // needed for backspace cropping selection
        ui->stackedWidget->addWidget(pointSelectorWidget);
        ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(pointSelectorWidget));
    }
    else{
        QMessageBox::warning(this, "Selecting Image error", "No image was selected or an unkown Error occured");
    }
}

