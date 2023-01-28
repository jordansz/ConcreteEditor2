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
    , widgetTemp(this)
{
    ui->setupUi(this);
    ui->sizeSlider->setDisabled(1);
    ui->tiltSlider->setDisabled(1);
    ui->wobbleSlider->setDisabled(1);

//    QWidget widget(this);
//    ui->stackedWidget->addWidget(&widget);
    pointSelectorWidget->setFocusPolicy(Qt::StrongFocus);       // needed for backspace cropping selection
    ui->stackedWidget->addWidget(pointSelectorWidget);
    ui->stackedWidget->addWidget(myOpenglWidget);
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(&widgetTemp));
//    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(pointSelectorWidget));
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
    ui->stackedWidget->setCurrentWidget(&widgetTemp);
    ui->stackedWidget->removeWidget(myOpenglWidget);
    myOpenglWidget = new MyOpenGLWidget(this);
    qDebug() << "initializing opengl stuff";
    myOpenglWidget->restart();
    myOpenglWidget->updateTexture(img);

    ui->stackedWidget->addWidget(myOpenglWidget);
    qDebug() << ui->stackedWidget->indexOf(myOpenglWidget);
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
//        ui->stackedWidget->setCurrentWidget(&widgetTemp);
        ui->stackedWidget->removeWidget(pointSelectorWidget);
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

