#include "allstylesheet.h"

/*************** Стиль основного виджета ******************
 В данном случае основной виджет играет роль фона, поэтому
 единственное свойство - это цвет фона.
*/
QString AllstyleSheet::getMainWidgetStyle()
{
    return "QWidget{"
                "background-color:rgb(247,247,247);" //более приятная глазу политра
            "}";
}


/*************** Цвет фона виджета для панелей справа *****************/
QString AllstyleSheet::getScrollWidgetStyle()
{
    return "QWidget{"
                "background-color:rgb(235,235,235);"
            "}";
}


QString AllstyleSheet::SelectTabButton()
{
    return "QPushButton{"
                "border-top:none;"
                "border-bottom:2px solid #ccc;"
                "border-left:none;"
                "border-right:none;"
                "background-color: transparent;"
             "}";
}

QString AllstyleSheet::NoSelectTabButton()
{
    return "QPushButton{"
                "border-top:none;"
                "border-bottom:2px solid transparent;"
                "border-left:none;"
                "border-right:none;"
                "background-color:transparent;"
             "}";
}
QString AllstyleSheet::select_title_btn()
{
    return     "QPushButton{"
        "border:none;"                      //Запрещаем весь border
        "border-bottom: 2px solid #ccc;"     //Устанавливаем нижний border
        "font-size:12px;"                   //Размер шрифта
        "color:#777;"                       //Цвет текста
        "text-align:left;"                  //Горизонтальное выравнивание
        "background: rgb(235,235,235);"                  //Цвет фона
        "padding:10px;"                     //Внутренний отступ
        "background-image: url(:/icons/images/minusic.png);"
        "background-repeat: no-repeat;"
        "background-position: center right;"
    "}";
}

QString AllstyleSheet::No_select_title_btn()
{
    return     "QPushButton{"
        "border:none;"                      //Запрещаем весь border
        "border-bottom:2px solid #ccc;"     //Устанавливаем нижний border
        "font-size:12px;"                   //Размер шрифта
        "color:#777;"                       //Цвет текста
        "text-align:left;"                  //Горизонтальное выравнивание
        "background:rgb(235,235,235);"                  //Цвет фона
        "padding:10px;"                     //Внутренний отступ
        "background-image: url(:/icons/images/plus.png);"
        "background-repeat: no-repeat;"
        "background-position: center right;"
    "}";
}
QString AllstyleSheet::content_widget()
{
    return

        "background: rgb(230,230,230);"     //Цвет фона

    ;
}
QString AllstyleSheet::scrollArea(){
    return
"QScrollArea {"
"border: none"
"}"
            "QScrollBar:vertical {"
               "border: none;"
               "background: rgb(225,225,225);"
               "width: 14px;"
               "margin: 10px 0 10px 0;"
               "border-radius: 0px;"
            "}"


           "QScrollBar::handle:vertical {"
              "background-color: rgb(195, 195, 195);"
             "min-height: 30px;"
            "border-radius: 7px;"
           "}"
           "QScrollBar::handle:vertical:hover{"
            "   background-color: rgb(175, 175, 175);"
           "}"
           "QScrollBar::handle:vertical:pressed {"
            "   background-color: rgb(150, 150, 150);"
           "}"


           "QScrollBar::sub-line:vertical {"
               "border: none;"
               "background-color: rgb(195, 195, 195);"
               "height: 10px;"
               "border-top-left-radius: 0px;"
               "border-top-right-radius: 0px;"
               "subcontrol-position: top;"
               "subcontrol-origin: margin;"
           "}"
           "QScrollBar::sub-line:vertical:hover {"
               "background-color: rgb(175, 175, 175);"
           "}"
           "QScrollBar::sub-line:vertical:pressed {"
               "background-color: rgb(150, 150, 150);"
           "}"


           "QScrollBar::add-line:vertical {"
               "border: none;"
               "background-color: rgb(195, 195, 195);"
               "height: 10px;"
               "border-bottom-left-radius: 0px;"
               "border-bottom-right-radius: 0px;"
               "subcontrol-position: bottom;"
               "subcontrol-origin: margin;"
           "}"
           "QScrollBar::add-line:vertical:hover {"
               "background-color: rgb(175, 175, 175);"
           "}"
           "QScrollBar::add-line:vertical:pressed {"
            "background-color: rgb(150, 150, 150);"
           "}"

           "QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical {"
            "   background: none;"
           "}"
           "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
               "background: none;"
           "}";
}

