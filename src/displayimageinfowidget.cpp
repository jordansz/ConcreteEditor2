#include "displayimageinfowidget.h"
#include "ui_displayimageinfowidget.h"

DisplayImageInfoWidget::DisplayImageInfoWidget(const QString &fp, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplayImageInfoWidget)
{
    ui->setupUi(this);
    QPixmap pix(fp);
    if(pix.isNull())
        qDebug() << __FILE__ << " pixmap is null";
    this->fp = new QString(fp);
    QPixmap pix2 = pix.scaledToWidth(parent->width() / 7);
    ui->pixLabel->setText(fp);
    ui->pixLabel->setPixmap(pix2);
    ui->pixLabel->setMask(pix2.mask());
    ui->pixLabel->setScaledContents(true);

    connect(this, SIGNAL(sendFilePath(QString)), this->parent()->parent(), SLOT(setTexture(QString)));
    connect(this, SIGNAL(signalParentClose()), parent, SLOT(on_homeBtn_clicked()));
}

DisplayImageInfoWidget::~DisplayImageInfoWidget()
{
    delete ui;
}

void DisplayImageInfoWidget::on_pushButton_clicked()
{
    emit sendFilePath(*fp);
    emit (signalParentClose());
}

