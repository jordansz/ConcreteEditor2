#ifndef DISPLAYIMAGEINFOWIDGET_H
#define DISPLAYIMAGEINFOWIDGET_H

#include <QWidget>
#include <QString>

namespace Ui {
class DisplayImageInfoWidget;
}

class DisplayImageInfoWidget : public QWidget
{
    Q_OBJECT

public:

    explicit DisplayImageInfoWidget(const QString &fp, QWidget *parent = nullptr);
    ~DisplayImageInfoWidget();

private slots:
    void on_pushButton_clicked();

signals:
    void sendFilePath(const QString &fp);
    void signalParentClose();

private:
    Ui::DisplayImageInfoWidget *ui;
    const QString *fp;
};

#endif // DISPLAYIMAGEINFOWIDGET_H