QString AllstyleSheet::BWOPH()
{
    // return
}





/*********************************************************
************** Кнопки инструментов слева *****************
**********************************************************/

/*************** Цвет фона панели инструментов *****************/
QString AllstyleSheet::panel_objects()
{
    return "background-color: rgb(255, 255, 255);";
}

/*************** PushButton *****************/
QString AllstyleSheet::getPushBottonToolActive()
{
    return "QPushButton {"
                "background-color: rgb(255, 255, 255);"
                "image: url(:/icons/images/pushButtonSelect.png);"
                "border:none;"
            "}";

}
QString AllstyleSheet::getPushBottonToolNormal()
{

    return "QPushButton {"
                "background-color: rgb(255, 255, 255);"
                "image: url(:/icons/images/pushButton.png);"
                "border:none;"
            "}"
            "QPushButton:hover{"
                "image: url(:/icons/images/pushButtonHover.png);"
                "background-color: rgb(210, 210, 210);"
            "}";

}

/*************** CheckBox button*****************/
QString AllstyleSheet::getCheckBoxToolActive()
{
    return "QPushButton {"
                "background-color: rgb(0, 0, 0);"
                "background-color: rgba(255, 255, 255, 0);"
                "image: url(:/icons/images/checkBoxSelect.png);"
            "}"
            ;

}
QString AllstyleSheet::getCheckBoxToolNormal()
{
    return "QPushButton {"
                "background-color: rgb(255, 255, 255);"
                "image: url(:/icons/images/checkBox.png);"
                "border:none;"
            "}"
            "QPushButton:hover{"
                "image: url(:/icons/images/checkBoxHover.png);"
                "background-color: rgb(210, 210, 210);"
            "}";

}

/*************** ComboBox button *****************/
QString AllstyleSheet::getCBoxToolActive()
{
    return "QPushButton {"

                "background-color: rgba(255, 255, 255, 0);"
                "image: url(:/icons/images/comboBoxSelect.png);"
            "}"
            ;

}
QString AllstyleSheet::getCBoxToolNormal()
{
    return "QPushButton {"
                "background-color: rgb(255, 255, 255,0);"
                "image: url(:/icons/images/comboBox.png);"
                "border:none;"
            "}"
            "QPushButton:hover{"
                "image: url(:/icons/images/comboBoxHover.png);"
                "background-color: rgb(255, 255, 255, 0);"
            "}";

}
/*************** RadioButton button*****************/
QString AllstyleSheet::getRadioBtnActive()
{
    return "QPushButton {"

                "background-color: rgba(255, 255, 255, 0);"
                "image: url(:/icons/images/radioSelect.png);"
            "}"
            ;

}

QString AllstyleSheet::getLabelNormal()
{
    return
    "QPushButton {"

       " background-color: rgba(255, 255, 255, 0);"


        "image: url(:/icons/images/label.png);"
    "}"

    "QPushButton:hover {"

       "image: url(:/icons/images/labelHover.png);"
    "}"

    "QPushButton:flat {"
      "  border: none; /* no border for a flat push button */"
    "}"

    "QPushButton:default {"
        "border-color: navy; /* make the default button prominent */"
    "}";
}

QString AllstyleSheet::getLabelActive()
{
    return
    "QPushButton {"

       " background-color: rgba(255, 255, 255, 0);"


        "image: url(:/icons/images/labelSelect.png);"
    "}";

}

QString AllstyleSheet::getCBOXNormal()
{
    return
    "QPushButton {"

       " background-color: rgba(255, 255, 255, 0);"


        "image: url(:/icons/images/comboBox.png);"
    "}"

    "QPushButton:hover {"

       "image: url(:/icons/images/comboBoxHover.png);"
    "}"

    "QPushButton:flat {"
      "  border: none; /* no border for a flat push button */"
    "}"

    "QPushButton:default {"
        "border-color: navy; /* make the default button prominent */"
    "}";
}

QString AllstyleSheet::getCBOXActive()
{
    return
    "QPushButton {"

       " background-color: rgba(255, 255, 255, 0);"


        "image: url(:/icons/images/comboBoxSelect.png);"
    "}";
}

