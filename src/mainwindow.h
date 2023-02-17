#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "pointselectorwidget.h"
#include "myopenglwidget.h"
#include <QMainWindow>
#include <QImage>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
        void disableSliders();

private slots:
    void on_tutorialBtn_clicked();
    void on_restartBtn_clicked();
    void on_undoBtn_clicked();
    void on_selectPicBtn_clicked();
    void on_tiltSlider_valueChanged();
    void on_wobbleSlider_valueChanged();
    void on_sizeSlider_valueChanged();
    void on_resetSlidersBtn_clicked();

    void on_chooseTxtreBtn_clicked();

public slots:
    void recieveDialogSize(QSize newSize, QPoint newPos);
    void initMyOpenglWidget(QImage img);
    void enableSliders();
    void displaySelectedBackImg();

signals:
    void slidersChanged(QVector4D vec);
    void userSelectedTexture(QImage img);

private:
    QVector4D getSliderVals();
    void resetSliders();

    QImage *selectedTextureImg;
    Ui::MainWindow *ui;
    PointSelectorWidget *pointSelectorWidget;
    MyOpenGLWidget *myOpenglWidget;
    QWidget widgetTemp;
};
#endif // MAINWINDOW_H
