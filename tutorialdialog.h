#ifndef TUTORIALDIALOG_H
#define TUTORIALDIALOG_H

#include <QDialog>
#include <QPoint>

namespace Ui {
class TutorialDialog;
}

class TutorialDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TutorialDialog(QWidget *parent = nullptr);
    ~TutorialDialog();

signals:
    void sendSize(QSize size, QPoint pos);

public slots:
    void on_homeBtn_clicked();


private:
    Ui::TutorialDialog *ui;
};

#endif // TUTORIALDIALOG_H
