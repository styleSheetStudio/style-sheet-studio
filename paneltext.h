#ifndef PANELTEXT_H
#define PANELTEXT_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <texteditlabel.h>
#include <QPainter>
#include <colorpicker.h>
#include <QCheckBox>

class PanelText : public QWidget
{
    Q_OBJECT
public:
    explicit PanelText(QWidget *parent = nullptr);
    QString getColor();
    QString getFont();
    QString getSizeF();
    int getAlignmentF();
    QString getBoldText();
    QComboBox *AlignBox = new QComboBox(this);//Выравнивание
    QComboBox *TText = new QComboBox(this);//шрифт комбобокс
    TextEditLabel *TPixel = new TextEditLabel(this);//размер текста
    colorPicker * pick = new colorPicker(this);//цвет текста пикер
    TextEditLabel *Bold = new TextEditLabel(this);
    QCheckBox *enableText = new QCheckBox(this);
    bool cycle = false;

private:

signals:
    void changeData();

protected:
    void paintEvent(QPaintEvent *);
 private slots:
    void updateData();

  //  void updateTText();
 //   void updateAlignText();
   // void updateColor();
};

#endif // PANELTEXT_H
