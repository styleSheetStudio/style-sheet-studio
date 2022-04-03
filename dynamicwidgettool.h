#ifndef DYNAMICWIDGETTOOL_H
#define DYNAMICWIDGETTOOL_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>
#include <QPaintDevice>
#include <QPaintEvent>
#include <QStyleOption>
#include <QCheckBox>




class DynamicWidgetTool : public QWidget
{
    Q_OBJECT
public:
    explicit DynamicWidgetTool(QWidget *parent = nullptr);
  static int ResID;
 DynamicWidgetTool(QString type, int ID, QString currentTool, QWidget *parent = nullptr);
 //PushButtonTool
 QPushButton *btnNormal;
  QPushButton *btnPressed;
   QPushButton *btnHover;

   QCheckBox *cboxNormal;
      QCheckBox *cboxPressed;
         QCheckBox *cboxHover;

         QLabel * labelNormal;
         QLabel * labelHover;
         QLabel * labelPressed;
QString curtool;
         QString getTool();
       int getID();
       QStringList SSBuffer_nor;
       QStringList SSBuffer_hover;
       QStringList SSBuffer_pressed;

QString types;
  QString getType();
       int NTextFont=0;
       int NTextColor=1;
       int NTextAlign=2;
       int NBackgroundColor =3;
       int NBackgroundImage =4;
       int NBackgroundRepeate =5;
       int NBackgroundPosition =6;
       int NRound = 7;
       int NMarginWidth =8;
       int NMarginStyle=9;
          int NMarginColor=10;
          int NMarginPadding=11;
           int NImage=12;
           int Nwidth;
           int NHeight;
          int HCheckBoxChecked=0;
          int HImage=1;
          int Hwidth=2;
          int HHeight=3;
          int HCloseCheckBoxChecked=4;
         int NCheckBoxIndicator;
         int NCloseCBoxIndicatorClose;

         int HCheckBox=13;
           //int HCheckBoxChecked=14;
           int HCloseCheckBox=15;
           int NCheckBox=13;
             //int HCheckBoxChecked=14;
             int NCloseCheckBox=15;
           // int HCloseCheckBoxChecked=16;

          int HTextFont=0;
          int HTextColor=1;
          int HTextAlign=2;
          int HBackgroundColor =3;
          int HBackgroundImage =4;
          int HBackgroundRepeate =5;
          int HBackgroundPosition =6;
          int HRound = 7;
          int HMarginWidth =8;
          int HMarginStyle=9;
             int HMarginColor=10;
             int HMarginPadding=11;

             int PTextFont=0;
             int PTextColor=1;
             int PTextAlign=2;
             int PBackgroundColor =3;
             int PBackgroundImage =4;
             int PBackgroundRepeate =5;
             int PBackgroundPosition =6;
             int PRound = 7;
             int PMarginWidth =8;
             int PMarginStyle=9;
                int PMarginColor=10;
                int PMarginPadding=11;

private:
     void updatePanel();
          int buttonID = 0;
private slots:



     void btnNormalUpdate();
     void btnHoverUpdate();
     void btnPressedUpdate();
    void cboxPressedUpdate();
     void cboxNormalUpdate();
     void cboxHoverUpdate();

         void labelNormalUpdate();
         void labelHoverUpdate();
         void labelPressedUpdate();
     //void cboxPressedUpdate();
protected:
  void paintEvent(QPaintEvent *);
signals:
  void newPanel(QString,QString);
};

#endif // DYNAMICWIDGETTOOL_H
