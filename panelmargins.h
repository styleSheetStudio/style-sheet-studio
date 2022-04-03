#ifndef PANELMARGINS_H
#define PANELMARGINS_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <colorpicker.h>
#include <texteditlabel.h>
class panelMargins : public QWidget
{
    Q_OBJECT
public:
    explicit panelMargins(QWidget *parent = nullptr);
    QComboBox *vbox = new QComboBox(this);
    QComboBox *marginType = new QComboBox(this);
    TextEditLabel  *boldMargin = new TextEditLabel(this);
    colorPicker *pick = new colorPicker(this);
    TextEditLabel *vedit = new TextEditLabel(this);
   // QComboBox *typeBorder = new QComboBox(this);
   // TextEditLabel  *bold = new TextEditLabel (this);
  //  QComboBox *posBorder = new QComboBox(this);
   QString getMArginInside();
   QString getColorBorder();
   QString getTypeBorder();
   QString getBoldBorder();
   QColor color;
   void updateData();
signals:
  void onDataUpdate();

};

#endif // PANELMARGINS_H
