#ifndef MARKER_H
#define MARKER_H

#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
#include <QStyleOption>
#include <QPainter>
#include <QColorDialog>
#include <defines.h>
#include <time.h>
#include "QTimer"
class QWidget;

class Marker : public QPushButton
{
    Q_OBJECT
public:
    Marker(QWidget *parent=nullptr);
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
      virtual void mouseDoubleClickEvent(QMouseEvent *event);

      Gmarker getData();

      QString y_string;
 bool ib;
   bool  unpressed = true;


    static int ResID;   // Статическая переменная, счетчик номеров кнопок
    int getID();
    //перемеменные экземпляра маркера...
    QString color_string;
    QString BufSS;
  QColor colorDlg;

    QString pos_x_string;
    void getId();
    int id;
public:
    QColor getNewColor();
    // Функция для возврата локального номера кнопки
    void setValueY(double value);
    void remove();
private:
    double y_tmp;
    double pos_x;
     QPoint oldPos;
     int buttonID = 0;
     int b;// Локальная переменная, номер кнопки
     QTimer post;
     QString buffercolor;
     QColor newColor;
signals:
     void changeColor(QColor);


     private slots:




};

#endif // MARKER_H
