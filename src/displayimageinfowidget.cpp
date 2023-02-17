#include "displayimageinfowidget.h"
#include "ui_displayimageinfowidget.h"

DisplayImageInfoWidget::DisplayImageInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplayImageInfoWidget)
{
    ui->setupUi(this);
}

DisplayImageInfoWidget::~DisplayImageInfoWidget()
{
    delete ui;
}
