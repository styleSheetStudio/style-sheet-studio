#ifndef PANEL_H
#define PANEL_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPaintEvent>
#include "texteditlabel.h"
#include "titlebutton.h"
#include "defines.h"
#include "gpick.h"
#include "QComboBox"
#include "paneltext.h"
#include "panelbackground.h"
#include "panelmargins.h"
#include "panelicon.h"
#include "panelround.h"
#include "panelgeometry.h"
#include "stylecontent.h"
#include "allstylesheet.h"

class Panel : public QWidget
{
    Q_OBJECT
public:
    explicit Panel(QWidget *parent = nullptr);
   Panel(QString type, QString name, QString status,QString tool, QWidget *parent = nullptr);
    Tools  currentTool = PUSH_BUTTON_TOOL ;
    PanelTypes types;
    QString panelType ;//= "PANEL_GEOMETRYS";
     int getID();
    int getCur();

    QString getTypePanel();
    QString getStatus();
   void setName(QString name);
    void setType(QString type);
    QString name;
    QString type;
    QString getTool();
    QString toolchain;
    QString GetStatus();
static int ResID;

    //QPUSHNUTTON
    //PANEL_GEOMETRY
    TextEditLabel *editS = new TextEditLabel;
    TextEditLabel *editH = new TextEditLabel;

    //PANEL_TEXT
     PanelText * pn = new PanelText(this); //Элемент части PANEL_TEXT
     panelBackground *contentBackground = new panelBackground(this);
     panelMargins *contentMargins = new panelMargins(this);
     panelIcon *contentIcon = new panelIcon(this);
     panelRound *contentRound = new panelRound(this);
       panelGeometry *contentGeometry = new panelGeometry(this);
        styleContent *stylesContent = new styleContent(this);
    //PANEL_MARGINS
    //PANEL_BACKGROUND
   GPick * gpicker = new GPick(this);







signals:
    void changeData(QString, QString, QString, int, bool);
public slots:
    void changeContentVisible();
    void  onGetData();
protected:
    TitleButton *titleButton;

    QVBoxLayout *vbox;
    QWidget *contentWidget;
    QGridLayout *contentbox;

    void paintEvent(QPaintEvent *);
private:
  bool contentVisible = false;
  int buttonID = 0;
  int cur;
  QString typep;
QString statuss;

};

#endif // PANEL_H
