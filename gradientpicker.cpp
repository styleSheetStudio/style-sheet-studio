#include "gradientpicker.h"
#include "ui_gradientpicker.h"
#include <QDebug>
#include <QPushButton>
#include <marker.h>
#include <QListWidgetItem>

#include <QListView>
#include <QListWidget>


GradientPicker::GradientPicker(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GradientPicker)
{
    ui->setupUi(this);

    //interval = new QTimer(this);

    //ThreadWhile threadr("mrkw");
  //   connect(interval, SIGNAL(timeout()), this, SLOT(out()));
//interval->start(1000/60);
    //threadr.start();
    ui->dialLine->setText("0");

}

GradientPicker::~GradientPicker()
{
    delete ui;
}


void GradientPicker::showData()
{

}

void GradientPicker::markerNewColor(QColor color)
{


}



void GradientPicker::on_comboBox_currentIndexChanged(int index)
{
    if(index==0){
        qDebug()<<"index 0";
        Gcurrent = false;
        //Liner();

    }else if(index==1){
         qDebug()<<"index 1";
          Gcurrent = true;
    }
}

void GradientPicker::Liner(){
 //rcolor0 = pick1->color.toRgb().name();







}

void GradientPicker::color_index_change()
{
 Marker *marker = qobject_cast <Marker*>(sender());
connect(marker, &QPushButton::released,this,&GradientPicker::updateSS);
Mcur=marker->getID();
qDebug()<<"MCUR:"<<Mcur;

 listc.removeAt(marker->getID()-1);
listc.insert(marker->getID()-1, marker->color_string);
listl.removeAt(marker->getID()-1);
listl.insert(marker->getID()-1, marker->pos_x_string);







}




//initF++;

 // qDebug()<<marker->pos_x_string;
    //   qDebug()<<listl;
  //qDebug()<<listc;








void GradientPicker::out()
{
 Marker *marker = qobject_cast <Marker*>(sender());




}


void GradientPicker::color_chnager()
{

}

void GradientPicker::updateSS()
{

    bufferQSS = "";
    bufferQSS.insert(0,"background-color: qlineargradient(spread:pad, ");
   for(int i=0; i < listl.count(); i++){
      bufferQSS += listl.at(i)+" ";

   }
   for(int i=0; i < listc.count(); i++){
      bufferQSS += listc.at(i)+" ";

   }

bufferQSS.remove(bufferQSS.size()-2,bufferQSS.size());
bufferQSS.append(");");
   ui->gradient->setStyleSheet(bufferQSS);
qDebug()<<bufferQSS;
}

void GradientPicker::list()
{

}

void GradientPicker::addMarker()
{
    // int i =0;
    Marker *marker = new Marker(this);
     marker->setGeometry(100,120 ,15,20);
     marker->setStyleSheet("background-color:blue");
     ui->box->addWidget(marker);
     marker->setFixedSize(15,20);


   //  ex->move(10,y);
     MarkersVector.append(marker);
    // marker->id++;
    // marker->setObjectName("marker_"+QString::number(index));


     connect(marker,&QPushButton::released,this,&GradientPicker::posUpdate);
 //connect(marker, &Marker::pressed, this, &GradientPicker::loadData);
  connect(marker, &Marker::released, this, &GradientPicker::color_index_change);
  connect(marker,&Marker::changeColor, this,&GradientPicker::markerNewColor);


   // posT->start();





















    // color += "stop:"+QString::number(index) + " ";



    // index++;

}


void GradientPicker::loadData()
{





}


void GradientPicker::on_plus_marker_clicked()
{
    addMarker();

qDebug()<<color;

}


void GradientPicker::on_st_clicked()
{


}


void GradientPicker::on_end_clicked()
{


}


void GradientPicker::on_minus_marker_clicked()
{

// MarkersVector.removeAt(Mcur);

 //qobject_cast <Marker*>(sender());

     //QLayoutItem* item = ->takeAt(itemIndex);
     //delete item->widget();
    // delete item;
 for(int i = 1; i < ui->box->count(); i++){
     /* Производим каст элемента слоя в объект динамической кнопки
      * */
     Marker *marker = qobject_cast<Marker*>(ui->box->itemAt(i)->widget());
     /* Если номер кнопки соответствует числу, которое установлено
      * в lineEdit, то производим удаление данной кнопки
      * */
     if(marker->getID() == Mcur){
         marker->hide();
         marker->remove();

         listc.removeAt(marker->getID()-1);
        listl.removeAt(marker->getID()-1);
        MarkersVector.removeAt(marker->getID()-1);
      delete marker;


     }
 }
}

void GradientPicker::posUpdate()
{
    Marker *marker = qobject_cast <Marker*>(sender());



    qDebug()<<marker->getID();



}









void GradientPicker::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
  //  int index = item->data(Qt::UserRole).toInt();
  //  qDebug()<<mrks.at(index).x;
    // qDebug()<<index;

}


void GradientPicker::on_dial_valueChanged(int value)
{
    double tmp;
    tmp=value;
ui->dialLine->setText(QString::number(tmp/100));
  foreach(Marker *marker, MarkersVector)
  {
      marker->setValueY(value/100.0);
  }
 updateSS();

}


void GradientPicker::on_mrk1_clicked()
{






    colorDlg  = QColorDialog::getColor(Qt::red);
     if(colorDlg.isValid()){
         QString buffercolor;
       buffercolor = colorDlg.toRgb().name();


     mrk1_color="stop:" + QString::number(0) + " " + buffercolor.append(",");
        ui->mrk1->setStyleSheet("background-color:"+colorDlg.name()+";");

        //qDebug()<<color_string;
        //tcolor1 = line->text();
        //toogle = true;



     }
     listc.removeAt(0);
     listc.insert(0, mrk1_color);
}


void GradientPicker::on_mrk2_clicked()
{
    colorDlg  = QColorDialog::getColor(Qt::red);
     if(colorDlg.isValid()){
         QString buffercolor;
       buffercolor = colorDlg.toRgb().name();


     mrk2_color="stop:" + QString::number(1) + " " + buffercolor.append(",");
        ui->mrk2->setStyleSheet("background-color:"+colorDlg.name()+";");

        qDebug()<<mrk2_color;
        qDebug()<<listc;
        listc.removeAt(1);
        listc.insert(1, mrk2_color);
        qDebug()<<mrk2_color;
        qDebug()<<listc;
     qDebug()<<listl;
     qDebug()<<bufferQSS;

     }
}


void GradientPicker::on_dialLine_textChanged(const QString &arg1)
{
    ui->dial->setValue(ui->dialLine->text().toDouble()*100);
    foreach(Marker *marker, MarkersVector)
    {
        marker->setValueY(ui->dialLine->text().toDouble());
    }
   updateSS();
}


void GradientPicker::on_buttonBox_accepted()
{
    this->accept();
}


void GradientPicker::on_buttonBox_rejected()
{
    this->reject();
    this->close();
    emit changeGradient();

}

void GradientPicker::onchange()
{

}

