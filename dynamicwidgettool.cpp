#include "dynamicwidgettool.h"
#include "QDebug"
DynamicWidgetTool::DynamicWidgetTool(QWidget *parent)
    : QWidget(parent)
{

}

DynamicWidgetTool::DynamicWidgetTool(QString type,  int ID, QString currentTool, QWidget *parent)    : QWidget(parent)
{
    curtool=currentTool;
    types= type;
  this->setFixedSize(400,50);
   // QVBoxLayout *box = new QVBoxLayout(this);
   // QWidget *widget = new QWidget(this);
  //this->setLayout(box);
    ResID++;            // Увеличение счетчика на единицу
    buttonID = ResID;

    QPushButton *labeln = new QPushButton(this);
    labeln->setGeometry(0,35,100,15);
    labeln->setText("Нормальный");
   // labeln->setAlignment(Qt::AlignCenter);
    labeln->setStyleSheet("font: 300 9pt 'Ubuntu Light';"
                          "color: grey;"
                          "border: none;"
                          "background-color: transparent;");

    QPushButton *labelh = new QPushButton(this);
    labelh->setGeometry(110,35,100,15);
    labelh->setText("Наведенный");
   // labelh->setAlignment(Qt::AlignCenter);
    labelh->setStyleSheet("font: 300 9pt 'Ubuntu Light';"
                          "color: grey;"
                          "border: none;"
                          "background-color: transparent;");

    QPushButton *labelp = new QPushButton(this);
    labelp->setGeometry(220,35,100,15);
    labelp->setText("Зажатый");
   // labelp->setAlignment(Qt::AlignCenter);
    labelp->setStyleSheet("font: 300 9pt 'Ubuntu Light';"
                          "color: grey;"
                          "border: none;"
                          "background-color: transparent;");
   //  QPushButton *settingsBtn = new QPushButton(this);
   //  settingsBtn->setGeometry(325,0,80,30);
    // settingsBtn->setStyleSheet("QPushButton{"
               //                 "border-style: none;"
              //                  "image: url(:/res/circle.png);"
             //                   "}"
             //"QPushButton::hover{"
             //                   ""
               //                 "}");


    if(type=="PUSH_BUTTON_TOOL"){

        connect(labeln,&QPushButton::clicked, this,&DynamicWidgetTool::btnNormalUpdate);

             connect(labelh,&QPushButton::clicked, this,&DynamicWidgetTool::btnHoverUpdate);
              connect(labelp,&QPushButton::clicked, this,&DynamicWidgetTool::btnPressedUpdate);
           for(int i=0; i<5; i++){
           SSBuffer_hover.insert(i,"");
           btnNormal = new QPushButton(this);
           btnHover = new QPushButton(this);
           btnPressed = new QPushButton(this);

           labeln->setText("нормальный");
           labelh->setText("наведенный");
          labelp->setText("зажатый");
         //  labelp->setVisible(false);
                  btnNormal->setGeometry(0,0,100,28);
                  btnHover->setGeometry(110,0,100,28);
                  btnPressed->setGeometry(220,0,100,28);

    }

    }else if(type=="CHECK_BOX_TOOL"){
        cboxNormal = new QCheckBox(this);
        cboxPressed = new QCheckBox(this);
        cboxHover = new QCheckBox(this);
        labeln->setText("unchecked");
        labelh->setText("Checked");
       labelp->setText("checked");
      //  labelp->setVisible(false);
               cboxNormal->setGeometry(20,0,100,28);
               cboxHover->setGeometry(120,0,100,28);
                 cboxPressed->setGeometry(240,0,100,28);
               connect(labeln,&QPushButton::clicked, this,&DynamicWidgetTool::cboxNormalUpdate);

                    connect(labelh,&QPushButton::clicked, this,&DynamicWidgetTool::cboxHoverUpdate);
                   connect(labelp,&QPushButton::clicked, this,&DynamicWidgetTool::cboxPressedUpdate);

cboxNormal->setText("test");
cboxHover->setText("test");
cboxPressed->setText("test");
//cboxp->setChecked(true);
//normal
NCheckBox=0;
NTextFont=1;
NTextColor=2;
NTextAlign=3;
NBackgroundColor =4;
NRound=5;
NCloseCheckBox=6;
NCheckBoxIndicator=7;
NImage=8;
Nwidth=9;
NHeight=10;
NCloseCBoxIndicatorClose=11;

//checked  (as hover)
HCheckBox=0;
HTextFont=1;
HTextColor=2;
HTextAlign=3;
HBackgroundColor =4;
HRound=5;
HCloseCheckBox=6;
HCheckBoxChecked=7;
HImage=8;
Hwidth=9;
HHeight=10;
HCloseCheckBoxChecked=11;




    }else if(type=="LABEL_TOOL"){
        labelNormal = new QLabel(this);
        labelHover = new QLabel(this);
  //      labelPressed = new QLabel(this);

        labeln->setText("нормальный");
        labelh->setText("наведенный");
       //labelp->setText("");
      //  labelp->setVisible(false);
               labelNormal->setGeometry(20,0,100,28);
               labelHover->setGeometry(120,0,100,28);
               //labelPressed->setGeometry(240,0,100,28);
               connect(labeln,&QPushButton::clicked, this,&DynamicWidgetTool::labelNormalUpdate);
                    connect(labelh,&QPushButton::clicked, this,&DynamicWidgetTool::labelHoverUpdate);
                   //connect(labelp,&QPushButton::clicked, this,&DynamicWidgetTool::labelPressedUpdate);

labelNormal->setText("test");
labelHover->setText("test");
 HTextFont=0;
 HTextColor=1;
 HTextAlign=2;
 HBackgroundColor =3;
 HBackgroundImage =4;
 HBackgroundRepeate =5;
 HBackgroundPosition =6;
 HRound = 7;
 HMarginWidth =8;
 HMarginStyle=9;
 HMarginColor=10;
 HMarginPadding=11;

 NTextFont=0;
 NTextColor=1;
 NTextAlign=2;
 NBackgroundColor =3;
 NBackgroundImage =4;
 NBackgroundRepeate =5;
 NBackgroundPosition =6;
 NRound = 7;
 NMarginWidth =8;
 NMarginStyle=9;
 NMarginColor=10;
 NMarginPadding=11;



    }


}

