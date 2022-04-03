#include "texteditlabel.h"
#include <QWidget>
#include <QDebug>
#include <QLineEdit>
#include <QStyleOption>
#include <QPainter>




TextEditLabel::TextEditLabel(QWidget *parent) : QLabel(parent)
{

    this->setCursor(QCursor(Qt::SizeHorCursor));
    edit = new QLineEdit(this);
    edit->setGeometry(60,0,65,19);
    //this->setFixedSize(55,15);
    name = new QLabel(this);
    //label->setText("Ширина");
    name->setGeometry(0,0,55,19);
   // labels->setGeometry(0,0,40,10);



}

void TextEditLabel::mousePressEvent(QMouseEvent *event)
{

    if(event->button() == Qt::LeftButton){
        qDebug() << "Зажали левую";
        qDebug() << event->pos().x();
        lastX = event->pos().x();
        start = true;
    }
    QLabel::mousePressEvent(event);
}

void TextEditLabel::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "Отпустили";
    QLabel::mouseReleaseEvent(event);

}

void TextEditLabel::mouseMoveEvent(QMouseEvent *event)
{
    if(start){
        value = value + (event->pos().x() - lastX)/10;
        qDebug() << "value=" << value;
        edit->setText(QString::number(value));
    }
    QLabel::mouseMoveEvent(event);
}

void TextEditLabel::setEdit(QLineEdit *edit)
{
    this->edit = edit;
}
