#include "tutorialdialog.h"
#include "ui_tutorialdialog.h"
#include <QDebug>
#include <QSize>

TutorialDialog::TutorialDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TutorialDialog)
{
    ui->setupUi(this);
    this->resize(parent->size());
    connect(ui->homeBtn, SIGNAL(clicked()), this, SLOT(on_homeBtn_clicked()));
    connect(this, SIGNAL(sendSize(QSize, QPoint)), parent, SLOT(recieveTutorialDialogSize(QSize, QPoint)));
}

TutorialDialog::~TutorialDialog()
{
    delete ui;
}


void TutorialDialog::on_homeBtn_clicked()
{
    emit sendSize(this->size(), pos());
    close();
}

