#include "resignin.h"
#include "ui_resignin.h"

resignin::resignin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::resignin)
{
    ui->setupUi(this);
}

resignin::~resignin()
{
    delete ui;
}
