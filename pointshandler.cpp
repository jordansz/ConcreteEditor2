#include "pointshandler.h"
#include <QDebug>

#define RADIUS 5

PointsHandler::PointsHandler()
{

}

void PointsHandler::addPoint(QPointF point)
{
    points.append(point);
}

void PointsHandler::deletePoint()
{
    points.removeLast();
}

QList<QPointF> PointsHandler::getPoints()
{
    return points;
}

void PointsHandler::setPreviousSizes(QSize oldImageSize, QSize oldWidgetSize)
{
    this->oldImageSize = oldImageSize;
    this->oldWidgetSize = oldWidgetSize;

}

void PointsHandler::setSizes(QSize imageSize, QSize widgetSize)
{
    this->imageSize = imageSize;
    this->widgetSize = widgetSize;
}

void PointsHandler::updatePoints()
{
    double xRatio = (double)imageSize.width() / oldImageSize.width();
    double yRatio = (double)imageSize.height() / oldImageSize.height();

    double oldXOffset = (oldWidgetSize.width() - oldImageSize.width()) / 2;
    double oldYOffset = (oldWidgetSize.height() - oldImageSize.height()) / 2;
    double newXOffset = (widgetSize.width() - imageSize.width()) / 2;
    double newYOffset = (widgetSize.height() - imageSize.height()) / 2;

    for(int i = 0; i < points.size(); i++){
        double newX = ((points[i].x() - oldXOffset) * xRatio) + newXOffset;
        double newY = ((points[i].y() - oldYOffset) * yRatio) + newYOffset;
        points.replace(i, QPointF(newX, newY));
    }
}

bool PointsHandler::isEmpty()
{
    return points.isEmpty();
}

bool PointsHandler::checkClosedRegion()
{
    if(points.size() > 2){
        double x1 = points[0].x();
        double y1 = points[0].y();
        double x2 = points.last().x();
        double y2 = points.last().y();

        double d = qSqrt(qPow(x1-x2, 2) + qPow(y1-y2, 2));
        if(d < RADIUS + RADIUS){
            points.removeLast();
            points.append(QPointF(x1, y1));
            return true;
        }
    }
    return false;
}

void PointsHandler::resetPoints()
{
    points.clear();
}

QList<QPointF> PointsHandler::getShiftedPoints(double xOff, double yOff)
{
    QList<QPointF> shiftedPoints;
    for(int i = 0; i < points.size(); i++){
        shiftedPoints.append(QPointF(points[i].x() - xOff, points[i].y() - yOff));
    }
    return shiftedPoints;
}

