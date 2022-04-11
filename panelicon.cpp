#include "panelicon.h"
#include "allstylesheet.h"
panelIcon::panelIcon(QWidget *parent)
    : QWidget(parent)
{
    this->setStyleSheet(AllstyleSheet::getPanelCSS());
    this->setFixedSize(200,125);
      QLabel *ilabel = new QLabel(this);
      ilabel->setText("Иконка");
      ilabel->setStyleSheet("font: 300 10pt 'Ubuntu Light';"
                           "color: #6f6f6f;");
      ilabel->setAlignment(Qt::AlignLeft);
      ilabel->setGeometry(0,0,60,25);
      pathEdit->setGeometry(60,0,120,19);
      pathBtns->setGeometry(181,0,19,19);
      pathBtns->setText("..");

      editRepeat->setGeometry(60,25,85,19);
      rlabel = new QLabel(this);
      rlabel->setGeometry(0,25,60,25);
      rlabel->setText("Repeat");
      rlabel->setStyleSheet("font: 300 10pt 'Ubuntu Light';"
                            "color: #6f6f6f;");

      rlabel->setAlignment(Qt::AlignLeft);
      editPos->setGeometry(60,50,85,19);
     plabel = new QLabel(this);
      plabel->setGeometry(0,50,60,25);
      plabel->setText("Позиция");
      plabel->setStyleSheet("font: 300 10pt 'Ubuntu Light';"
                                     "color: #6f6f6f;");
      plabel->setAlignment(Qt::AlignLeft);

    //  QString filename =   QFileDialog::getOpenFileName(this, "Открыть файл*", "","все(*_*);;Текстовые (*.txt);;c, c++(*.h *.cpp);;Markup Languages(*.xml *.json *qml *yaml *js);;");
      connect (pathBtns,&QPushButton::clicked,this,&panelIcon::updatePath);
      connect (pathEdit,&QLineEdit::textChanged,this,&panelIcon::dataUpdate);
      connect (editPos,&QComboBox::currentTextChanged,this,&panelIcon::dataUpdate);
     connect (editRepeat,&QComboBox::currentTextChanged,this,&panelIcon::dataUpdate);
     editRepeat->addItem("no-repeat");
        editRepeat->addItem("repeat");

        editPos->addItem("bottom right");
           editPos->addItem("bottom left");
           editPos->addItem("bottom");
              editPos->addItem("top");
              editPos->addItem("center right");
                 editPos->addItem("center left");
                 editPos->addItem("center");
}

void panelIcon::setupCheckBox()
{
    editRepeat->setVisible(false);
   delete editRepeat;
    editPos->setVisible(false);
   delete editPos;

  editWidth = new TextEditLabel(this);
   editHeight = new TextEditLabel(this);
   editWidth->setGeometry(0,25,100,19);
   editWidth->name->setText("ширина");
   editWidth->name->setStyleSheet("font: 300 10pt 'Ubuntu Light';"
                                                "color: #6f6f6f;");

                        editWidth->name->setAlignment(Qt::AlignLeft);


   editHeight->setGeometry(0,50,100,19);
   editHeight->name->setText("высота");
   editHeight->name->setStyleSheet("font: 300 10pt 'Ubuntu Light';"
                                                "color: #6f6f6f;");

                        editHeight->name->setAlignment(Qt::AlignLeft);

   plabel->setVisible(false);
   delete plabel;
   rlabel->setVisible(false);
   delete rlabel;
     connect(editWidth->edit,&QLineEdit::textChanged,this,&panelIcon::dataUpdate);
           connect (editHeight->edit,&QLineEdit::textChanged,this,&panelIcon::dataUpdate);
}

QString panelIcon::getIconPath()
{
 return pathEdit->text();
}

QString panelIcon::getHeight()
{
return editHeight->edit->text();
}

QString panelIcon::getWidth()
{
return editWidth->edit->text();
}

QString panelIcon::getRepeat()
{
   return editRepeat->currentText();
}

QString panelIcon::getPos()
{
return editPos->currentText();
}

void panelIcon::dataUpdate()
{
    emit onDataChanged();
}

void panelIcon::updatePath()
{
    fileIconPath = QFileDialog::getOpenFileName(this, "Выберите путь*", "","все(*_*);;Images(*.png *.jpg *jpeg);;");
    pathEdit->setText(fileIconPath);
}
