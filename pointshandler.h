#ifndef POINTSHANDLER_H
#define POINTSHANDLER_H

#include <QPoint>
#include <QList>
#include <QSize>

class PointsHandler
{
public:
    PointsHandler();
    void addPoint(QPointF point);
    void deletePoint();
    QList<QPointF> getPoints();
    void setPreviousSizes(QSize oldImageSize, QSize oldWidgetSize);
    void setSizes(QSize imageSize, QSize widgetSize);
    void updatePoints();
    bool isEmpty();
    bool checkClosedCircle();

private:
    QList<QPointF> points;
    QSize oldImageSize;
    QSize oldWidgetSize;
    QSize imageSize;
    QSize widgetSize;
};

#endif // POINTSHANDLER_H
