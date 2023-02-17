#ifndef TEXTUREPICKERDIALOG_H
#define TEXTUREPICKERDIALOG_H

#include <QDialog>
#include <QLayout>
#include "flowlayout.h"

namespace Ui {
class TexturePickerDialog;
}

class TexturePickerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TexturePickerDialog(QWidget *parent = nullptr);
    ~TexturePickerDialog();

signals:
    void sendSize(QSize size, QPoint pos);

public slots:
    void on_homeBtn_clicked();

private:
    Ui::TexturePickerDialog *ui;
    QVBoxLayout *mainLayout;
    FlowLayout *flowLayout;
};

#endif // TEXTUREPICKERDIALOG_H
