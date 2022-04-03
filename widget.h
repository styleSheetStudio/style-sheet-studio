#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <allstylesheet.h>
#include <QMenu>
#include <QVBoxLayout>
#include "panel.h"
#include <QScrollArea>
#include "defines.h"
#include <QVector>
#include <dynamicwidgettool.h>
#include <QFile>
#include <notificationpopup.h>
#include <highlighter.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QString, QWidget *parent = nullptr);

    ~Widget();
QFile * fileProject;
    QString str;
    void openProject(QString filePath);
    void code();
    void newProject(QString fileName);
    QStringList strList;
    QString slate_object;
   QString projectCodeFile;
    QString becn ; //button example code normal
     QString becp; //button example code pressed
      QString bech; //button example code hover


       QString leech;
       QString noSelectStyle, SelectStyle;

int wdt_ID=0;
 QVBoxLayout *box = new QVBoxLayout();

QString ResultCodeSS;

private:
    Ui::Widget *ui;
    QMenu *menu;
    QString dwt_status;
    Highlighter*  highlighter;
    bool first_normal=true;
    QString currentToolchain;
    bool first_hover=true;
    bool first_pressed=true;
    QString fileNames;
QString QtDesignerSS;
    void codeEdit(bool status,QStringList list);
    void addPanel(QString);
    void updateAllData(QString, QString, bool);
    void setStyleFromFile(QStringList normal, QStringList hover, QStringList pressed, QString ttool);
   QString col;
    QVBoxLayout *rightbox;
  bool check = true;
    void setAplicationMenu();
    void tabUpdateButtons();
    void changeActivTool();
    void changeWorkAreaContent();
    void setPanelGroup();
    void clearActivStateTools();
   QStringList SSBuffer;
    Tools currentTool;
   int ID_PANEL;
    void removeAllPanels();
    void setPushButtonPanels();
    void setCheckBoxPanels();
    void setLabelPanels();
    void   setCBOXPanels();
    void setLeditPanels();
    void  setListWPanels();
    void    setRadioBtnPanels();
        void onDataChanged(QString PanelType, QString ToolType, QString status, int ID, bool cycle);
    void  setSBOXPanels();
    void   setTabWPanels();
    void   setTeditPanels();
    void  setTBTNPanels();
    void insertTOList(int);
    void updateColNumbers(int, bool, bool);



    QStringList indicators;
   bool tool_button_slate = false;
   void tool_button();
   void SetSSDWT(QString panelType, QString toolType, QString status, int, bool); //setVISual coding
   void SetCodeSS(QString panelType, QString toolType, QString status);
   QStringList SSText;
   QString statusWidget;
   int indexProperty;
    //   QStringList strList;

   //index Lists

    int TextFont=0;
    int TextColor=1;
    int TextAlign=2;
    int BackgroundColor =3;
    int BackgroundImage =4;
    int BackgroundRepeate =5;
    int BackgroundPosition =6;
    int Round = 7;
    int MarginWidth =8;
    int MarginStyle=9;
       int MarginColor=10;
       int MarginPadding=11;
  int CheckBox=0;
    int   CloseCheckBox=6;
     int CheckBoxIndicator=7;
     int CloseCheckBoxIndicator;
       int Image=8;
        int PWidth=9;
       int PHeight=10;
        int CheckBoxChecked=0;
      int CloseCheckBoxChecked=4;


         //int Image=4;
     //PanelText font
    bool codeError;

    bool codeCycle = false;

    bool btnn=true;
    bool btnp=true;
    bool btnh=true;

    bool cboxn=true;
    bool cboxp = true;
    bool cboxh=true;

    bool labeln=true;
    bool labelh=true;


    bool setPushButton = true;
    bool setCBox = true;
    bool setLabel = true;
signals:

private slots:
    void showMenu();

    void on_code_edit_textChanged();
    void newPanel(QString type, QString status);
   void tabContextMenuOpen(QPoint points);

   void close();
   void saveAs();
   void home();

    void on_copyWidgetSS_clicked();
    void on_copySS_clicked();
    void on_pushButton_3_clicked();
    void on_checkbox_b_clicked();


};
#endif // WIDGET_H
