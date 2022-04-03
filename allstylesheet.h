#ifndef ALLSTYLESHEET_H
#define ALLSTYLESHEET_H

#include <QObject>

class AllstyleSheet : public QObject
{
    Q_OBJECT



public:
    static QString getMainWidgetStyle();
    static QString getScrollWidgetStyle();
    static QString SelectTabButton();
    static QString NoSelectTabButton();
    static QString panel_objects();
    static QString getPushBottonToolNormal();
    static QString getPushBottonToolActive();
    static QString getCheckBoxToolNormal();
    static QString getCheckBoxToolActive();
    static QString BWOPN();
    static QString BWOPH();
           QString icon_name;
    static QString content_widget();
    static QString select_title_btn();
    static QString No_select_title_btn();
    static QString scrollArea();

    static QString getCBoxToolNormal(); //ComboBox
    static QString getCBoxToolActive();


   static QString getTabWNormal();
   static QString getTabWActive();
   static QString getSBOXNormal();
   static QString getSBOXActive();
   static QString getListWNormal();
   static QString getListWActive();
   static QString getLineEditNormal();
   static QString getLineEditActive();
   static QString getRadioBtnNormal();
   static QString getRadioBtnActive();

   static QString getLabelNormal();
   static QString getLabelActive();

  static QString getCBOXNormal();
  static QString getCBOXActive();

   static QString getTextEditNormal();
      static QString getTextEditActive();

      static QString getToolBtnActives();
   static QString getToolBtnNormal();

   static QString normal_btns();
   static QString active_btns();

signals:

};

#endif // ALLSTYLESHEET_H
