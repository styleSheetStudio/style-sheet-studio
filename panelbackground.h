#ifndef PANELBACKGROUND_H
#define PANELBACKGROUND_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <texteditlabel.h>
#include <QPainter>
#include <colorpicker.h>
#include <gpick.h>
class panelBackground : public QWidget
{
    Q_OBJECT
public:
    explicit panelBackground(QWidget *parent = nullptr);

    //Margins
  //  TextEditLabel *EditMargins;
  //  TextEditLabel *leftMargin;
  //  TextEditLabel *rightMargin;
  //  TextEditLabel *topMargin;
   // TextEditLabel *bottomMargin;


    //Background
     GPick *Gradient = new GPick(this);
     colorPicker *pick = new colorPicker(this);
     QComboBox *style = new QComboBox(this);

QString getGradient();
QString getColor();
QString getStyle();

private slots:
void updateData();
void onstyle();
void ongradient();
void oncolor();

signals:
void onDataUpdate();
};

#endif // PANELBACKGROUND_H
