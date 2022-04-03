#ifndef COLORPICKER_H
#define COLORPICKER_H

#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QColorDialog>

class colorPicker : public QWidget
{
    Q_OBJECT
public:
    explicit colorPicker(QWidget *parent = nullptr);

     QPushButton *btn;
     QLineEdit *line;
     QString tcolor1;
     QColor color;
     bool toogle=false;
private:

    int value = 0;

    void on_btn_click();
    bool current;


signals:
void changeColor(QColor);



};

#endif // COLORPICKER_H