QString DynamicWidgetTool::getTool()
{
 return curtool;
}
void DynamicWidgetTool::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);


}
int DynamicWidgetTool::getID()
{
    return buttonID;
}

QString DynamicWidgetTool::getType()
{
    return types;
}

void DynamicWidgetTool::updatePanel()
{

    emit newPanel("PUSH_BUTTON_TOOL", "NULL");
}

void DynamicWidgetTool::btnNormalUpdate()
{
      emit newPanel("PUSH_BUTTON_TOOL", "NORMAL");
       qDebug()<<"tool: "<<curtool;
}
void DynamicWidgetTool::btnHoverUpdate()
{
      emit newPanel("PUSH_BUTTON_TOOL", "HOVER");
       qDebug()<<curtool;
}
void DynamicWidgetTool::btnPressedUpdate()
{
    emit newPanel("PUSH_BUTTON_TOOL", "PRESSED");
       qDebug()<<curtool;
}


void DynamicWidgetTool::cboxNormalUpdate()
{
    emit newPanel("CHECK_BOX_TOOL", "NORMAL");
    qDebug()<<curtool;
}

void DynamicWidgetTool::cboxHoverUpdate()
{
    emit newPanel("CHECK_BOX_TOOL", "HOVER");
}

void DynamicWidgetTool::labelNormalUpdate()
{
    emit newPanel("LABEL_TOOL", "NORMAL");
}

void DynamicWidgetTool::labelHoverUpdate()
{
    emit newPanel("LABEL_TOOL", "HOVER");
}

void DynamicWidgetTool::labelPressedUpdate()
{
    emit newPanel("LABEL_TOOL", "PRESSED");
}
void DynamicWidgetTool::cboxPressedUpdate()
{
    emit newPanel("CHECK_BOX_TOOL", "PRESSED");
}



int DynamicWidgetTool::ResID = 0;
