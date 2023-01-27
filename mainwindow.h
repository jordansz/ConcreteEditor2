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

private slots:
    void on_tutorialBtn_clicked();

    void on_restartBtn_clicked();

    void on_undoBtn_clicked();

    void on_selectPicBtn_clicked();

public slots:
    void recieveTutorialDialogSize(QSize newSize, QPoint newPos);
    void initMyOpenglWidget(QImage img);

private:
    Ui::MainWindow *ui;
    PointSelectorWidget *pointSelectorWidget;
    MyOpenGLWidget *myOpenglWidget;
    QWidget widgetTemp;
};
#endif // MAINWINDOW_H
