#include "texturepickerdialog.h"
#include "displayimageinfowidget.h"
#include "ui_texturepickerdialog.h"
#include <QDirIterator>
#include <QDebug>

TexturePickerDialog::TexturePickerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TexturePickerDialog),
    mainLayout(new QVBoxLayout(this)),
    flowLayout(new FlowLayout)
{
    ui->setupUi(this);
    this->resize(parent->size());
    mainLayout->addWidget(ui->homeBtn, 0, Qt::AlignTop | Qt::AlignRight);
    mainLayout->addLayout(flowLayout, 5);

    QDirIterator it(":Textures", QDirIterator::Subdirectories);
    while(it.hasNext()){
        QString fp(it.next());
        flowLayout->addWidget(new DisplayImageInfoWidget(fp, this));
//        qDebug() << it.fileName();
    }

    connect(ui->homeBtn, SIGNAL(clicked()), this, SLOT(on_homeBtn_clicked()));
    connect(this, SIGNAL(sendSize(QSize, QPoint)), parent, SLOT(recieveDialogSize(QSize, QPoint)));
}

TexturePickerDialog::~TexturePickerDialog()
{
//    delete flowLayout;
//    delete mainLayout;
    delete ui;
}

void TexturePickerDialog::on_homeBtn_clicked()
{
    qDebug() << "closing texture dialog";
    emit sendSize(this->size(), pos());
    close();
}
