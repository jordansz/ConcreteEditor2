#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tutorialdialog.h"

#include <QFileDialog>
#include "assert.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , selectedTextureImg(new QImage(""))
    , ui(new Ui::MainWindow)
    , pointSelectorWidget(nullptr)
    , myOpenglWidget(nullptr)
    , widgetTemp(this)
{
    ui->setupUi(this);
    ui->sizeSlider->setDisabled(1);
    ui->tiltSlider->setDisabled(1);
    ui->wobbleSlider->setDisabled(1);

//    QWidget widget(this);
//    ui->stackedWidget->addWidget(&widget);
//    pointSelectorWidget->setFocusPolicy(Qt::StrongFocus);       // needed for backspace cropping selection
//    ui->stackedWidget->addWidget(pointSelectorWidget);
//    ui->stackedWidget->addWidget(myOpenglWidget);
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
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(&widgetTemp));
    if(myOpenglWidget != nullptr){
        myOpenglWidget->restart();      // important for resetting the global variable square
        ui->stackedWidget->removeWidget(myOpenglWidget);
        delete myOpenglWidget;
    }
    myOpenglWidget = new MyOpenGLWidget(img, this);
    qDebug() << "initializing opengl stuff";
//    myOpenglWidget->restart();                      //square is global, reseting it just in case
//    myOpenglWidget->updateTexture(img);
    connect(this, SIGNAL(slidersChanged(QVector3D)), myOpenglWidget, SLOT(updateRotation(QVector3D)));
    ui->stackedWidget->addWidget(myOpenglWidget);
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(myOpenglWidget));
}


void MainWindow::on_restartBtn_clicked()
{
    resetSliders();
    disableSliders();
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
        resetSliders();
        disableSliders();
        //create QImage variable
        QImage image;
        assert(image.load(filename));
        ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(&widgetTemp));
        if(pointSelectorWidget != nullptr){
            qDebug() << "Deleting previous pointSelectorWidget\n" << pointSelectorWidget->initialized;
            ui->stackedWidget->removeWidget(pointSelectorWidget);
            delete pointSelectorWidget;

        }
        pointSelectorWidget = new PointSelectorWidget(image, this);
//        pointSelectorWidget = NULL;
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

void MainWindow::enableSliders()
{
    ui->sizeSlider->setEnabled(true);
    ui->tiltSlider->setEnabled(true);
    ui->wobbleSlider->setEnabled(true);
}

QVector3D MainWindow::getSliderVals()
{
    GLfloat x = ui->wobbleSlider->value();
    GLfloat y = ui->tiltSlider->value();
    GLfloat z = 0.0f;
    return QVector3D(x, y, z);
}

void MainWindow::resetSliders()
{
    ui->tiltSlider->setValue((ui->tiltSlider->maximum() + ui->tiltSlider->minimum()) / 2);
    ui->wobbleSlider->setValue((ui->wobbleSlider->maximum() + ui->wobbleSlider->minimum()) / 2);
    ui->sizeSlider->setValue((ui->sizeSlider->maximum() + ui->sizeSlider->minimum()) / 2);
}

void MainWindow::disableSliders()
{
    ui->sizeSlider->setDisabled(true);
    ui->tiltSlider->setDisabled(true);
    ui->wobbleSlider->setDisabled(true);
}


void MainWindow::on_tiltSlider_valueChanged()
{
    emit slidersChanged(getSliderVals());
}


void MainWindow::on_wobbleSlider_valueChanged()
{
    emit slidersChanged(getSliderVals());
}


void MainWindow::on_sizeSlider_valueChanged()
{
    emit slidersChanged(getSliderVals());
}


void MainWindow::on_resetSlidersBtn_clicked()
{
    resetSliders();
}


void MainWindow::on_chooseTxtreBtn_clicked()
{
    //I Should make this a seperate dialog window to show off the textures.  Kind of photo gallery widget
//    QFile file(":/Textures");

    QString filename = QFileDialog::getOpenFileName(this, tr("Select Texture"), ":/Textures", tr("Images (*png *jpg)"));  //"Images (... part is allowables photo types... opens
    if(!filename.isNull()){
        if(!selectedTextureImg->isNull()){
            selectedTextureImg = nullptr;
            delete selectedTextureImg;
            qDebug() << "Not ldkdk Null image";
        }
//        selectedTextureImg = new QImage(filename);
        selectedTextureImg = new QImage(filename);
        qDebug() << selectedTextureImg->load(filename);
//        selectedTextureImg = new QImage(this);
        qDebug() << "User selected a texture" << selectedTextureImg;
        assert(!selectedTextureImg->isNull());
        qDebug() << "past it";
    }
}

