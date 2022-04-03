#include "panel.h"
#include <QStyleOption>
#include <QPainter>
#include "allstylesheet.h"
#include "colorpicker.h"
#include <QDebug>
#include <gpick.h>
#include "paneltext.h"

Panel::Panel(QWidget *parent) : QWidget(parent)
{


}

Panel::Panel(QString name, QString type, QString status,QString tool, QWidget *parent): QWidget(parent)
{
    toolchain = tool;
    typep = type;
    this->setStyleSheet("background:#ccc;");
    titleButton = new TitleButton;
    titleButton->setText(name);
    titleButton->setStyleSheet(AllstyleSheet::No_select_title_btn());
    vbox = new QVBoxLayout;
    vbox->setMargin(0);
    vbox->setSpacing(0);
    this->setLayout(vbox);
    vbox->addWidget(titleButton);
    contentWidget = new QWidget;
    vbox->addWidget(contentWidget);
    // contentWidget->setMinimumHeight(20);
    contentbox = new QGridLayout;
    connect(titleButton,&TitleButton::clicked,this,&Panel::changeContentVisible);

    //для примера пока что я сделал отдельный класс texteditLabel
    qDebug()<<type;

    ResID++;            // Увеличение счетчика на единицу
    buttonID = ResID;

    panelType = type;


statuss = status;
      connect(pn,&PanelText::changeData, this,&Panel::onGetData);
 connect(contentBackground,&panelBackground::onDataUpdate, this,&Panel::onGetData);
  connect(contentIcon,&panelIcon::onDataChanged, this,&Panel::onGetData);
    connect(contentRound,&panelRound::onDataUpdate, this,&Panel::onGetData);
        connect(contentMargins,&panelMargins::onDataUpdate, this,&Panel::onGetData);

    // QLabel *label = new QLabel("Контент");
    // contentbox->addWidget(edits,0,0);
    contentWidget->setLayout(contentbox);
    contentWidget->setVisible(false);
    onGetData();


}

int Panel::getID()
{
    return buttonID;
}

int Panel::getCur()
{

}

QString Panel::getTypePanel()
{
return typep;
}

QString Panel::getStatus()
{
return statuss;
}




void Panel::setName(QString name)
{
titleButton->setText(name);
}

void Panel::setType(QString type)
{

 panelType = type;

}

QString Panel::getTool()
{
    return toolchain;
}

QString Panel::GetStatus()
{
       return statuss;
}



void Panel::changeContentVisible()
{
    qDebug() << "changeContentVisible";
    if(contentVisible == false){


        //if(currentTool==PUSH_BUTTON_TOOL){
            if(panelType=="PANEL_BACKGROUND"){
                contentBackground->setVisible(true);
                contentbox->addWidget(contentBackground);

            }else if(panelType=="PANEL_TEXT"){
                pn->setVisible(true);
                contentbox->addWidget(pn);
            }else if(panelType=="PANEL_GEOMETRYS"){
                contentGeometry->setVisible(true);
                contentbox->addWidget(contentGeometry);

            }else if(panelType=="PANEL_MARGINS"){
                contentMargins->setVisible(true);
                contentbox->addWidget(contentMargins);

            }else if(panelType=="PANEL_ICON"){
                contentIcon->setVisible(true);
                contentbox->addWidget(contentIcon);

            }else if(panelType=="PANEL_ROUND"){
                contentRound->setVisible(true);
                contentbox->addWidget(contentRound);

            }else if(panelType=="PANEL_STYLE"){
                stylesContent->setVisible(true);
                contentbox->addWidget(stylesContent);

            }
       // }

  this->contentWidget->setVisible(true);
  contentVisible = true;
    qDebug()<<pn->getSizeF(); //проверка работы функции получения размера текста

  titleButton->setStyleSheet(AllstyleSheet::select_title_btn());



    }else{
          titleButton->setStyleSheet(AllstyleSheet::No_select_title_btn());
        this->contentWidget->setVisible(false);
        contentVisible = false;
        if(currentTool==PUSH_BUTTON_TOOL){
            if(panelType=="PANEL_BACKGROUND"){
                gpicker->setVisible(false);
            }else if(panelType=="PANEL_TEXT"){
                pn->setVisible(false);
            }
        }


    }
}

void Panel::onGetData()
{

        emit changeData(getTypePanel(), getTool(), GetStatus(), getID(),true);


}





void Panel::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);


}
int Panel::ResID = 0;
