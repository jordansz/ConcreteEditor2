#ifndef DISPLAYIMAGEINFOWIDGET_H
#define DISPLAYIMAGEINFOWIDGET_H

#include <QWidget>

namespace Ui {
class DisplayImageInfoWidget;
}

class DisplayImageInfoWidget : public QWidget
{
    Q_OBJECT

public:

    explicit DisplayImageInfoWidget(QWidget *parent = nullptr);
    ~DisplayImageInfoWidget();

private:
    Ui::DisplayImageInfoWidget *ui;
};

#endif // DISPLAYIMAGEINFOWIDGET_H
