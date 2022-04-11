#include "panelgeometry.h"
#include "allstylesheet.h"

panelGeometry::panelGeometry(QWidget *parent)
    : QWidget(parent)
{
    this->setFixedSize(200,53);
this->setStyleSheet(AllstyleSheet::getPanelCSS());
      widthEdit->setGeometry(0,0,130,25);
      widthEdit->name->setText("Ширина");
      widthEdit->name->setAlignment(Qt::AlignLeft);
        widthEdit->name->setStyleSheet("font: 300 10pt 'Ubuntu Light';"
                                       "color: #6f6f6f;");

        heightEdit->setGeometry(0,25,130,25);
        heightEdit->name->setText("Высота");
        heightEdit->name->setAlignment(Qt::AlignLeft);
        heightEdit->name->setStyleSheet("font: 300 10pt 'Ubuntu Light';"
                                        "color: #6f6f6f;");
        connect (heightEdit->edit,&QLineEdit::textChanged,this,&panelGeometry::updateData);
        connect (widthEdit->edit,&QLineEdit::textChanged,this,&panelGeometry::updateData);
}

void panelGeometry::updateData()
{
    emit onDataUpdate();
}
