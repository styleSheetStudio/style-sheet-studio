#include "colorpicker.h"
#include <QStyleOption>
#include <QPainter>
#include <QDebug>


colorPicker::colorPicker(QWidget *parent) : QWidget(parent)
{
    btn = new QPushButton(this);
    line = new QLineEdit(this);
    this->setFixedSize(200,19);
    line->setGeometry(0,0,55,19);
    btn->setGeometry(58,0,55,19);

      connect(btn,&QPushButton::clicked,this,&colorPicker::on_btn_click);

}




void colorPicker::on_btn_click()
{
    qDebug()<<"Clicked";

   color  = QColorDialog::getColor(Qt::red);
    if(color.isValid()){
       line->setText(color.name());
       btn->setStyleSheet("background-color:"+color.name()+";");
       tcolor1 = line->text();
       toogle = true;
      emit changeColor(color);
    }
}

