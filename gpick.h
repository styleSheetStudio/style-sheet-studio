#ifndef GPICK_H
#define GPICK_H

#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QColorDialog>
#include <gradientpicker.h>

class GPick : public QWidget
{
    Q_OBJECT
public:
    explicit GPick(QWidget *parent = nullptr);

     QPushButton *btn;
     QLineEdit *line;
     QString tcolor1;
     QColor color;
     bool toogle=false;
     QString FinalSS;
    GradientPicker *gpicks = new GradientPicker();
private:
   // QWidget *ssv = new QWidget;
    int value = 0;

    void on_btn_click();
    bool current;
 QLabel *ssv = new QLabel;

signals:




};

#endif // GPick_H