QString AllstyleSheet::getTextEditNormal()
{
    return
    "QPushButton {"

       " background-color: rgba(255, 255, 255, 0);"


        "image: url(:/icons/images/textEdit.png);"
    "}"

    "QPushButton:hover {"

       "image: url(:/icons/images/textEditHover.png);"
    "}"

    "QPushButton:flat {"
      "  border: none; /* no border for a flat push button */"
    "}"

    "QPushButton:default {"
        "border-color: navy; /* make the default button prominent */"
    "}";
}

QString AllstyleSheet::getTextEditActive()
{
    return
    "QPushButton {"

       " background-color: rgba(255, 255, 255, 0);"


        "image: url(:/icons/images/textEditSelect.png);"
    "}";
}

QString AllstyleSheet::getPanelCSS()
{
return
      " QComboBox"
       " {"
        "    border: 2px solid rgba(0, 0, 0, 102);"
         "   padding-left: 10px;"
          "  padding-right: 10px;"
           " padding-top: 3px;"
           " padding-bottom: 4px;"
            "   background: rgb(255, 255, 255);"
       "}"
      "QPushButton"
"{"
    "background: rgb(255, 255, 255);"
    "border: 2px solid transparent;"
    "padding-left: 14px;"
    "padding-right: 14px;"
    "padding-top: 4px;"
    "padding-bottom: 4px;"
"}"

"QPushButton:hover"
"{"
  "  border: 2px solid rgba(0, 0, 0, 102);"
"}"

"QPushButton:pressed"
"{"
 "  border: 2px solid transparent;"
    "background: rgba(0, 0, 0, 102);"
"}"



        "QComboBox:hover:!pressed"
        "{"
         "border-color: rgb(102, 102, 102);"
        "}"

       " QComboBox::pressed"
        "{"
         "   background: rgb(204, 204, 204);"
        "}"

        "QComboBox QAbstractItemView"
         "{"
          "border: 1px solid rgb(204, 204, 204);"

         "selection-background-color: lightgray;"
          "padding-left: 9px;"
         "padding-right: 9px;"
        "background:  rgb(255, 255, 255);"
       "}"

        "QComboBox QAbstractItemView::item"
        "{"
         "   padding-top: 3px;"
        "   padding-bottom: 4px;"
       "}"


       " QComboBox::drop-down"
        "{"
          "  border: none;"
         "  padding-right: 8px;"
        "}"

        "QComboBox::down-arrow"
        "{"
          "  image: url(:/style/images/checkbox_down_arrow.svg);"
         "height: 6px;"
        "width: 12px;"
       "}"
        "QLineEdit{"
         "background: rgb(255, 255, 255);"
           "color: rgb(0, 0, 0);"
          "border: 2px solid rgba(0, 0, 0, 102);"

        "}"
        "QLineEdit::focus{"
         "background:  rgb(255, 255, 255);"
           "color: rgb(0, 0, 0);"
          "border: 2px solid rgba(0, 0, 0, 102);"

        "}"

       "QCheckBox::indicator"
        "{"
        " width: 16px;"
         " height: 16px;"
          " border: 2px solid rgb(0, 0, 0);"
        "}"


       " QCheckBox::indicator:disabled"
       "{"
          "border: 2px solid rgb(172, 172, 172);"
        "}"


        "QCheckBox::indicator::pressed"
       " {"
          "  border: 2px solid rgb(102, 102, 102);"
         "   background: rgb(102, 102, 102);"
        "}"

        "QCheckBox::indicator:checked"
       "{"
        "image: url(:/style/images/checkbox_checked.svg);"
        "}"

        "QCheckBox::indicator:checked:!pressed"
        "{"
           " border: 2px solid rgb(0, 99, 177);"
          " background: rgb(0, 99, 177);"
         " image: url(:/style/images/checkbox_checked.svg);"
        "}"

        "QCheckBox::indicator:checked:!pressed:hover"
        "{"
         "   border: 2px solid rgb(0, 0, 0);"
        "}"


        "QCheckBox::indicator:indeterminate"
         "{"
            "image: url(:/style/images/checkbox_indeterminate.svg);"
          "  border: 2px solid rgb(0, 99, 177);"
        "}";


}

