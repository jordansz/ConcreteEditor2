#ifndef POINTSELECTORWIDGET_H
#define POINTSELECTORWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QShowEvent>
#include <QResizeEvent>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QImage>

#include "pointshandler.h"

QT_BEGIN_NAMESPACE
namespace Ui { class PointSelectorWidget; }
QT_END_NAMESPACE

class PointSelectorWidget : public QWidget
{
    Q_OBJECT

public:
    PointSelectorWidget(QWidget *parent = nullptr);
    ~PointSelectorWidget();
    void setImage(const QString fp);
    void resizeImage();

protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void showEvent(QShowEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    QImage image;
    QImage image2;
    PointsHandler pointsHandler;
    bool editImage;
};

#endif // POINTSELECTORWIDGET_H
