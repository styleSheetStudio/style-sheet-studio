#include "panelbackground.h"
#include "QMessageBox"
#include "QDebug"
#include "allstylesheet.h"
panelBackground::panelBackground(QWidget *parent)
    : QWidget(parent)
{
    this->setStyleSheet(AllstyleSheet::getPanelCSS());
  this->setFixedSize(200,125);
    QLabel *clabel = new QLabel(this);
    clabel->setText("Цвет");
    clabel->setStyleSheet("font: 300 10pt 'Ubuntu Light';"
                         "color: #6f6f6f;");
    clabel->setAlignment(Qt::AlignLeft);
    clabel->setGeometry(0,0,42,25);
    pick->setGeometry(60,0,55,25);

   Gradient->setGeometry(60,25,40,25);

   QLabel *grlabel = new QLabel(this);
   grlabel->setText("Градиент");
   grlabel->setStyleSheet("font: 300 10pt 'Ubuntu Light';"
                        "color: #6f6f6f;");
   grlabel->setGeometry(0,25,60,25);
  grlabel->setAlignment(Qt::AlignLeft);

  style->setGeometry(60,50,105,22);
  QLabel *slabel = new QLabel(this);
  slabel->setText("Стиль");
  slabel->setGeometry(0,50,60,25);
  slabel->setAlignment(Qt::AlignLeft);
  slabel->setStyleSheet("font: 300 10pt 'Ubuntu Light';"
                        "color: #6f6f6f;");
  style->addItem("Flat");
  style->addItem("Default Qt");
  style->addItem("None");
   // connect (pick->btn,&QPushButton::clicked,this,&panelBackground::oncolor);

  connect (pick,&colorPicker::changeColor,this,&panelBackground::oncolor);
    connect (Gradient->gpicks,&GradientPicker::changeGradient,this,&panelBackground::ongradient);
  //connect (GradienT,&QPushButton::clicked,this,&panelBackground::ongradient);

  connect (style,&QComboBox::currentText,this,&panelBackground::onstyle);
   connect (Gradient->line,&QLineEdit::textChanged,this,&panelBackground::ongradient);

}

QString panelBackground::getGradient()
{
return Gradient->line->text();
}

QString panelBackground::getColor()
{
return  pick->line->text();
}

QString panelBackground::getStyle()
{
    return style->currentText();
}

void panelBackground::updateData()
{
    emit onDataUpdate();
    qDebug()<<"PICker!!!!";
}

void panelBackground::onstyle()
{

}

void panelBackground::ongradient()
{

        emit onDataUpdate();

}

void panelBackground::oncolor()
{
       emit onDataUpdate();

}
