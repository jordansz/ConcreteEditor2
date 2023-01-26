#include "pointselectorwidget.h"
#include <QDebug>
#include <QBrush>
#include <QRegion>

PointSelectorWidget::PointSelectorWidget(QWidget *parent)
    : QWidget{parent}
{
    setParent(parent);
    setImage(":/Images/homeButton.png");
//    setImage(":/Images/stackoverflow_Qt_dimmensios_question.png");
    this->adjustSize();
    editImage = false;
    connect(this, SIGNAL(sendImg(QImage)), parent, SLOT(initMyOpenglWidget(QImage)));
}

PointSelectorWidget::~PointSelectorWidget(){

}

void PointSelectorWidget::setImage(const QString fp)
{
    image = QImage(fp);
    image2 = QImage(fp);
    if(image.isNull()){
        qDebug() << "Error: Null Image. Line: " << __LINE__ << __FILE__;
    }
}

// resize image to fit the resized widget from resizeEvent()
void PointSelectorWidget::resizeImage()
{
    image = image2.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

void PointSelectorWidget::restart()
{
    editImage = false;
    pointsHandler.resetPoints();
    update();
}

void PointSelectorWidget::deletePoint()
{
//    image = image2.scaled(image.size(), Qt::KeepAspectRatio); //possibly not but //needed for removing the point left behind after backspace, just redoing it
    if(!pointsHandler.isEmpty()){
        editImage = false;
        pointsHandler.deletePoint();
        update();
    }
}

void PointSelectorWidget::resizeEvent(QResizeEvent *event)
{
    pointsHandler.setPreviousSizes(image.size(), event->oldSize());
    resizeImage();
    pointsHandler.setSizes(image.size(), this->size());
    pointsHandler.updatePoints();
    QWidget::resizeEvent(event);
}

void PointSelectorWidget::paintEvent(QPaintEvent *event)
{
    // from the image size and resolution size of widget draw it in the center
    double xOffset = (this->width() - image.width()) / 2;
    double yOffset = (this->height() - image.height()) / 2;
    QList<QPointF> points = pointsHandler.getPoints();
    // If image is not ready to be edited (not a close region) draw all lines and points
    if(!editImage){
        QPainter painter(this);
        painter.setPen(Qt::gray);
        painter.drawImage(xOffset, yOffset, image);

        for(auto point : points){
            painter.drawEllipse(point, 10, 10);
        }
        for(int i = 0; i < points.size() - 1; i++){
            painter.drawLine(points[i], points[i + 1]);
        }
    }
    if(editImage){
        // from the image size and resolution size of widget draw it in the center
//        QList<QPointF> points = pointsHandler.getPoints();
        QList<QPointF> points = pointsHandler.getShiftedPoints(xOffset, yOffset);
        QPolygon clipPolygon = QPolygonF(points).toPolygon();
        QRegion clippedRegion(clipPolygon, Qt::OddEvenFill);
//        QRect translatedImageRect = image.rect().translated(QPoint(xOffset, yOffset));
//        QRegion unClippedRegion = QRegion(translatedImageRect).subtracted(clippedRegion);
        QRegion unClippedRegion = QRegion(image.rect()).subtracted(clippedRegion);
        QImage output(image.size(), QImage::Format_ARGB32);
        QPainter painter(&output);
        output.fill(Qt::transparent);
        painter.setClipRegion(unClippedRegion, Qt::ReplaceClip);


        QRectF imgRec(0, 0, image.width(), image.height());
        qDebug() << xOffset;
        painter.drawImage(imgRec, image);
        painter.end();
        emit sendImg(output);
    }
    QWidget::paintEvent(event);
}

void PointSelectorWidget::mousePressEvent(QMouseEvent *event)
{
    qDebug() << event->pos();
    // Image is not ready to be cropped, continue checking new points close it
    if(!editImage){
        pointsHandler.addPoint(event->pos());
        editImage = pointsHandler.checkClosedRegion();
        update();                                   //for drawing point immediatly
    }
}

void PointSelectorWidget::showEvent(QShowEvent *event)
{

    pointsHandler.setPreviousSizes(image.size(), this->size());
    pointsHandler.setSizes(image.size(), this->size());
    update();
    QWidget::showEvent(event);
}

void PointSelectorWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Backspace){
        deletePoint();
    }
}
