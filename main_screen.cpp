#include "main_screen.h"
#include "ui_main_screen.h"
#include "QFile"
#include "QFileInfo"
#include "QStandardPaths"
#include "QDir"
#include "QFileDialog"
#include "QDebug"
#include "widget.h"
#include <QApplication>
#include <QStringListModel>
#include "QGraphicsDropShadowEffect"
#include "projectpreview.h"
#include "QSettings"
#include "QStandardPaths"

main_screen::main_screen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::main_screen)
{
    ui->setupUi(this);
    this->setWindowTitle("QSS - Home");
    QIcon logo(":/icons/images/logo.png");
    this->setWindowIcon(logo);
   // ui->panel1->setF
    QGraphicsDropShadowEffect *effect=new QGraphicsDropShadowEffect();
    //dialog->setGraphicsEffect(effect);
    //dialog->show();
    //ui->panel1->setGraphicsEffect(effect);
    //ui->frame->setFrameShadow("");
   // projectPreview *pp = new projectPreview;
  //  ui->projects->addWidget(pp);



    QSettings settings(path+"/qss.conf", QSettings::IniFormat );
       settings.beginGroup( "RecentProjects" );
      // int x = settings.value( "x", -1 ).toInt();

     int count =  settings.value("count").toInt();
       for(int i=0; i<count; i++){
         projectsList.append( settings.value(QString::number(i)).toString());
         ui->listWidget->addItem( settings.value(QString::number(i)).toString());
       }
       settings.endGroup();

}

main_screen::~main_screen()
{
    delete ui;
}

void main_screen::saveSettings()
{
    QSettings conf(path+"/qss.conf", QSettings::IniFormat);

    conf.beginGroup( "RecentProjects" );
    conf.setValue("count",QString::number(projectsList.count()));
    for(int i=0;i<projectsList.count(); i++){
        conf.setValue(QString::number(i), projectsList.at(i));
    }
        //conf.setValue( "",  fileName);
        conf.endGroup();
}

void main_screen::on_pushButton_clicked()
{
   // QString path =
     QString fileName = QFileDialog::getSaveFileName(this,
             "Новый проект","unitled.qss",
              "StyleSheet (*.qss)");
     if(!fileName.isEmpty()){
         Widget *w = new Widget(fileName);
         QFileInfo info(fileName);
         w->setWindowTitle("QSS - "+info.fileName());
         w->setStyleSheet(AllstyleSheet::getMainWidgetStyle());

        // model->insertRow();
        // QModelIndex index = model->index(model->rowCount()-1)


//QFileInfo info();
 QListWidgetItem *itm = new QListWidgetItem;
 itm->setText(fileName);

        w->newProject(fileName);
        this->close();
      w->show();


      ui->listWidget->addItem(itm);
projectsList.append(fileName);

     saveSettings();

     }




      //qDebug()<<fileName;
}


void main_screen::on_pushButton_2_clicked()
{

     QString fileNames =   QFileDialog::getOpenFileName(this, "Открыть проект*", "","styleSheetStudio(*.qss);;");
    Widget *w = new Widget(fileNames);
    QFileInfo info(fileNames);
    if(!fileNames.isEmpty()){
    w->setWindowTitle("QSS - "+info.fileName());
    w->setStyleSheet(AllstyleSheet::getMainWidgetStyle());
    w->show();
    w->openProject(fileNames);
    this->close();
    QListWidgetItem *itm = new QListWidgetItem;
    itm->setText(fileNames);
           //this->close();
         // w->show();
       //   bool check = false;
      // //  for(int i=0; i<projectsList.count();i++){
       //   if(projectsList.at(i)==fileNames){

       //   }else{
        //      check=true;

       //   }
        // }
        // if(check){
             ui->listWidget->addItem(itm);
       projectsList.append(fileNames);
           saveSettings();
       //  }


    }
}


void main_screen::on_listWidget_itemClicked(QListWidgetItem *item)
{
   qDebug()<< item->text();
   QString fileNames =   item->text();;
  Widget *w = new Widget(fileNames);
  QFileInfo info(fileNames);
  if(!fileNames.isEmpty()){
  w->setWindowTitle("QSS - "+info.fileName());
  w->setStyleSheet(AllstyleSheet::getMainWidgetStyle());
  w->show();
  w->openProject(fileNames);
  this->close();
  QListWidgetItem *itm = new QListWidgetItem;
  itm->setText(fileNames);
         this->close();
        w->show();
    //    ui->listWidget->addItem(itm);

  //projectsList.append(fileNames);
  //saveSettings();
  }
}

