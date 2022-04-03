#include "stylecontent.h"
#include "QFileInfo"
styleContent::styleContent(QWidget *parent)
    : QWidget(parent)
{
this->setFixedSize(200,125);
   widgetlist->setGeometry(0,0,200,100);
   QSettings settings(path+"/styles.conf", QSettings::IniFormat );
      settings.beginGroup( "PUSH_BUTTON_TOOL" );
     // int x = settings.value( "x", -1 ).toInt();
QFileInfo info;
    int count =  settings.value("count").toInt();
      for(int i=0; i<count; i++){
        list.append( settings.value(QString::number(i)).toString());
       widgetlist->addItem( settings.value(QString::number(i)).toString());
       //info.setFile(settings.value(QString::number(i)).toString());
       //widgetlist->addItem(info.fileName());

      }
      settings.endGroup();
}
