#include "panelmargins.h"

panelMargins::panelMargins(QWidget *parent)
    : QWidget(parent)
{
      this->setFixedSize(200,175);
  QLabel * vlabel = new QLabel(this);

  // vlabel->setText("Внутренние");
   vedit->setGeometry(0,0,160,25);
   vedit->edit->setGeometry(85,0,40,19);
   vedit->name->setGeometry(0,0,85,19);
   vedit->name->setText("Внутренние");
   vlabel->setText("Тип");
   vlabel->setStyleSheet("font: 300 10pt 'Ubuntu Light';"
                              "color: #6f6f6f;"
                              "");
   vlabel->setAlignment(Qt::AlignLeft);

   marginType->setGeometry(85, 25, 70,20);
   marginType->addItem("none");
      vlabel->setGeometry(0,25,85,25);
//    pick->setGeometry(60,0,55,25);
   boldMargin->setGeometry(0,50,160,25);
   boldMargin->edit->setGeometry(85,0,40,19);
   boldMargin->name->setGeometry(0,0,85,19);
   boldMargin->name->setText("Толщина");
   boldMargin->name->setStyleSheet("font: 300 10pt 'Ubuntu Light';"
                               "color: #6f6f6f;"
                               "");
   boldMargin->name->setAlignment(Qt::AlignLeft);
   vedit->name->setStyleSheet("font: 300 10pt 'Ubuntu Light';"
                              "color: #6f6f6f;"
                              "");
   vedit->name->setAlignment(Qt::AlignLeft);
  pick->setGeometry(85,75,45,19);
   QLabel * plabel = new QLabel(this);
   plabel->setGeometry(0,75,85,19);
   plabel->setText("Цвет");
   plabel->setAlignment(Qt::AlignLeft);
   plabel->setStyleSheet("font: 300 10pt 'Ubuntu Light';"
                              "color: #6f6f6f;"
                              "");
  // bold->setGeometry(0,100,85,19);


  connect (vedit->edit,&QLineEdit::textChanged,this,&panelMargins::updateData); //внутренние границы коннект
   connect (pick->line,&QLineEdit::textChanged,this,&panelMargins::updateData);
   connect (marginType,&QComboBox::currentTextChanged,this,&panelMargins::updateData);
    //connect (pick->line,&QLineEdit::textChanged,this,&panelMargins::updateData);
   connect (boldMargin->edit,&QLineEdit::textChanged,this,&panelMargins::updateData);
   marginType->addItem("outset");
    marginType->addItem("slit");
       marginType->addItem("inset");
}

QString panelMargins::getMArginInside()
{
return vedit->edit->text();
}

QString panelMargins::getColorBorder()
{
return pick->line->text();
}

QString panelMargins::getTypeBorder()
{
return marginType->currentText();
}

QString panelMargins::getBoldBorder()
{
    return boldMargin->edit->text();
}

void panelMargins::updateData()
{
 emit onDataUpdate();
}