QString AllstyleSheet::getToolBtnActives()
{
    return
    "QPushButton {"

       " background-color: rgba(255, 255, 255, 0);"


        "image: url(:/icons/images/toolButtonSelect.png);"
    "}";
}

QString AllstyleSheet::getToolBtnNormal()
{
    return
    "QPushButton {"

       " background-color: rgba(255, 255, 255, 0);"


        "image: url(:/icons/images/toolButton.png);"
    "}"

    "QPushButton:hover {"

       "image: url(:/icons/images/toolButtonHover.png);"
    "}"

    "QPushButton:flat {"
      "  border: none; /* no border for a flat push button */"
    "}"

    "QPushButton:default {"
        "border-color: navy; /* make the default button prominent */"
    "}";
}

QString AllstyleSheet::normal_btns()
{
    return
   " QPushButton{"
    "border:none;"
    "background-color: rgb(220,220,220);"
    "}"
    "QPushButton:hover{"
    "border:none;"
    "background-color: rgb(210,210,210);"
    "}";
}

QString AllstyleSheet::active_btns()
{
    return
   " QPushButton{"
    "border:none;"
    "background-color: rgb(190,190,190);"
    "}"
    "QPushButton:hover{"
    "border:none;"
    "background-color: rgb(210,210,210);"
    "}";
}
QString AllstyleSheet::getRadioBtnNormal()
{
    return "QPushButton {"
                "background-color: rgb(255, 255, 255,0);"
                "image: url(:/icons/images/radio.png);"
                "border:none;"
            "}"
            "QPushButton:hover{"
                "image: url(:/icons/images/radioHover.png);"
                "background-color: rgb(255, 255, 255, 0);"
            "}";

}
/*************** LineEdit button *****************/
QString AllstyleSheet::getLineEditActive()
{
    return "QPushButton {"

                "background-color: rgba(255, 255, 255, 0);"
                "image: url(:/icons/images/lineEditSelect.png);"
            "}"
            ;

}
QString AllstyleSheet::getLineEditNormal()
{
    return "QPushButton {"
                "background-color: rgb(255, 255, 255,0);"
                "image: url(:/icons/images/lineEdit.png);"
                "border:none;"
            "}"
            "QPushButton:hover{"
                "image: url(:/icons/images/lineEditHover.png);"
                "background-color: rgb(255, 255, 255, 0);"
            "}";

}
/*************** ListWidget button*****************/
QString AllstyleSheet::getListWActive()
{
    return "QPushButton {"

                "background-color: rgba(255, 255, 255, 0);"
                "image: url(:/icons/images/listWidgetSelect.png);"
            "}"
            ;

}
QString AllstyleSheet::getListWNormal()
{
    return "QPushButton {"
                "background-color: rgb(255, 255, 255,0);"
                "image: url(:/icons/images/listWidget.png);"
                "border:none;"
            "}"
            "QPushButton:hover{"
                "image: url(:/icons/images/listWidgetHover.png);"
                "background-color: rgb(255, 255, 255, 0);"
            "}";

}
/*************** SpinBox button*****************/
QString AllstyleSheet::getSBOXActive()
{
    return "QPushButton {"

                "background-color: rgba(255, 255, 255, 0);"
                "image: url(:/icons/images/speenBoxSelect.png);"
            "}"
            ;

}
QString AllstyleSheet::getSBOXNormal()
{
    return "QPushButton {"
                "background-color: rgb(255, 255, 255,0);"
                "image: url(:/icons/images/spenBox.png);"
                "border:none;"
            "}"
            "QPushButton:hover{"
                "image: url(:/icons/images/speenBoxHover.png);"
                "background-color: rgb(255, 255, 255, 0);"
            "}";

}

/*************** TabWidget button*****************/
QString AllstyleSheet::getTabWActive()
{
    return "QPushButton {"

                "background-color: rgba(255, 255, 255, 0);"
                "image: url(:/icons/images/tabWidgetSelect.png);"
            "}"
            ;

}
QString AllstyleSheet::getTabWNormal()
{
    return "QPushButton {"
                "background-color: rgb(255, 255, 255,0);"
                "image: url(:/icons/images/tabWidget.png);"
                "border:none;"
            "}"
            "QPushButton:hover{"
                "image: url(:/icons/images/tabWidgetHover.png);"
                "background-color: rgb(255, 255, 255, 0);"
            "}";

}



