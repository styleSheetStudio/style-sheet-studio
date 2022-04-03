#include "marker.h"
#include <QDebug>
#include <QWidget>


Marker::Marker(QWidget *parent):QPushButton(parent)
{
    ResID++;            // Увеличение счетчика на единицу
    buttonID = ResID;



   // buttonID = b--;
}

void Marker::mousePressEvent(QMouseEvent *event)
{

    if(event->button() == Qt::LeftButton){
        oldPos = event->pos();
      //  this->setStyleSheet("background-color:red;");
    }
    QPushButton::mousePressEvent(event);
}

void Marker::mouseReleaseEvent(QMouseEvent *event)
{

    QPushButton::mouseReleaseEvent(event);
    //this->setStyleSheet("background-color:blue;");
}

void Marker::mouseMoveEvent(QMouseEvent *event)
{

    if(event->isAccepted()==true){
        unpressed = true;
        double delta = event->pos().x() - oldPos.x();
        move(pos().x() + delta, pos().y());
        QPushButton::mouseMoveEvent(event);

        pos_x = pos().x()/3.25/100;


        //pos_x_string.append(QString::number(pos_x));






             // pos_x_string.indexOf("x1:"); // 1
              pos_x_string=(QString::number(pos_x));
              pos_x_string.insert(0,"x" + QString::number(getID())+":");

            // pos_x_string.append();
          QString tmps = (QString::number(y_tmp)) + ",";
             pos_x_string.append(", y"+QString::number(getID())+":" );
              pos_x_string +=tmps;



               //


              color_string = QString::number(pos_x);
                       color_string.insert(0, "stop:");
                       color_string.append(" "+buffercolor+",");


              qDebug()<<color_string;



         qDebug()<<pos_x_string;
         //getData();
        // GradientPicker:color_index_change();
    }else if(event->isAccepted()==false){
   unpressed = false;
     qDebug()<<"unMoved";
    }


}

void Marker::mouseDoubleClickEvent(QMouseEvent *event)
{
   // buttonID=b-1;
    if(event->button() == Qt::LeftButton){
    qDebug()<<"doubleCLick";
    colorDlg  = QColorDialog::getColor(Qt::red,nullptr,"Выбор цвета", QColorDialog::ShowAlphaChannel);
     if(colorDlg.isValid()){
       newColor = colorDlg;


   emit changeColor(colorDlg);

         color_string = "stop:" + QString::number(pos_x) + " " + buffercolor.append(",");
        this->setStyleSheet("background-color:"+colorDlg.name()+";");
   buffercolor=colorDlg.name();
        qDebug()<<color_string;
        //tcolor1 = line->text();
        //toogle = true;



     }
    }
}

Gmarker Marker::getData()
{
// Gmarker data;
// data.color_string = color_string;
// data.pos_x = pos_x_string;
}


/* Метод для возврата значения номера кнопки
 * */
int Marker::getID()
{
    return buttonID;

}

QColor Marker::getNewColor()
{
    return newColor;
}

void Marker::setValueY(double value)
{
y_tmp=value;
// pos_x_string.indexOf("x1:"); // 1
 pos_x_string=(QString::number(pos_x));
 pos_x_string.insert(0,"x" + QString::number(getID())+":");

// pos_x_string.append();
QString tmps = (QString::number(y_tmp)) + ",";
pos_x_string.append(", y"+QString::number(getID())+":" );
 pos_x_string +=tmps;


}

void Marker::remove()
{
ResID--;
}




/* Инициализация статической переменной класса.
 * Статическая переменная класса должна инициализироваться в обязательном порядке
 * */
int Marker::ResID = 0;
