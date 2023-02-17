#include "texturepickerdialog.h"
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
    mainLayout->addLayout(flowLayout, 0);

    QDirIterator it(":Textures", QDirIterator::Subdirectories);
    while(it.hasNext()){
        qDebug() << it.next();
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
    emit sendSize(this->size(), pos());
    close();
}
