#include "gpick.h"
#include <QStyleOption>
#include <QPainter>
#include <QDebug>


GPick::GPick(QWidget *parent) : QWidget(parent)
{
    btn = new QPushButton(this);
    line = new QLineEdit(this);
    this->setFixedSize(200,36);
    line->setGeometry(0,0,55,19);
    btn->setGeometry(58,0,55,19);
   // ssv->setGeometry(0,15, 200,95);
    //->setStyleSheet("background: #fff;");
      connect(btn,&QPushButton::clicked,this,&GPick::on_btn_click);


}




void GPick::on_btn_click()
{
    qDebug()<<"Clicked";

    gpicks->setWindowTitle("Градиент Dialog");
    gpicks->setWindowIcon(QIcon(":/icons/images/gradient_icon.png"));

    //gpicks->exec();
     if(gpicks->exec()==QDialog::Accepted){
       line->setText(gpicks->bufferQSS);
       btn->setStyleSheet(gpicks->bufferQSS);
       FinalSS = gpicks->bufferQSS;
    }

}
