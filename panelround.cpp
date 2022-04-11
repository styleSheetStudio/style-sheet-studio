#include "panelround.h"
#include "allstylesheet.h"
panelRound::panelRound(QWidget *parent)
    : QWidget(parent)
{
    this->setStyleSheet(AllstyleSheet::getPanelCSS());
     this->setFixedSize(200,125);

roundp->setGeometry(0,0,130,25);
roundp->name->setText("Скругление");
roundp->edit->setGeometry(85,0,40,19);
roundp->name->setGeometry(0,0,85,19);
roundp->name->setStyleSheet("font: 300 10pt 'Ubuntu Light';"
                           "color: #6f6f6f;"
                           "");
roundp->name->setAlignment(Qt::AlignLeft);
enableRound->setGeometry(145,0,25,25);
enableRound->setChecked(true);
enableRound->setText("");
  connect (roundp->edit,&QLineEdit::textChanged,this,&panelRound::updateData);
    connect (enableRound,&QCheckBox::clicked,this,&panelRound::updateData);
}

QString panelRound::getRound()
{
    return roundp->edit->text();
}

void panelRound::updateData()
{
    emit onDataUpdate();
}
