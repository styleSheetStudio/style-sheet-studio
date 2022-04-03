#include "paneltext.h"
#include "QDebug"
#include "QCheckBox"
PanelText::PanelText(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(200,150);


    TPixel->edit->setText("10");
    Bold->edit->setText("200");

    //labelT->setText("Размер");
    //labelT->setGeometry(0,0,40,20);
    TPixel->setGeometry(0,0,160,25);
    TPixel->name->setText("Размер");
    TPixel->name->setStyleSheet("font: 300 10pt 'Ubuntu Light';"
                                "color: #6f6f6f;"
                                "");
    TPixel->name->setAlignment(Qt::AlignLeft);
    connect(TPixel->edit,&QLineEdit::textChanged,this,&PanelText::updateData);
    connect(Bold->edit,&QLineEdit::textChanged,this,&PanelText::updateData);
    connect (TText,&QComboBox::currentTextChanged,this,&PanelText::updateData);
    connect (pick,&colorPicker::changeColor,this,&PanelText::updateData);
    connect (pick,&colorPicker::changeColor,this,&PanelText::updateData);
    connect (AlignBox,&QComboBox::currentTextChanged,this,&PanelText::updateData);
    Bold->setGeometry(0,102,125,20);
    Bold->name->setText("Толщина");

    QLabel * Textl = new QLabel(this);
    Textl->setText("Шрифт");
    Textl->setGeometry(0,25,55,25);
    Textl->setStyleSheet("font: 300 10pt 'Ubuntu Light';"
                         "color: #6f6f6f;");
    Textl->setAlignment(Qt::AlignLeft);

    TText->setGeometry(59,25,125,20);

    AlignBox->setGeometry(59,50,125,20);
    QLabel * TextA = new QLabel(this);
    TextA->setText("Align");
    TextA->setGeometry(0,50,55,25);
    TextA->setStyleSheet("font: 300 10pt 'Ubuntu Light';"
                         "color: #6f6f6f;");
    TextA->setAlignment(Qt::AlignLeft);

    pick->setGeometry(59,75,55,25);
    QLabel *textC = new QLabel(this);
    textC->setText("Цвет");
    textC->setGeometry(0,75,55,25);
    textC->setStyleSheet("font: 300 10pt 'Ubuntu Light';"
                         "color: #6f6f6f;");

    textC->setAlignment(Qt::AlignLeft);
    Bold->name->setStyleSheet("font: 300 10pt 'Ubuntu Light';"
                              "color: #6f6f6f;");
    //Items Font combo box
    TText->addItem("Ubuntu");
    TText->addItem("Ubuntu mono");
    TText->addItem("Ubuntu light");
    TText->addItem("Times new roman");
    //Items Align comboBox
    AlignBox->addItem("Левый край");
    AlignBox->addItem("Сверху центр");
    AlignBox->addItem("Центр");
    AlignBox->addItem("Снизу центр");
    AlignBox->addItem("Правый край");

    QLabel *textT = new QLabel(this);
    textT->setText("Текст");
    textT->setGeometry(0,125,55,25);
    textT->setStyleSheet("font: 300 10pt 'Ubuntu Light';"
                         "color: #6f6f6f;");
    enableText->setGeometry(60,125,25,25);
    enableText->setText("");
    connect (AlignBox,&QComboBox::currentTextChanged,this,&PanelText::updateData);
    connect(enableText,&QCheckBox::clicked,this,&PanelText::updateData);
    updateData();

}

QString PanelText::getColor()//Возвращает ЦВЕТ текста
{
    return pick->color.name();
    // emit changeData();

}

QString PanelText::getFont()
{
    return TText->currentText();
    // emit changeData();

}

QString PanelText::getSizeF() //Возвращает размер текста
{
    return TPixel->edit->text();
    // emit changeData();
}

int PanelText::getAlignmentF()
{
    return AlignBox->currentIndex();
    //emit changeData();
}

QString PanelText::getBoldText()
{
    return Bold->edit->text();
}
void PanelText::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);


}

void PanelText::updateData()
{
    if(cycle==true){
        return;
    }else{
         emit changeData();
    }

}

