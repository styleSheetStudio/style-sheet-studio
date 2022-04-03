#include "drawer.h"
#include "ui_drawer.h"

drawer::drawer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::drawer)
{
    ui->setupUi(this);
}

drawer::~drawer()
{
    delete ui;
}
