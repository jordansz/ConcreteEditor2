#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tutorialdialog.h"

#include <QFileDialog>
#include "assert.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
//    , selectedTextureImg(new QImage(""))
    , selectedTextureImg(nullptr)
    , ui(new Ui::MainWindow)
    , pointSelectorWidget(nullptr)
    , myOpenglWidget(nullptr)
    , widgetTemp(this)
{
    ui->setupUi(this);
    ui->sizeSlider->setDisabled(1);
    ui->tiltSlider->setDisabled(1);
    ui->wobbleSlider->setDisabled(1);

    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(&widgetTemp));
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
    connect(this, SIGNAL(slidersChanged(QVector4D)), myOpenglWidget, SLOT(updateSliderVals(QVector4D)));
    ui->stackedWidget->addWidget(myOpenglWidget);
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(myOpenglWidget));
}


void MainWindow::on_restartBtn_clicked()
{
    resetSliders();
    disableSliders();
    if(pointSelectorWidget != nullptr){
        pointSelectorWidget->restart();
        ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(pointSelectorWidget));
    }
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
            ui->stackedWidget->removeWidget(pointSelectorWidget);
            delete pointSelectorWidget;
        }
        pointSelectorWidget = new PointSelectorWidget(image, this);
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

void MainWindow::displaySelectedBackImg()
{
    if(selectedTextureImg != nullptr){
        connect(this, SIGNAL(userSelectedTexture(QImage)), myOpenglWidget, SLOT(updateBackTexture(QImage)));
        emit userSelectedTexture(*selectedTextureImg);
    }
}

QVector4D MainWindow::getSliderVals()
{
    GLfloat x = ui->tiltSlider->value();
    GLfloat y = ui->wobbleSlider->value();
    GLfloat z = 0.0f;
    GLfloat scaledSize = 200.0f - ui->sizeSlider->value() / 2.0f;

//            ui->sizeSlider->value() / (GLfloat)(ui->sizeSlider->maximum());
    return QVector4D(x, y, z, scaledSize);
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
        if(selectedTextureImg != nullptr){
            delete selectedTextureImg;
        }
        selectedTextureImg = new QImage(filename);
        assert(!selectedTextureImg->isNull());

        if(myOpenglWidget != nullptr){
            connect(this, SIGNAL(userSelectedTexture(QImage)), myOpenglWidget, SLOT(updateBackTexture(QImage)));
            emit userSelectedTexture(*selectedTextureImg);
        }
    }
}

