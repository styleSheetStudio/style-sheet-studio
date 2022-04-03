#include "projectpreview.h"

projectPreview::projectPreview(QWidget *parent)
    : QWidget(parent)
{
this->setFixedSize(200,100);
    QLabel *label_Name = new QLabel(this);
    QLabel *label_path = new QLabel(this);
    label_Name->setGeometry(10,10,300,25);
    label_Name->setText("Название");
    this->setStyleSheet("background-color: red;");
}
void projectPreview::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);



}
