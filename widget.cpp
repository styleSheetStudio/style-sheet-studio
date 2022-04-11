#include "widget.h"
#include "ui_widget.h"
#include "QDebug"
#include "QLabel"
#include "ui_widget.h"
#include "QVBoxLayout"
#include "QSpacerItem"
#include <gradientpicker.h>
#include <gpick.h>
#include <panel.h>
#include <paneltext.h>
#include <QHBoxLayout>
#include <QImage>
#include <QRegExp>
#include <QToolTip>
#include <QClipboard>
#include <QFileInfo>
#include "highlighter.h"
#include "QFont"
#include "drawer.h"
#include "main_screen.h"

Widget::Widget(QString fileName, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    /************** Устанавливаем свойства окна ******************/
    this->setWindowIcon(QIcon(":/icons/images/logo.png"));
    this->setWindowTitle("QSS studio");
    this->layout()->setMargin(0);
QFileInfo info(fileName);
this->setWindowTitle("QSS - "+info.fileName()+"*");



fileNames= fileName;
    //this->setStyleSheet(AllstyleSheet::getMainWidgetStyle()); ломает stylesheet QSrollBar

    /************** Это вспомогательные элементы (пока оставим) ***********/

    // PanelText *pnk = new PanelText;
    // pnk->show();

    /************** Настраиваем StyleSheet TabView ***********/
    //в будущем


    /************** Настраиваем панель свойств (справа) ***********/
    rightbox = new QVBoxLayout;
    rightbox->setMargin(0);
    rightbox->setSpacing(0);
    rightbox->setAlignment(Qt::AlignTop);
    //rightbox->addSpacerItem(new QSpacerItem(1,1,QSizePolicy::Fixed,QSizePolicy::Expanding));
    ui->scrollArea->setStyleSheet(AllstyleSheet::scrollArea());
    ui->scrollAreaWidgetContents->setStyleSheet(AllstyleSheet::getScrollWidgetStyle());
    ui->scrollAreaWidgetContents->setLayout(rightbox);
   // ui->colNum->setAlignment(Qt::AlignTop);
    QTextCursor cursor = ui->colNum->textCursor();
    QTextBlockFormat textBlockFormat = cursor.blockFormat();
   textBlockFormat.setAlignment(Qt::AlignTop);
   cursor.mergeBlockFormat(textBlockFormat);
   ui->colNum->setTextCursor(cursor);
   ui->colNum->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

 ui->colNum->setVerticalScrollBar(ui->code_edit->verticalScrollBar());
  ui->code_edit->setText("background-color:");
  highlighter = new Highlighter(ui->code_edit->document());

 ui->copyWidgetSS->setToolTip("Скопировать текущий виджет для вставки в QtDesigner");
    /************** Настраиваем вкладки ***********/

    ui->tabWidget->setTabVisible(0, false);
    ui->tabWidget->setTabVisible(1, false);
    ui->tabWidget->setCurrentIndex(0);
 ui->colNum->setAlignment(Qt::AlignRight);
    /************** Настраиваем кнопки переключения вида ***********/
    ui->desigh->setStyleSheet(AllstyleSheet::SelectTabButton());
    ui->code_button->setStyleSheet(AllstyleSheet::NoSelectTabButton());
    ui->combo->setStyleSheet(AllstyleSheet::NoSelectTabButton());

    connect(ui->desigh,&QPushButton::clicked,this,&Widget::tabUpdateButtons);
    connect(ui->combo,&QPushButton::clicked,this,&Widget::tabUpdateButtons);
    connect(ui->code_button,&QPushButton::clicked,this,&Widget::tabUpdateButtons);
   ui->tab_2->layout()->setMargin(0);

    /************** Настраиваем кнопки инструментов (слева) ***********/
    ui->obj_panel->setStyleSheet(AllstyleSheet::panel_objects());
    connect(ui->pushbutton_b,&QPushButton::clicked,this,&Widget::changeActivTool);
    connect(ui->checkbox_b,&QPushButton::clicked,this,&Widget::changeActivTool);
    connect(ui->label_b,&QPushButton::clicked,this,&Widget::changeActivTool);
    connect(ui->combobox_b,&QPushButton::clicked,this,&Widget::changeActivTool);
    connect(ui->line_edit,&QPushButton::clicked,this,&Widget::changeActivTool);
    connect(ui->list_b,&QPushButton::clicked,this,&Widget::changeActivTool);
    connect(ui->radio_b,&QPushButton::clicked,this,&Widget::changeActivTool);
    connect(ui->speenbox_b,&QPushButton::clicked,this,&Widget::changeActivTool);
    connect(ui->tab_b,&QPushButton::clicked,this,&Widget::changeActivTool);
    connect(ui->textedit_b,&QPushButton::clicked,this,&Widget::changeActivTool);
    connect(ui->settingsbutton_b,&QPushButton::clicked,this,&Widget::changeActivTool);

    QFont codeFont(":/fonts/couriernew.ttf", 10);
    ui->code_edit->setFont(codeFont);


    clearActivStateTools();
    ui->tab->setLayout(box);
    box->setAlignment(Qt::AlignTop);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::openProject(QString filePath)
{
    if(!filePath.isEmpty())
    {
qDebug()<<"PROJECT Openning!";


   QString text;
   QStringList strT;
        QFileInfo info(filePath);

        //QString tittle = info.fileName();
        //ui->tabWidget->addTab(edit, tittle);
        //ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
        //ui->tabWidget->setTabToolTip(ui->tabWidget->count()-1, filename);
           fileProject = new QFile(filePath);
            QStringList normal;
            QStringList hover;
            QStringList pressed;
        QStringList filetext;
          if(fileProject->open(QIODevice::ReadOnly|QIODevice::Text)){
     // while(file.atEnd()){
        //     filetext.append(file.readLine());
     // }

              text=  fileProject->readAll();
              strT = text.split(QRegExp("[\n]"));
              QString current_ttool="";
              qDebug()<<"DATA! " << strT;
              bool btnN=false;
              bool btnH=false;
              bool btnP=false;
              bool btn=true;

              bool cboxN=false;
              bool cboxH=false;
              bool cboxP=false;
              bool cbox=true;

              bool labelN=false;
              bool labelH=false;
              //bool labelP=false;
              bool label=true;
              QStringList cboxBufferN;
              QStringList cboxBufferH;


              for(int i=0;i<strT.count(); i++){
                  if(strT.at(i)=="PUSH_BUTTON_TOOL begin"){

                      current_ttool="PUSH_BUTTON_TOOL";
                  }else if(strT.at(i)=="CHECK_BOX_TOOL::UNCHECKED begin" or strT.at(i)=="CHECK_BOX_TOOL::CHECKED begin"){
                      current_ttool="CHECK_BOX_TOOL";
                  }else if(strT.at(i)=="LABEL_TOOL begin"){
                      current_ttool="LABEL_TOOL";
                  }

                 if(current_ttool=="PUSH_BUTTON_TOOL" and btn==true){
                      if(strT.at(i)=="QPushButton{"){
                          // normal+=strT.at(i)+"\n";
                          btnN=true;
                      }else if(btnN==true){

                          if(strT.at(i)=="}"){
                              btnN=false;
                          }else{
                              normal+=strT.at(i).trimmed()+"\n";
                          }
                      }else if(strT.at(i)=="QPushButton::hover{"){
                          //  hover+=strT.at(i)+"\n";
                          btnH=true;
                      }else if(btnH==true){
                          if(strT.at(i)=="}"){

                              btnH=false;
                          }else{
                              hover+=strT.at(i).trimmed()+"\n";
                          }
                      }else if(strT.at(i)=="QPushButton::pressed{"){
                          btnP=true;
                          //pressed+=strT.at(i)+"\n";
                      }else if(btnP==true){

                          if(strT.at(i)=="}"){
                              btnP=false;
                          }else{
                              pressed+=strT.at(i).trimmed()+"\n";
                          }
                      }else if(strT.at(i)=="end"){
                          setPushButtonPanels();
                          currentTool=PUSH_BUTTON_TOOL;
                          currentToolchain="PUSH_BUTTON_TOOL";
                          qDebug()<<"btn NormalL: "<<normal;
                            qDebug()<<"btn Hover: "<<hover;
                              qDebug()<<"btn PressedL: "<<pressed;
                        setStyleFromFile(normal,hover,pressed, current_ttool);

                          //btnN=false;
                           //btnH=false;
                            //btnP=false;
                        btn=false;
                        //for (int i=0; i<normal.count(); i++) normal.removeAt(i);
                       //for (int i=0; i<hover.count(); i++) hover.removeAt(i);
                       //for (int i=0; i<pressed.count(); i++) pressed.removeAt(i);

                      }
                  }

                 if(current_ttool=="LABEL_TOOL" and label==true){
                      if(strT.at(i)=="QLabel{"){
                          // normal+=strT.at(i)+"\n";
                          labelN=true;
                      }else if(labelN==true){

                          if(strT.at(i)=="}"){
                              labelN=false;
                          }else{
                              normal+=strT.at(i)+"\n";
                          }
                      }else if(strT.at(i)=="QLabel::hover{"){
                          //  hover+=strT.at(i)+"\n";
                          labelH=true;
                      }else if(labelH==true){
                          if(strT.at(i)=="}"){

                              labelH=false;
                          }else{
                              hover+=strT.at(i)+"\n";
                          }
                      }else if(strT.at(i)=="end"){
                          setLabelPanels();
                          currentTool=LABEL_TOOL;
                          currentToolchain="LABEL_TOOL";
                          qDebug()<<"btn NormalL: "<<normal;
                            qDebug()<<"btn Hover: "<<hover;
                              qDebug()<<"btn PressedL: "<<pressed;
                        setStyleFromFile(normal,hover,pressed, current_ttool);

                          //btnN=false;
                           //btnH=false;
                            //btnP=false;
                        label=false;
                        //for (int i=0; i<normal.count(); i++) normal.removeAt(i);
                       //for (int i=0; i<hover.count(); i++) hover.removeAt(i);
                       //for (int i=0; i<pressed.count(); i++) pressed.removeAt(i);

                      }
                  }

                  if(current_ttool=="CHECK_BOX_TOOL" and cbox==true){
                      if(strT.at(i)=="CHECK_BOX_TOOL::UNCHECKED begin"){
                          // normal+=strT.at(i)+"\n";
                       //  cboxBufferN+=strT.at(i)+"\n";
                           cboxN=true;
                      }else if(cboxN==true){

                          if(strT.at(i)=="end::unchecked"){
                                 cboxN=false;

                          }else{
                                cboxBufferN+=strT.at(i).trimmed()+"\n";

                       }

                      }else if(strT.at(i)=="CHECK_BOX_TOOL::CHECKED begin"){
                          //  hover+=strT.at(i)+"\n";
                         // cboxBufferN+=strT.at(i)+"\n";
                          cboxH=true;
                      }else if(cboxH==true){

                          if(strT.at(i)=="end::checked"){

                            cboxH=false;
                          }else{
                                 cboxBufferH+=strT.at(i).trimmed()+"\n";
                          }

                      }else if(strT.at(i)=="end::tools"){
                          setCheckBoxPanels();
                          currentTool=CHECK_BOX_TOOL;
                          currentToolchain="CHECK_BOX_TOOL";
                          cbox=false;
                          qDebug()<<"CHECKBOX NormalL: "<<normal;
                            qDebug()<<"CHECKBOX Hover: "<<hover;
                            //  qDebug()<<"CHECKBOX PressedL: "<<pressed;
                    setStyleFromFile(cboxBufferN,cboxBufferH,hover, current_ttool);

                        //  cboxBufferN.clear();
                        //   cboxBufferH.clear();
                            //hover.clear();
                      }

                  }


              }

              qDebug()<<"FileText!!: "<<strT;

          }
  // file.readLine();





}
fileProject->close();
}

void Widget::setStyleFromFile(QStringList normal, QStringList hover, QStringList pressed, QString ttool)
{
    QString normaltool="";
    QString hovertool="";
    QString pressedtool="";


    for(int i = 0; i < box->count(); i++){
        DynamicWidgetTool *wdt = qobject_cast<DynamicWidgetTool*>(box->itemAt(i)->widget());




        for(int i=0; i<normal.count(); i++){
            normaltool+=normal.at(i);
        }
        for(int i=0; i<hover.count(); i++){
            hovertool+=hover.at(i);
        }
        for(int i=0; i<pressed.count(); i++){
            pressedtool+=pressed.at(i);
        }

QRegExp exp("[ ]+");
        if(wdt->getType()=="PUSH_BUTTON_TOOL" and ttool=="PUSH_BUTTON_TOOL"){

           // codeEdit(true,normal);
            for(int i=0;i<normal.count();i++){
                if(!exp.exactMatch(normal.at(i))){
                     wdt->SSBuffer_nor.insert(i,normal.at(i).trimmed()+"\n");
                }

            }
              //SSBuffer.clear();
              //  codeEdit(true,hover);
                for(int i=0;i<hover.count();i++){
                    if(!exp.exactMatch(hover.at(i))){
                         wdt->SSBuffer_hover.insert(i,hover.at(i).trimmed()+"\n");
                    }
                }
                //  SSBuffer.clear();
              //  codeEdit(true,pressed);
                for(int i=0;i<pressed.count();i++){
                    if(!exp.exactMatch(pressed.at(i))){
                         wdt->SSBuffer_pressed.insert(i,pressed.at(i).trimmed()+"\n");
                    }
                }
                 //SSBuffer.clear();

        wdt->btnNormal->setStyleSheet(normaltool);

        wdt->btnHover->setStyleSheet(hovertool);

        wdt->btnPressed->setStyleSheet(pressedtool);



        }else if(wdt->getType()=="CHECK_BOX_TOOL" and ttool=="CHECK_BOX_TOOL"){
      wdt->cboxNormal->setStyleSheet(normaltool);
      wdt->cboxHover->setStyleSheet(hovertool);
      for(int i=0;i<normal.count();i++){
          if(!exp.exactMatch(normal.at(i))){
               wdt->SSBuffer_nor.insert(i,normal.at(i).trimmed()+"\n");
          }

      }
      for(int i=0;i<hover.count();i++){
          if(!exp.exactMatch(hover.at(i))){
               wdt->SSBuffer_hover.insert(i,hover.at(i).trimmed()+"\n");
          }
      }

        }else if(wdt->getType()=="LABEL_TOOL" and ttool=="LABEL_TOOL"){
      wdt->labelNormal->setStyleSheet(normaltool);
      wdt->labelHover->setStyleSheet(hovertool);
      for(int i=0;i<normal.count();i++){
          if(!exp.exactMatch(normal.at(i))){
               wdt->SSBuffer_nor.insert(i,normal.at(i).trimmed()+"\n");
          }

      }
      for(int i=0;i<hover.count();i++){
          if(!exp.exactMatch(hover.at(i))){
               wdt->SSBuffer_hover.insert(i,hover.at(i).trimmed()+"\n");
          }
      }

    }
    }
}





void Widget::code()
{


}

void Widget::newProject(QString fileName)
{
    fileProject = new QFile(fileName);
}

void Widget::codeEdit(bool status,QStringList list)
{

    if(codeCycle==true){
        codeCycle=false;
        return;
    }else{
        QString tstr;
        if(status==true){//функция проверки из QStringList
           // strList.clear();
            for(int c=0;c<list.count();c++){
                strList.insert(c,list.at(c));
            }
        }else{//проверка из текстового редактора
            QString data = ui->code_edit->toPlainText();
            strList = data.split(QRegExp("[\n]"));
            qDebug()<<"codeEdit from list!";
        }

        QString tmpS;
        QStringList tmp;
        updateColNumbers(0, false, true);
//    if(currentTool == PUSH_BUTTON_TOOL){

        //   for(int i = 1; i < rightbox->count(); i++){
        /* Производим каст элемента слоя в объект динамической кнопки
             * */
        //  Panel *panel = qobject_cast<Panel*>(rightbox->itemAt(i)->widget());
        /* Если номер кнопки соответствует числу, которое установлено
             * в lineEdit, то производим удаление данной кнопки
          /   * */
        //   if(panel->getID() == 2){

        // qDebug()<<"IDPANEL2";


        //  }
        //}

        // col="";


        //for(int i=0;i<ui->code_edit->document()->blockCount();i++){
        // SStmp.at(i) = ui->code_edit->document()->
        //}


        //tstr = ui->code_edit->toPlainText();
        //      QRegExp colorRx("(color:)[ ]+(#)[0-9A-Fa-f]{6}(;)");
        //text-align: top;
        QRegExp panelTextRx("(font:)[ ]+[0-9]+[ ]+[0-9]+(pt)[ ]+(')[a-zA-Z]+(')(;)");
        QRegExp colorRx("(color:)[ ]+(#)[0-9A-Fa-f]{6}(;)");
        QRegExp alignRx("(text-align:)[ ]+[a-z]+(;)");
        QRegExp emptyRx("[ ]+");
        QRegExp BackgroundColorRx("(background-color:)[ ]+(#)[0-9A-Fa-f]{6}(;)");

        QRegExp BackgroundImageRx("(background-image:)[ ]+(url)[(][A-Za-z0-9/.А-Яа-я\-\_]+[)](;)");
        QRegExp BackgroundImageRepeatRx("(background-repeat:)[ ]+[a-z\-]+(;)");
        QRegExp BackgroundImagePosRx("(background-position:)[ ]+[a-z\-]+(;)");
        QRegExp BorderColorRx("(border-color:)[ ]+(#)[0-9A-Fa-f]{6}(;)");
        QRegExp BorderStyleRx("(border-style:)[ ]+[a-z]+(;)");
        QRegExp BorderPaddingRx("(padding:)[ ]+[0-9]+(px)(;)");
        QRegExp RoundRx("(border-radius:)[ ]+[0-9]+(px)(;)");
        QRegExp BorderWidthRx("(border-width:)[ ]+[0-9]+(px)(;)");
        //QRegExp end("[}]");
        QRegExp btnNormal("(QPushButton{)");
        QRegExp btnHover("(QPushButton::hover{)");
        QRegExp btnPressed("(QPushButton::pressed{)");


        QRegExp ImageRx("(image:)[ ]+(url)[(][A-Za-z0-9/.А-Яа-я\-\_]+[)](;)");
        QRegExp widthRx("(width:)[ ]+[0-9]+(;)");
        QRegExp heightRx("(height:)[ ]+[0-9]+(;)");

        bool falign= true;
        bool tfont=true;
        bool fcolor=true;
        //text-align:left
        //QRegExp checkLine("");
        //( )[0-9](pt)[a-zA-Z]

        //check line
        for(int i=0; i<strList.count();i++){
            //if(QString tmp = strList.split)
            tmpS=strList.at(i);
            tmp = tmpS.split(":");
            if(tmp.at(0)=="font"){

                if(panelTextRx.exactMatch(tmpS.trimmed())==true){
                    qDebug()<<"EXACT TRUE PANEL TEXT";
                    // strList.at(i);
                    codeError=false;
                    indexProperty=i;
                  //  TextFont = i;
                    //TextAlign++;


                    //TextColor +1;
                    qDebug()<<"strList: "<<strList;
                    if(codeError==false){
                        SSBuffer.removeAt(TextFont);
                        SSBuffer.insert(TextFont, tmpS.trimmed()+"\n");
                          tmpS+"\n";
                        for(int i = 1; i < rightbox->count(); i++){
                            /* Производим каст элемента слоя в объект динамической кнопки
                             * */
                            Panel *panel = qobject_cast<Panel*>(rightbox->itemAt(i)->widget());
                            if(panel->getStatus()==statusWidget){

                                //
                                QRegExp TextFontS("[0-9]+(pt)");
                                //QString str2;
                                int str2 = TextFontS.indexIn(tmpS);  //str);
                                int strEnd = TextFontS.lastIndexIn(tmpS);  //str);

                                //qDebug()<<str.at(str2);
                                //qDebug()<<str.at(strEnd);
                                //tmpS.count()-strEnd;

                                QString size="";
                                size += tmpS.at(str2);
                                size += tmpS.at(strEnd);
                                qDebug()<<size;
                                panel->pn->cycle=true;
                                panel->pn->TPixel->edit->setText(size);
                                panel->pn->cycle=false;
                            }
                        }





                            //updateAllData("NORMAL","PUSH_BUTTON_TOOL",cycle);
                        if(status==false){
                            SetCodeSS("PANEL_TEXT",currentToolchain, statusWidget);
                             updateColNumbers(i, true, true); //index, type, true green/false red
                        }



                }
}

            }else if(tmp.at(0)=="color"){
                if(colorRx.exactMatch(tmpS)){
                    indexProperty=i;
               //     TextColor = i;




                    codeError=false;

                    qDebug()<<"EXACT match color";
                    if(codeError==false){
                        SSBuffer.removeAt( TextColor);
                        SSBuffer.insert( TextColor, tmpS.trimmed()+="\n");
                        tmpS+"\n";
                          if(status==false){
                               updateColNumbers(i, true, true);
                           SetCodeSS("PANEL_TEXT",currentToolchain, statusWidget);
}

                    }
                }

            }else if(tmp.at(0)=="background-color"){
                if(BackgroundColorRx.exactMatch(tmpS)){
                    indexProperty=i;
                   // BackgroundColor = i;




                codeError=false;

                qDebug()<<"EXACT match ALIGN!!!";

                    SSBuffer.removeAt(BackgroundColor);
                    SSBuffer.insert(BackgroundColor, tmpS.trimmed()+="\n");
                    tmpS+"\n";
  if(status==false){
      updateColNumbers(i, true, true);
          SetCodeSS("PANEL_TEXT",currentToolchain, statusWidget);
}


                }
            }else if(tmp.at(0)=="background-image"){
                if(BackgroundImageRx.exactMatch(tmpS)){
                    indexProperty=i;
                   // BackgroundImage = i;




                codeError=false;

                qDebug()<<"EXACT match BackIMAGE!!!";

                    SSBuffer.removeAt(BackgroundImage);
                    SSBuffer.insert(BackgroundImage, tmpS.trimmed()+="\n");
            if(status==false){
            updateColNumbers(i, true, true);
                    SetCodeSS("PANEL_TEXT",currentToolchain, statusWidget);

            }



                }

            }else if(tmp.at(0)=="border-color"){
                if(BorderColorRx.exactMatch(tmpS))
                {
                    indexProperty=i;
                  //  MarginColor = i;




                codeError=false;
              //  updateColNumbers(i, true, true);
                qDebug()<<"EXACT match BackIMAGE!!!";
                if(codeError==false){
                    SSBuffer.removeAt( MarginColor);
                    SSBuffer.insert( MarginColor, tmpS.trimmed()+="\n");
                    if(status==false){
                      updateColNumbers(i, true, true);
                      SetCodeSS("PANEL_TEXT",currentToolchain, statusWidget);
                    }


                }
                }
            }else if(tmp.at(0)=="border-style"){
                if(BorderStyleRx.exactMatch(tmpS))
                {
                    indexProperty=i;
                  //  MarginStyle = i;




                codeError=false;
                updateColNumbers(i, true, true);
                qDebug()<<"EXACT match BackIMAGE!!!";
                if(codeError==false){
                    SSBuffer.removeAt(MarginStyle);
                    SSBuffer.insert(MarginStyle, tmpS.trimmed()+="\n");
                     if(status==false){
                   updateColNumbers(i, true, true);
                       SetCodeSS("PANEL_TEXT",currentToolchain, statusWidget);
                     }


                }
                }
            }else if(tmpS=="QPushButton{"){
                if(btnNormal.exactMatch(tmpS))
                {
                    //indexProperty=i;
                 //   MarginStyle = i;




                codeError=false;

                qDebug()<<"EXACT match BackIMAGE!!!";
                if(codeError==false){
                    SSBuffer.removeAt(i);
                    SSBuffer.insert(i, tmpS.trimmed()+="\n");
                      if(status==false){
                      SetCodeSS("PANEL_TEXT",currentToolchain, statusWidget);
                        updateColNumbers(i, true, true);
                      }


                }
                }
            }else if(tmpS=="QPushButton::hover{"){
                if(btnHover.exactMatch(tmpS))
                {
                    //indexProperty=i;
                 //   MarginStyle = i;




                codeError=false;

                qDebug()<<"EXACT match BackIMAGE!!!";
                if(codeError==false){
                    SSBuffer.removeAt(i);
                    SSBuffer.insert(i, tmpS.trimmed()+="\n");
if(status==false){
                   SetCodeSS("PANEL_TEXT",currentToolchain, statusWidget);
                   updateColNumbers(i, true, true);
}


                }
                }
            }else if(tmpS.trimmed()=="QCheckBox::indicator{"){
                   indexProperty=i;
                  //CheckBoxIndicator = i;




               codeError=false;

               qDebug()<<"EXACT match IMAGE!!!";
               if(codeError==false){

                   SSBuffer.removeAt(CheckBoxIndicator);
                   SSBuffer.insert(CheckBoxIndicator, tmpS.trimmed()+="\n");
                 if(status==false){
                     for(int c=i; c<strList.count(); c++){
                         if(strList.at(i).trimmed()=="}"){
                          //   CloseCheckBoxIndicator=c;
                           //  codeError=false;
                             updateColNumbers(c, true, true);
                           //  SSBuffer.removeAt(CloseCheckBoxIndicator);
                          //   SSBuffer.insert(CloseCheckBoxIndicator, tmpS.trimmed()+="\n");
                         }
                  }
                       updateColNumbers(i, true, true);
                      SetCodeSS("PANEL_TEXT",currentToolchain, statusWidget);
}

               }
            }else if(tmpS.trimmed()=="QCheckBox{"){
                   indexProperty=i;
                //  CheckBox = i;

               qDebug()<<"EXACT match IMAGE!!!";
               if(codeError==false){
                   SSBuffer.removeAt(CheckBox);
                   SSBuffer.insert(CheckBox, tmpS.trimmed()+="\n");
                   if(status==false){
                 for(int f=i; f<strList.count(); f++){
                     if(strList.at(i).trimmed()=="}"){
                      //   CloseCheckBox=f;
                         codeError=false;
                         updateColNumbers(f, true, true);
                       //  SSBuffer.removeAt(CloseCheckBox);
                       //  SSBuffer.insert(CloseCheckBox, tmpS.trimmed()+="\n");
                     }
              }


 SetCodeSS("PANEL_TEXT",currentToolchain, statusWidget);
              codeError=false;
              updateColNumbers(i, true, true);
                   }



               }

            }else if(tmp.at(0)=="padding"){
                if(BorderPaddingRx.exactMatch(tmpS))
                {
                    indexProperty=i;
                   // MarginPadding = i;




                codeError=false;
                updateColNumbers(i, true, true);
                qDebug()<<"EXACT match BackIMAGE!!!";
                if(codeError==false){
                    SSBuffer.removeAt(MarginPadding );
                    SSBuffer.insert(MarginPadding , tmpS.trimmed()+="\n");
tmpS+"\n";
                    SetCodeSS("PANEL_TEXT",currentToolchain, statusWidget);


                }
                }
            }else if(tmp.at(0)=="border-radius"){
                if(RoundRx.exactMatch(tmpS))
                {
                    indexProperty=i;
                    //Round = i;




                codeError=false;

                qDebug()<<"EXACT match BackIMAGE!!!";
                SSBuffer.removeAt(Round );
                SSBuffer.insert(Round , tmpS.trimmed()+="\n");
                       if(status==false){

   updateColNumbers(i, true, true);
                     SetCodeSS("PANEL_TEXT",currentToolchain, statusWidget);


                }
                }
            }else if(tmp.at(0)=="background-repeat"){
                if( BackgroundImageRepeatRx.exactMatch(tmpS)){
                    indexProperty=i;
                  // BackgroundRepeate = i;




                codeError=false;

                qDebug()<<"EXACT match BackIMAGE!!!";
                SSBuffer.removeAt(BackgroundRepeate);
                SSBuffer.insert(BackgroundRepeate, tmpS.trimmed()+="\n");
                 if(status==false){
                    updateColNumbers(i, true, true);
SetCodeSS("PANEL_TEXT",currentToolchain, statusWidget);


                }
                }
            }else if(tmp.at(0)=="background-position"){
                if( BackgroundImagePosRx.exactMatch(tmpS)){
                    indexProperty=i;
                    //TextAlign = i;




                codeError=false;

                qDebug()<<"EXACT match BackIMAGE!!!";
                SSBuffer.removeAt(BackgroundPosition);

                SSBuffer.insert(BackgroundPosition, tmpS.trimmed()+"\n");
                if(status==false){
               SetCodeSS("PANEL_TEXT",currentToolchain, statusWidget);
                updateColNumbers(i, true, true);

                }
                }
            }else if(tmp.at(0)=="border-width"){
                if( BorderWidthRx.exactMatch(tmpS)){
                    indexProperty=i;
                   // MarginWidth = i;




                codeError=false;

                qDebug()<<"EXACT match BackIMAGE!!!";
                SSBuffer.removeAt(MarginWidth);

                SSBuffer.insert(MarginWidth, tmpS.trimmed()+"\n");
                if(status==false){
                     updateColNumbers(i, true, true);
                      SetCodeSS("PANEL_TEXT",currentToolchain, statusWidget);


                }
                }
            }else if(tmp.at(0)=="text-align"){
                if(alignRx.exactMatch(tmpS)){
                    indexProperty=i;
                  //  TextAlign = i;







                codeError=false;

                qDebug()<<"EXACT match ALIGN!!!";
                SSBuffer.removeAt( TextAlign);

                SSBuffer.insert( TextAlign, tmpS.trimmed()+"\n");
              if(status==false){
              updateColNumbers(i, true, true);

                     SetCodeSS("PANEL_TEXT",currentToolchain, statusWidget);


                }
}
            }else if(tmp.at(0)=="image"){
                if(ImageRx.exactMatch(tmpS)){
                    indexProperty=i;
                   // Image = i;




                codeError=false;
                SSBuffer.removeAt(Image);
                SSBuffer.insert(Image, tmpS.trimmed()+="\n");
                qDebug()<<"EXACT match IMAGE!!!";
                if(status==false){

 updateColNumbers(i, true, true);
                       SetCodeSS("PANEL_TEXT",currentToolchain, statusWidget);


                }
                }
            }else if(tmp.at(0)=="width"){
                if(widthRx.exactMatch(tmpS)){
                    indexProperty=i;
                   // PWidth = i;




                codeError=false;

                qDebug()<<"EXACT match IMAGE!!!";
                SSBuffer.removeAt(PWidth );
                SSBuffer.insert(PWidth , tmpS.trimmed()+="\n");
                 if(status==false){

    updateColNumbers(i, true, true);
                       SetCodeSS("PANEL_TEXT",currentToolchain, statusWidget);


                }
                }
            }else if(tmp.at(0)=="height"){
                if(heightRx.exactMatch(tmpS)){
                    indexProperty=i;
                //    PHeight = i;




                codeError=false;

                qDebug()<<"EXACT match IMAGE!!!";
                SSBuffer.removeAt(PHeight);
                SSBuffer.insert(PHeight, tmpS.trimmed()+="\n");
                if(status==false){

                updateColNumbers(i, true, true);
                       SetCodeSS("PANEL_TEXT",currentToolchain, statusWidget);


                }
                }

             }else if(tmpS=="QCheckBox::indicator:checked{"){
                    indexProperty=i;
                  // CheckBoxChecked = i;




                codeError=false;

                qDebug()<<"EXACT match IMAGE!!!";
                SSBuffer.removeAt(CheckBoxChecked);
                SSBuffer.insert(CheckBoxChecked, tmpS.trimmed()+="\n");
                 if(status==false){
                     for(int c=i; c<strList.count(); c++){
                         if(strList.at(i)=="}"){
                         //    CloseCheckBoxChecked=c;
                             codeError=false;
                             updateColNumbers(c, true, true);
                            // SSBuffer.removeAt(CloseCheckBoxChecked);
                            // SSBuffer.insert(CloseCheckBoxChecked, tmpS.trimmed()+="\n");
                         }
                  }

updateColNumbers(i, true, true);
                       SetCodeSS("PANEL_TEXT",currentToolchain, statusWidget);


                }

            }else if(emptyRx.exactMatch(tmpS)){
             //   SSBuffer.removeAt(i);
               // SSBuffer.insert(i,tmpS);
                codeError=false;
                // SetCodeSS("PANEL_TEXT","PUSH_BUTTON_TOOL", "NORMAL");
                // ui->code_edit->setText(SSBuffer.at(i));   //SSBuffer.at(i);
                updateColNumbers(i, true, true);
                //   qDebug()<<"EMPTY";
            }else if(tmpS.isEmpty()){
                //SSBuffer.removeAt(i);
               // SSBuffer.insert(i,"\n");
                codeError=false;
                //SetCodeSS("PANEL_TEXT","PUSH_BUTTON_TOOL", "NORMAL");
                //ui->code_edit->setText(SSBuffer.at(i));   //SSBuffer.at(i);
                updateColNumbers(i, true, true);
                qDebug()<<"EMPTY";
                //  }else if(!emptyRx.exactMatch(tmpS)){
                //          //   SSBuffer.removeAt(i);
                // SSBuffer.insert(i,tmpS);
                //     updateColNumbers(i, true, false);
                //     codeError = true;
            }




    // qDebug()<<ui->code_edit->document()->blockCount();
    }
    qDebug()<<"Buffer: "<<SSBuffer;
}

}



void Widget::addPanel(QString status)
{
    if(currentToolchain=="PUSH_BUTTON_TOOL"){
        rightbox->addWidget( new Panel("ГЕОМЕТРИЯ", "PANEL_GEOMETRYS",status,currentToolchain)); //0

        rightbox->addWidget( new Panel("ТЕКСТ", "PANEL_TEXT", status,currentToolchain)); //1

        rightbox->addWidget( new Panel("ГРАНИЦЫ", "PANEL_MARGINS",status,currentToolchain)); //2

        rightbox->addWidget( new Panel("ФОН", "PANEL_BACKGROUND", status,currentToolchain)); //3

        rightbox->addWidget(   new Panel("ИКОНКА", "PANEL_ICON", status,currentToolchain)); //4

        rightbox->addWidget(    new Panel("СКРУГЛЕНИЕ", "PANEL_ROUND", status,currentToolchain)); //5

          rightbox->addWidget(    new Panel("СТИЛИ", "PANEL_STYLE", status,currentToolchain)); //6


    }else if(currentToolchain=="CHECK_BOX_TOOL"){
        rightbox->addWidget( new Panel("ГЕОМЕТРИЯ", "PANEL_GEOMETRYS",status,currentToolchain)); //0

        rightbox->addWidget( new Panel("ТЕКСТ", "PANEL_TEXT", status,currentToolchain)); //1

        //rightbox->addWidget( new Panel("ГРАНИЦЫ", "PANEL_MARGINS",status,currentToolchain)); //2

      rightbox->addWidget( new Panel("ФОН", "PANEL_BACKGROUND", status,currentToolchain)); //3

        rightbox->addWidget(   new Panel("ИНДИКАТОР", "PANEL_ICON", status,currentToolchain)); //4

       rightbox->addWidget(    new Panel("СКРУГЛЕНИЕ", "PANEL_ROUND", status,currentToolchain)); //5


        for(int i=0; i<rightbox->count(); i++){
            Panel * panel = qobject_cast<Panel*>(rightbox->itemAt(i)->widget());
              if(panel->getTypePanel()=="PANEL_ICON"){
                  if(panel->GetStatus()==status){
                           panel->contentIcon->setupCheckBox();
         }
              }

}
}else if(currentToolchain=="LABEL_TOOL"){
        rightbox->addWidget( new Panel("ГЕОМЕТРИЯ", "PANEL_GEOMETRYS",status,currentToolchain)); //0

        rightbox->addWidget( new Panel("ТЕКСТ", "PANEL_TEXT", status,currentToolchain)); //1

        rightbox->addWidget( new Panel("ГРАНИЦЫ", "PANEL_MARGINS",status,currentToolchain)); //2

      rightbox->addWidget( new Panel("ФОН", "PANEL_BACKGROUND", status,currentToolchain)); //3

        rightbox->addWidget(   new Panel("ИКОНКА", "PANEL_ICON", status,currentToolchain)); //4

       rightbox->addWidget(    new Panel("СКРУГЛЕНИЕ", "PANEL_ROUND", status,currentToolchain)); //5











        }
    for(int i=0; i<rightbox->count(); i++){
        Panel * panel = qobject_cast<Panel*>(rightbox->itemAt(i)->widget());
        connect (panel, &Panel::changeData, this,&Widget::onDataChanged);
    }
    }


void Widget::updateAllData(QString status, QString toolType, bool cycle)
{
    if(cycle==true){
//if(toolType=="PUSH_BUTTON_TOOL"){
    //for(int c=1; c<i;c++){
        for(int i = 0; i < rightbox->count(); i++){
            /* Производим каст элемента слоя объект panel нужный находим
         * */
            Panel *panel = qobject_cast<Panel*>(rightbox->itemAt(i)->widget());
            if(panel->getStatus()==status){
                       if(panel->getTool()==toolType){
               //  SSBuffer="";


                onDataChanged(panel->getTypePanel(),panel->getTool(),panel->GetStatus(),i,false);


            }
            }
        }
    //}


//}
    }else if(cycle==false){
      return;
    }
}



void Widget::tabUpdateButtons()
{
    QPushButton *btn = qobject_cast <QPushButton*>(sender());
    ui->desigh->setStyleSheet(AllstyleSheet::NoSelectTabButton());
    ui->code_button->setStyleSheet(AllstyleSheet::NoSelectTabButton());
    ui->combo->setStyleSheet(AllstyleSheet::NoSelectTabButton());
    if(btn->objectName()=="desigh"){
        ui->desigh->setStyleSheet(AllstyleSheet::SelectTabButton());
        ui->tabWidget->setCurrentIndex(0);
    }else if(btn->objectName()=="code_button"){
        ui->code_button->setStyleSheet(AllstyleSheet::SelectTabButton());
        ui->tabWidget->setCurrentIndex(1);
    }else{
        ui->combo->setStyleSheet(AllstyleSheet::SelectTabButton());
        //  ui->tabWidget->setCurrentIndex(2);
    }
}



void Widget::setAplicationMenu()
{

}


/* Меняем содержимое интерфейса в зависимости от
 * выбранного инструмента. Функция вызывается, когда пользователь
 * кликает по кнопке инструментов слева.
 * С помощью имени объекта понимаем, какая именно из кнопок была нажата,
 * поскольку все они связаны с одним слотом.
 */
void Widget::changeActivTool()
{
    clearActivStateTools(); //фцнкция очистки панели не удаляя spacer если 1 < n-widgets
    /* sender'ом приравниваем к типу qpushbutton и сверяем имя обтекта через if */
    QPushButton *btn = qobject_cast <QPushButton*>(sender());

    if(btn->objectName()=="pushbutton_b"){
        currentTool = PUSH_BUTTON_TOOL;
        ui->pushbutton_b->setStyleSheet(AllstyleSheet::getPushBottonToolActive());

    }else if(btn->objectName()=="checkbox_b"){
        currentTool = CHECK_BOX_TOOL;
        ui->checkbox_b->setStyleSheet(AllstyleSheet::getCheckBoxToolActive());
    } else if(btn->objectName()=="label_b"){
        currentTool = LABEL_TOOL;
        ui->label_b->setStyleSheet(AllstyleSheet::getLabelActive());
    } else if(btn->objectName()=="line_edit"){
        currentTool = LINE_EDIT_TOOL;
        ui->line_edit->setStyleSheet(AllstyleSheet::getLineEditActive());
    }else if(btn->objectName()=="textedit_b"){
        currentTool = TEXT_EDIT_TOOL;
        ui->textedit_b->setStyleSheet(AllstyleSheet::getTextEditActive());
    }else if(btn->objectName()=="combobox_b"){
        currentTool = COMBO_BOX_TOOL;
        ui->combobox_b->setStyleSheet(AllstyleSheet::getCBOXActive());
    } else if(btn->objectName()=="radio_b"){
        currentTool = RADIO_BUTTON_TOOL;
        ui->radio_b->setStyleSheet(AllstyleSheet::getRadioBtnActive());
    } else if(btn->objectName()=="speenbox_b"){
        currentTool = SPIN_BOX_TOOL;
        //    setPanelGroup(); //фунция установки текущей группы панели справа currentTool = SPIN_BOX_TOOL;
        ui->speenbox_b->setStyleSheet(AllstyleSheet::getSBOXActive());
    }else if(btn->objectName()=="tab_b"){
        currentTool = TAB_WIDGET_TOOL;
        ui->tab_b->setStyleSheet(AllstyleSheet::getTabWActive());
    }else if(btn->objectName()=="list_b"){
        currentTool = LIST_WIDGET_TOOL;
        ui->list_b->setStyleSheet(AllstyleSheet::getListWActive());
    }else if(btn->objectName()=="settingsbutton_b"){
        currentTool = SETTINGS_BUTTON_TOOL;
        ui->settingsbutton_b->setStyleSheet(AllstyleSheet::getToolBtnActives());

    }
    setPanelGroup(); //фунция установки текущей группы панели справаw
}




/* Устанавливаем содержимое для правой панели.
 * Содержимое будет разным для разных инструментов.
 */
void Widget::setPanelGroup()
{
    switch (currentTool) {
    case PUSH_BUTTON_TOOL:
        setPushButtonPanels();

        break;
    case CHECK_BOX_TOOL:
        setCheckBoxPanels();
        break;
    case LABEL_TOOL:
        setLabelPanels();
        break;
    case COMBO_BOX_TOOL:
        setCBOXPanels();
        break;
    case LINE_EDIT_TOOL:
        setLeditPanels();
        break;
    case LIST_WIDGET_TOOL:
        setListWPanels();
        break;
    case RADIO_BUTTON_TOOL:
        setRadioBtnPanels();
        break;
    case SPIN_BOX_TOOL:
        setSBOXPanels();
        break;
    case TAB_WIDGET_TOOL:
        setTabWPanels();
        break;
    case TEXT_EDIT_TOOL:
        setTeditPanels();
        break;
    case SETTINGS_BUTTON_TOOL:
        setTBTNPanels();
        break;
    }
}

void Widget::clearActivStateTools() //сбрасывает кнопки в normal slate
{
    ui->pushbutton_b->setStyleSheet(AllstyleSheet::getPushBottonToolNormal());
    ui->checkbox_b->setStyleSheet(AllstyleSheet::getCheckBoxToolNormal());
    ui->label_b->setStyleSheet(AllstyleSheet::getLabelNormal());
    ui->combobox_b->setStyleSheet(AllstyleSheet::getCBOXNormal());
    ui->line_edit->setStyleSheet(AllstyleSheet::getLineEditNormal());
    ui->list_b->setStyleSheet(AllstyleSheet::getListWNormal());
    ui->radio_b->setStyleSheet(AllstyleSheet::getRadioBtnNormal());
    ui->speenbox_b->setStyleSheet(AllstyleSheet::getSBOXNormal());
    ui->tab_b->setStyleSheet(AllstyleSheet::getTabWNormal());
    ui->textedit_b->setStyleSheet(AllstyleSheet::getTextEditNormal());
    ui->settingsbutton_b->setStyleSheet(AllstyleSheet::getToolBtnNormal());
}

void Widget::removeAllPanels() //удаление виджитов и items c панели
{
  for(int i=0; i<rightbox->count(); i++) {
        //int itemIndex = rightbox->count();
       // qDebug() << "Элементов в layout = "<<rightbox->count();
       // qDebug() << "Удаляем элемент с индексом " <<itemIndex;
      Panel * panel = qobject_cast<Panel*>(rightbox->itemAt(i)->widget());
  //panel->setVisible(false);
 //      delete panel;
  //if(i==panel->getID()){
     panel->setVisible(false);
 //}

}
}

void Widget::setPushButtonPanels()
{
    currentToolchain="PUSH_BUTTON_TOOL";
  if(setPushButton==true){
  qDebug()<<"PBTN select tool-panel";
  removeAllPanels();
  DynamicWidgetTool *dwt = new DynamicWidgetTool("PUSH_BUTTON_TOOL",0,"NORMAL");
  box->addWidget(dwt);
 // dwt->setProperty("flag");
  //dwt->btnNormal->setStyleSheet("font: 300 57pt 'Ubuntu Light';");
  wdt_ID = dwt->getID();


connect(dwt,&DynamicWidgetTool::newPanel, this,&Widget::newPanel);
setPushButton=false;
}else{
      removeAllPanels();
      for(int i = 0; i < box->count(); i++){

         DynamicWidgetTool *dwt = qobject_cast<DynamicWidgetTool*>(box->itemAt(i)->widget());
          if(dwt->getType()=="PUSH_BUTTON_TOOL"){
              wdt_ID = dwt->getID();
               connect(dwt,&DynamicWidgetTool::newPanel, this,&Widget::newPanel);
          }
      }

  }

}

void Widget::setCheckBoxPanels()
{
      currentToolchain="CHECK_BOX_TOOL";
    if(setCBox==true){
    qDebug()<<"QCheckBOx select tool-panel";
    removeAllPanels();
    DynamicWidgetTool *dwt = new DynamicWidgetTool("CHECK_BOX_TOOL",1,"NORMAL");
    box->addWidget(dwt);
   // dwt->setProperty("flag");
    //dwt->btnNormal->setStyleSheet("font: 300 57pt 'Ubuntu Light';");
    wdt_ID = dwt->getID();


 connect(dwt,&DynamicWidgetTool::newPanel, this,&Widget::newPanel);
    //   qDebug()<<"CHeckBox select tool-panel";
    //  removeAllPanels();
    //  int index = 0;
    //  rightbox->insertWidget(index, new Panel("ГЕОМЕТРИЯ", PANEL_GEOMETRY));
    // index ++;
    // rightbox->insertWidget(index, new Panel("ТЕКСТ", PANEL_TEXT));
    //  index ++;
    // rightbox->insertWidget(index, new Panel("ГРАНИЦЫ", PANEL_MAGRINGS));
    //  index ++;
    // rightbox->insertWidget(index, new Panel("ФОН", PANEL_BACKGROUND));
 setCBox=false;
}else{
        removeAllPanels();
        for(int i = 0; i < box->count(); i++){

            DynamicWidgetTool *wdt = qobject_cast<DynamicWidgetTool*>(box->itemAt(i)->widget());
            if(wdt->getType()=="CHECK_BOX_TOOL"){
                wdt_ID = wdt->getID();
                 connect(wdt,&DynamicWidgetTool::newPanel, this,&Widget::newPanel);
            }
        }

    }

}

void Widget::setLabelPanels()
{
    currentToolchain="LABEL_TOOL";
  if(setLabel==true){
  qDebug()<<"QLabel select tool-panel";
  removeAllPanels();
  DynamicWidgetTool *dwt = new DynamicWidgetTool("LABEL_TOOL",2,"NORMAL");
  box->addWidget(dwt);
 // dwt->setProperty("flag");
  //dwt->btnNormal->setStyleSheet("font: 300 57pt 'Ubuntu Light';");
  wdt_ID = dwt->getID();


connect(dwt,&DynamicWidgetTool::newPanel, this,&Widget::newPanel);
  //   qDebug()<<"CHeckBox select tool-panel";
  //  removeAllPanels();
  //  int index = 0;
  //  rightbox->insertWidget(index, new Panel("ГЕОМЕТРИЯ", PANEL_GEOMETRY));
  // index ++;
  // rightbox->insertWidget(index, new Panel("ТЕКСТ", PANEL_TEXT));
  //  index ++;
  // rightbox->insertWidget(index, new Panel("ГРАНИЦЫ", PANEL_MAGRINGS));
  //  index ++;
  // rightbox->insertWidget(index, new Panel("ФОН", PANEL_BACKGROUND));
setLabel=false;
}else{
      removeAllPanels();
      for(int i = 0; i < box->count(); i++){

          DynamicWidgetTool *wdt = qobject_cast<DynamicWidgetTool*>(box->itemAt(i)->widget());
          if(wdt->getType()=="LABEL_TOOL"){
              wdt_ID = wdt->getID();
               connect(wdt,&DynamicWidgetTool::newPanel, this,&Widget::newPanel);
          }
      }

  }
}

void Widget::setCBOXPanels()

{
    //  qDebug()<<"QComboBox select tool-panel";
    // removeAllPanels();
    //  int index = 0;
    // rightbox->insertWidget(index, new Panel("ГЕОМЕТРИЯ", PANEL_GEOMETRY));
    // index ++;
    // rightbox->insertWidget(index, new Panel("ТЕКСТ", PANEL_TEXT));
    //  index ++;
    // rightbox->insertWidget(index, new Panel("ГРАНИЦЫ", PANEL_MAGRINGS));
}

void Widget::setLeditPanels()
{
    //   qDebug()<<"QLineEdit select tool-panel";
    // removeAllPanels();
    //  int index = 0;
    //  rightbox->insertWidget(index, new Panel("ГЕОМЕТРИЯ", PANEL_GEOMETRY));
    //  index ++;
    // rightbox->insertWidget(index, new Panel("ТЕКСТ", PANEL_TEXT));
    // index ++;
    //  rightbox->insertWidget(index, new Panel("ГРАНИЦЫ", PANEL_MAGRINGS));
    //  index ++;
    //  rightbox->insertWidget(index, new Panel("ФОН", PANEL_BACKGROUND));

}

void Widget::setListWPanels()
{
    //   qDebug()<<"ListView select tool-panel";
    //  removeAllPanels();
    //  int index = 0;
    // rightbox->insertWidget(index, new Panel("ГЕОМЕТРИЯ", PANEL_GEOMETRY));
    //  index ++;
    //  rightbox->insertWidget(index, new Panel("ТЕКСТ", PANEL_TEXT));
    //  index ++;
    //  rightbox->insertWidget(index, new Panel("ГРАНИЦЫ", PANEL_MAGRINGS));
    //  index ++;
    //   rightbox->insertWidget(index, new Panel("ФОН", PANEL_BACKGROUND));

}

void Widget::setRadioBtnPanels()
{
    //   qDebug()<<"QRadioButton select tool-panel";
    //  removeAllPanels();
    //  int index = 0;
    //  rightbox->insertWidget(index, new Panel("ГЕОМЕТРИЯ", PANEL_GEOMETRY));
    //  index ++;
    //  rightbox->insertWidget(index, new Panel("ТЕКСТ", PANEL_TEXT));
    //    index ++;
    // rightbox->insertWidget(index, new Panel("ГРАНИЦЫ", PANEL_MAGRINGS));
    //  index ++;
    // / rightbox->insertWidget(index, new Panel("ФОН", PANEL_BACKGROUND));
    // index ++;
    //  rightbox->insertWidget(index, new Panel("ИКОНКА", PANEL_ICON));

}

void Widget::setSBOXPanels()
{
    //  qDebug()<<"QSpinBox select tool-panel";
    // removeAllPanels();
    //  int index = 0;
    //rightbox->insertWidget(index, new Panel("ГЕОМЕТРИЯ", PANEL_GEOMETRY));
    //index ++;
    // rightbox->insertWidget(index, new Panel("ТЕКСТ", PANEL_TEXT));
    //  index ++;
    // rightbox->insertWidget(index, new Panel("ГРАНИЦЫ", PANEL_MAGRINGS));
    // index ++;
    //  rightbox->insertWidget(index, new Panel("ФОН", PANEL_BACKGROUND));


}

void Widget::setTabWPanels()
{
    //    qDebug()<<"QPTabView widget select tool-panel";
    // removeAllPanels();
    //  int index = 0;
    //  rightbox->insertWidget(index, new Panel("ГЕОМЕТРИЯ", PANEL_GEOMETRY));
    //  index ++;
    //  rightbox->insertWidget(index, new Panel("ТЕКСТ", PANEL_TEXT));
    //  index ++;
    // rightbox->insertWidget(index, new Panel("ГРАНИЦЫ", PANEL_MAGRINGS));
    // index ++;
    //  rightbox->insertWidget(index, new Panel("ФОН", PANEL_BACKGROUND));

}

void Widget::setTeditPanels()
{
    //   qDebug()<<"QTextEdit select tool-panel";
    //  removeAllPanels();
    //  int index = 0;
    //  rightbox->insertWidget(index, new Panel("ГЕОМЕТРИЯ", PANEL_GEOMETRY));
    //  index ++;
    //  rightbox->insertWidget(index, new Panel("ТЕКСТ", PANEL_TEXT));
    // index ++;
    // rightbox->insertWidget(index, new Panel("ГРАНИЦЫ", PANEL_MAGRINGS));
    //index ++;
    //rightbox->insertWidget(index, new Panel("ФОН", PANEL_BACKGROUND));

}

void Widget::setTBTNPanels()
{
    //   qDebug()<<"ToolButton select tool-panel";
    //  removeAllPanels();
    //int index = 0;
    // rightbox->insertWidget(index, new Panel("ГЕОМЕТРИЯ", "PANEL_GEOMETRY"));
    // index ++;
    //  rightbox->insertWidget(index, new Panel("ТЕКСТ", "PANEL_TEXT"));
    // index ++;
    //rightbox->insertWidget(index, new Panel("ГРАНИЦЫ", "PANEL_MAGRINGS"));
    // index ++;
    //rightbox->insertWidget(index, new Panel("ФОН", PANEL_BACKGROUND));
    //index ++;
    // rightbox->insertWidget(index, new Panel("ИКОНКА", PANEL_ICON));
    // index ++;
    //rightbox->insertWidget(index, new Panel("СКРУГЛЕНИЕ", PANEL_ROUND));
}

void Widget::insertTOList(int i)
{
 for(int c=0; c<i;c++){
     SSBuffer.insert(c," ");
 }
}

void Widget::updateColNumbers(int index, bool type, bool color)
{
    col="";

    if(type==false){
        for(int i=0; i<indicators.count();i++){
            indicators.removeAt(i);
        }
        for(int i=0; i<ui->code_edit->document()->blockCount();i++){
              indicators.removeAt(i);
              indicators.insert(i,QString::number(i)+"<font color='red'>|</font>"+"\n");
              //   QLabel *indicator = new QLabel;



           }
        for(int i=0; i<indicators.count();i++){
            col+=indicators.at(i);

        }

    }else if(type==true){
        indicators.removeAt(index);
        if(color==true){
          indicators.insert(index,QString::number(index)+"<font color='green'>|</font>"+"\n");
        }else{
             indicators.insert(index,QString::number(index)+"<font color='red'>|</font>"+"\n");
        }

        for(int i=0; i<indicators.count();i++){
            col+=indicators.at(i);

        }
    }
      ui->colNum->setHtml(col);
     // ui->colNum->moveCursor(QTextCursor::End);
}

void Widget::tool_button()
{
    if(tool_button_slate==true){

    }
}

void Widget::SetSSDWT(QString panelType, QString toolType, QString status, int IDpanel, bool cycle)
{
    QString tmpN = "";
    QString tmpPress="";
    QString tmpHover="";
   // if(toolType=="PUSH_BUTTON_TOOL"){

            for(int i = 0; i < box->count(); i++){
                DynamicWidgetTool *wdt = qobject_cast<DynamicWidgetTool*>(box->itemAt(i)->widget());
                if(wdt->getID()==wdt_ID){

                    if(status=="NORMAL"){

                        int count;
                        count = SSBuffer.count();
                    tmpN="";
                  //  SSBuffer.removeAt(0);
                  //  SSBuffer.insert(0,"QPushButton{\n");
                    for(int i=0;i<count;i++){
                          wdt->SSBuffer_nor.removeAt(i);
                          wdt->SSBuffer_nor.insert(i, SSBuffer.at(i));
                    }

                  // if(!strList.isEmpty()){
                    //for(int i=0; i<strList.count(); i++){
                    //SSBuffer.insert(i, strList.at(i));



//tmp = ui->code_edit->toPlainText();
//font: 20 20pt 'ubuntu' ;
                    QRegExp exp("[ ]+");
                    for(int i=0; i<wdt->SSBuffer_nor.count(); i++){
                        if(!exp.exactMatch(wdt->SSBuffer_nor.at(i))){
                             tmpN+= wdt->SSBuffer_nor.at(i).trimmed()+"\n";
                        }

                    }
                   // tmp=tmp+"}";

                    ui->code_edit->clear();
                 ui->code_edit->setText(tmpN.trimmed());
                 if(toolType=="PUSH_BUTTON_TOOL"){
                wdt->btnNormal->setStyleSheet(tmpN);
                if(check==false){
                    wdt->btnNormal->setText("");
                }else if(check==true){
                     wdt->btnNormal->setText("Test");
                }
                 }else if(toolType=="CHECK_BOX_TOOL"){
                   //  QString m = "QCheckBox::indicator{\n";
                     //m+=tmpN +="}";
                   wdt->cboxNormal->setStyleSheet(tmpN);

                 }else if(toolType=="LABEL_TOOL"){
                   //  QString m = "QCheckBox::indicator{\n";
                     //m+=tmpN +="}";
                   wdt->labelNormal->setStyleSheet(tmpN);

                 }


                      }else if(status=="HOVER"){

                            int count;
                            count = SSBuffer.count();
                  tmpHover="";

         //               SSBuffer.removeAt(0);
   //  SSBuffer.insert(0,"QPushButton::hover{\n");
                        for(int i=0;i<count;i++){
                              wdt->SSBuffer_hover.removeAt(i);
                              wdt->SSBuffer_hover.insert(i, SSBuffer.at(i));
                        }

                      // if(!strList.isEmpty()){
                        //for(int i=0; i<strList.count(); i++){
                        //SSBuffer.insert(i, strList.at(i));



    //tmp = ui->code_edit->toPlainText();
    //font: 20 20pt 'ubuntu' ;
                        QRegExp exp("[ ]+");
                        for(int i=0; i<wdt->SSBuffer_hover.count(); i++){
                            if(!exp.exactMatch(wdt->SSBuffer_hover.at(i))){
                                 tmpHover+= wdt->SSBuffer_hover.at(i).trimmed()+"\n";
                            }
                        }
                                //qDebug()<<"RIGHTBOX.COUNT posle: "<<rightbox->count();

   // qDebug()<<"SS "<<tmp;
   // tmp=tmp+"}";
                        ui->code_edit->clear();
                     ui->code_edit->setText(tmpHover);
                     if(toolType=="PUSH_BUTTON_TOOL"){
                    wdt->btnHover->setStyleSheet(tmpHover);
                    if(check==false){
                        wdt->btnHover->setText("");
                    }else if(check==true){
                         wdt->btnHover->setText("Test");
                    }
                     }else if(toolType=="CHECK_BOX_TOOL"){
                       wdt->cboxHover->setStyleSheet(tmpHover);
                     }else if(toolType=="LABEL_TOOL"){
                       wdt->labelHover->setStyleSheet(tmpHover);

                     }


                        }else  if(status=="PRESSED"){

                                int count;
                                count = SSBuffer.count();
                            tmpPress="";
                   //         SSBuffer.removeAt(0);
    // SSBuffer.insert(0,"QPushButton::pressed{\n");
                              QRegExp exp("[ ]+");
                            for(int i=0;i<count;i++){
                                  wdt->SSBuffer_pressed.removeAt(i);
                                  wdt->SSBuffer_pressed.insert(i, SSBuffer.at(i));
                            }
                          // if(!strList.isEmpty()){
                            //for(int i=0; i<strList.count(); i++){
                            //SSBuffer.insert(i, strList.at(i));



        //tmp = ui->code_edit->toPlainText();
        //font: 20 20pt 'ubuntu' ;
                            for(int i=0; i<wdt->SSBuffer_pressed.count(); i++){
                                if(!exp.exactMatch(wdt->SSBuffer_pressed.at(i))){
                                     tmpPress+= wdt->SSBuffer_pressed.at(i).trimmed()+"\n";
                                }
                            }
                                    //qDebug()<<"RIGHTBOX.COUNT posle: "<<rightbox->count();
 //tmp = tmp+"}";
      //  qDebug()<<"SS "<<tmp;
                            ui->code_edit->clear();
                         ui->code_edit->setText(tmpPress);

                         if(toolType=="PUSH_BUTTON_TOOL"){
                             wdt->btnPressed->setStyleSheet(tmpPress);
                                     if(check==false){
                                         wdt->btnPressed->setText("");
                                     }else if(check==true){
                                          wdt->btnPressed->setText("Test");
                                     }
                         }else if(toolType=="CHECK_BOX_TOOL"){
                        //   wdt->cboxPressed->setStyleSheet(tmpPress);
                         }





                }

        }
    }
            }
//}


void Widget::SetCodeSS(QString panelType, QString toolType, QString status)
{
    QString tmpNC = "";
    QString tmpPressC="";
    QString tmpHoverC="";
   // if(toolType=="PUSH_BUTTON_TOOL"){

            for(int i = 0; i < box->count(); i++){
                DynamicWidgetTool *wdt = qobject_cast<DynamicWidgetTool*>(box->itemAt(i)->widget());
                if(wdt->getID()==wdt_ID){

                    if(status=="NORMAL"){

                        int count;
                        count = SSBuffer.count();
                    tmpNC="";
                  //  SSBuffer.removeAt(0);
                  //  SSBuffer.insert(0,"QPushButton{\n");


                            wdt->SSBuffer_nor.clear();
                    for(int i=0;i<count;i++){
                          wdt->SSBuffer_nor.removeAt(i);
                          wdt->SSBuffer_nor.insert(i, SSBuffer.at(i));
                    }

                  // if(!strList.isEmpty()){
                    //for(int i=0; i<strList.count(); i++){
                    //SSBuffer.insert(i, strList.at(i));



//tmp = ui->code_edit->toPlainText();
//font: 20 20pt 'ubuntu' ;
                    for(int i=0; i<wdt->SSBuffer_nor.count(); i++){
                     tmpNC+= wdt->SSBuffer_nor.at(i);
                    }
                   // tmp=tmp+"}";


                 if(toolType=="PUSH_BUTTON_TOOL"){
                wdt->btnNormal->setStyleSheet(tmpNC);

                 }else if(toolType=="CHECK_BOX_TOOL"){
                   //  QString m = "QCheckBox::indicator{\n";
                     //m+=tmpN +="}";
                   wdt->cboxNormal->setStyleSheet(tmpNC);

                 }else if(toolType=="LABEL_TOOL"){
                   wdt->labelNormal->setStyleSheet(tmpNC);

                 }


                      }else if(status=="HOVER"){

                            int count;
                            count = SSBuffer.count();
                  tmpHoverC="";
         wdt->SSBuffer_hover.clear();
         //               SSBuffer.removeAt(0);
   //  SSBuffer.insert(0,"QPushButton::hover{\n");
                        for(int i=0;i<count;i++){
                              wdt->SSBuffer_hover.removeAt(i);
                              wdt->SSBuffer_hover.insert(i, SSBuffer.at(i));
                        }

                      // if(!strList.isEmpty()){
                        //for(int i=0; i<strList.count(); i++){
                        //SSBuffer.insert(i, strList.at(i));



    //tmp = ui->code_edit->toPlainText();
    //font: 20 20pt 'ubuntu' ;
                        for(int i=0; i<wdt->SSBuffer_hover.count(); i++){
                         tmpHoverC+= wdt->SSBuffer_hover.at(i);
                        }
                                //qDebug()<<"RIGHTBOX.COUNT posle: "<<rightbox->count();

   // qDebug()<<"SS "<<tmp;

                     if(toolType=="PUSH_BUTTON_TOOL"){
                    wdt->btnHover->setStyleSheet(tmpHoverC);

                     }else if(toolType=="CHECK_BOX_TOOL"){
                       wdt->cboxHover->setStyleSheet(tmpHoverC);
                     }else if(toolType=="LABEL_TOOL"){
                       wdt->labelHover->setStyleSheet(tmpHoverC);

                     }


                        }else  if(status=="PRESSED"){
     wdt->SSBuffer_pressed.clear();
                                int count;
                                count = SSBuffer.count();
                            tmpPressC="";
                   //         SSBuffer.removeAt(0);
    // SSBuffer.insert(0,"QPushButton::pressed{\n");
                            for(int i=0;i<count;i++){
                                  wdt->SSBuffer_pressed.removeAt(i);
                                  wdt->SSBuffer_pressed.insert(i, SSBuffer.at(i));
                            }
                          // if(!strList.isEmpty()){
                            //for(int i=0; i<strList.count(); i++){
                            //SSBuffer.insert(i, strList.at(i));



        //tmp = ui->code_edit->toPlainText();
        //font: 20 20pt 'ubuntu' ;
                            for(int i=0; i<wdt->SSBuffer_pressed.count(); i++){
                             tmpPressC+= wdt->SSBuffer_pressed.at(i);
                            }
                                    //qDebug()<<"RIGHTBOX.COUNT posle: "<<rightbox->count();
 //tmp = tmp+"}";
      //  qDebug()<<"SS "<<tmp;
                          //  ui->code_edit->clear();
                        // ui->code_edit->setText(tmpPress);

                         if(toolType=="PUSH_BUTTON_TOOL"){
                             wdt->btnPressed->setStyleSheet(tmpPressC);

                         }else if(toolType=="CHECK_BOX_TOOL"){
                         // wdt->cboxPressed->setStyleSheet(tmpPressC);
                         }





                }

        }
    }
            }






void Widget::showMenu()
{
    // int x = ui->menuButton->pos().x()+5;
    //  int y = ui->menuButton->pos().y()+30;
    //  menu->popup(this->mapToGlobal(QPoint(x,y)));
}

void Widget::onDataChanged(QString PanelType, QString ToolType, QString status, int ID,bool cycle)
{
    ID_PANEL = ID;
    qDebug()<<"Data changed WIDGET!";
    qDebug()<<PanelType;
    qDebug()<<ToolType;
    if(ToolType=="PUSH_BUTTON_TOOL"){
        if(PanelType=="PANEL_TEXT"){
            // :)
            for(int i = 1; i < rightbox->count(); i++){
                /* Производим каст элемента слоя объект panel нужный находим
             * */
                Panel *panel = qobject_cast<Panel*>(rightbox->itemAt(i)->widget());

                if(panel->getID()==ID){

                    qDebug()<<"FROM WIDGET WIDGET PANEL_SIZE!!!: "<<panel->pn->getSizeF();
                    QString TEXT_SS =panel->pn->getSizeF();
                    QString size = "font: " + panel->pn->getBoldText() + " "+ TEXT_SS+"pt" + " '" + panel->pn->getFont() +"'" +";\n";
                    QString color = "color: " + panel->pn->getColor() + ";\n";
                    QString align= "text-align: left;\n";

                    if(panel->pn->getAlignmentF()==0){ //left
                        align= "text-align: left;\n";
                    }else if(panel->pn->getAlignmentF()==1){ //вверх центр
                        align= "text-align: top;\n";
                    }else if (panel->pn->getAlignmentF()==2){ //центр
                        align= "text-align: centre;\n";
                    }else if(panel->pn->getAlignmentF()==3){ //вниз центр
                        align= "text-align: bottom;\n";
                    }else if(panel->pn->getAlignmentF()==4){ //право

                        align= "text-align: right;\n";
                    }
                    if(!panel->pn->enableText->isChecked()){
                        check = false;
                    }else{

                        check = true;
                    }
                 //   SSBuffer="";

                   SSBuffer.removeAt(TextFont);
                   SSBuffer.insert(TextFont,size);
                   SSBuffer.removeAt(TextColor);
                  SSBuffer.insert(TextColor,color);
                    SSBuffer.removeAt(TextAlign);
                   SSBuffer.insert(TextAlign,align);

                   // += size += color += align;
qDebug()<<SSBuffer;
         int count;
       count =  SSBuffer.count();

       qDebug()<<"COUNT "<<count;
                    if(panel->GetStatus()=="NORMAL"){
                          //updateAllData("NORMAL","PUSH_BUTTON_TOOL",cycle);
                   SetSSDWT("PANEL_BACKGROUND","PUSH_BUTTON_TOOL", "NORMAL", panel->getID()-1, false);

                    }else if (panel->GetStatus()=="PRESSED"){
                          //updateAllData("PRESSED","PUSH_BUTTON_TOOL",cycle);
                       SetSSDWT("PANEL_BACKGROUND","PUSH_BUTTON_TOOL", "PRESSED",panel->getID()-1,false);
                    }else if (panel->GetStatus()=="HOVER"){
                         // updateAllData("HOVER","PUSH_BUTTON_TOOL",cycle);
                       SetSSDWT("PANEL_BACKGROUND","PUSH_BUTTON_TOOL", "HOVER",panel->getID()-1,false);
                    }
                }
            }


        }else if(PanelType=="PANEL_BACKGROUND"){
            for(int i = 1; i < rightbox->count(); i++){
                /* Производим каст элемента слоя в объект panel нужный находим
             * */
                Panel *panel = qobject_cast<Panel*>(rightbox->itemAt(i)->widget());
                if(panel->getID()==ID){
                    QString tmp_color="";

                    QString tmpCl = panel->contentBackground->getColor()+";\n";
                    tmp_color="background-color: " + tmpCl;
                    QString gradient_tmp = panel->contentBackground->getGradient()+";\n";
                  //  SSBuffer+=tmp_color+=gradient_tmp;

                    if(!panel->contentBackground->getGradient().isEmpty()){
                        SSBuffer.removeAt(BackgroundColor);
                        SSBuffer.insert(BackgroundColor,gradient_tmp);

                    }else if(!panel->contentBackground->getColor().isEmpty()){
                        SSBuffer.removeAt(BackgroundColor);
                         SSBuffer.insert(BackgroundColor,tmp_color);
                    }

                    int count;
                  count =  SSBuffer.count();
                    if(panel->GetStatus()=="NORMAL"){
                     //     updateAllData("NORMAL","PUSH_BUTTON_TOOL",cycle);
                    SetSSDWT("PANEL_BACKGROUND","PUSH_BUTTON_TOOL", "NORMAL", panel->getID()-1,false);
                    }else if (panel->GetStatus()=="PRESSED"){
                      //    updateAllData("PRESSED","PUSH_BUTTON_TOOL",cycle);
                   SetSSDWT("PANEL_BACKGROUND","PUSH_BUTTON_TOOL", "PRESSED", panel->getID()-1,false);
                    }else if (panel->GetStatus()=="HOVER"){
                      //    updateAllData("HOVER","PUSH_BUTTON_TOOL",cycle);
                     SetSSDWT("PANEL_BACKGROUND","PUSH_BUTTON_TOOL", "HOVER",  panel->getID()-1,false);

            }
                }
            }
        }else if(PanelType=="PANEL_ICON"){
            for(int i = 1; i < rightbox->count(); i++){
                /* Производим каст элемента слоя в объект panel нужный находим
             * */
                Panel *panel = qobject_cast<Panel*>(rightbox->itemAt(i)->widget());
                if(panel->getID()==ID){
                    QString tmp;
                    QString tmp1;
                    QString tmp2;
                    QString tmp3;
                  // tmp="image: url(" + panel->contentIcon->getIconPath() +"); \n";
                    tmp1=      "background-image: url("+ panel->contentIcon->getIconPath()+");\n";
                    tmp2  =          "background-repeat: " +panel->contentIcon->getRepeat()+";\n";
                    tmp3 =           "background-position: " +panel->contentIcon->getPos() +";\n";


                       if(!panel->contentIcon->getIconPath().isEmpty()){
                           SSBuffer.removeAt(BackgroundImage);
                           SSBuffer.insert(BackgroundImage,tmp1);
                    //   }else if(!panel->contentIcon->getRepeat().isEmpty()){
                           SSBuffer.removeAt(BackgroundRepeate);
                           SSBuffer.insert(BackgroundRepeate,tmp2);

                    //   }else if(!panel->contentIcon->getPos().isEmpty()){
                           SSBuffer.removeAt(BackgroundPosition);
                           SSBuffer.insert(BackgroundPosition,tmp3);
                       }

          //              qDebug()<<"ICON: "<<tmp;
                      //  int count;
                  //    count =  SSBuffer.count();
                      if(panel->GetStatus()=="NORMAL"){
                       //     updateAllData("NORMAL","PUSH_BUTTON_TOOL",cycle);
                      SetSSDWT("PANEL_ICON","PUSH_BUTTON_TOOL", "NORMAL", panel->getID()-1,false);
                      }else if (panel->GetStatus()=="PRESSED"){
                        //    updateAllData("PRESSED","PUSH_BUTTON_TOOL",cycle);
                     SetSSDWT("PANEL_ICON","PUSH_BUTTON_TOOL", "PRESSED", panel->getID()-1,false);
                      }else if (panel->GetStatus()=="HOVER"){
                        //    updateAllData("HOVER","PUSH_BUTTON_TOOL",cycle);
                       SetSSDWT("PANEL_ICON","PUSH_BUTTON_TOOL", "HOVER",  panel->getID()-1,false);

              }
                }
            }
        }else if(PanelType=="PANEL_ROUND"){
            for(int i = 1; i < rightbox->count(); i++){

                Panel *panel = qobject_cast<Panel*>(rightbox->itemAt(i)->widget());
                if(panel->getID()==ID){

                  QString tmp="";
                  QString lastTmp;
                // QString tmp = "border-width: 1px;"
                //               "border-radius: 10px;";
                //  tmp+="border-style: outset; \n";

                  if(!panel->contentRound->getRound().isEmpty()){
                     tmp= "border-radius: "+  panel->contentRound->getRound()+"px; \n";
                     SSBuffer.removeAt(Round);
                     SSBuffer.insert(Round,tmp);
           }

                // if(!panel->contentRound->enableRound->isChecked()){

                //  lastTmp = tmp;
                //          tmp="";
               //  }else{
                //     tmp = lastTmp;
                 //}


                //  tmp = "background-color: red";
                  qDebug()<<tmp;

                    int count;
                  count =  SSBuffer.count();
                    if(panel->GetStatus()=="NORMAL"){
                 //         updateAllData("NORMAL","PUSH_BUTTON_TOOL",cycle);
                   SetSSDWT("PANEL_ROUND","PUSH_BUTTON_TOOL", "NORMAL",  panel->getID()-1, false);
                    }else if (panel->GetStatus()=="PRESSED"){
                   //       updateAllData("PRESSED","PUSH_BUTTON_TOOL",cycle);
                     SetSSDWT("PANEL_ROUND","PUSH_BUTTON_TOOL", "PRESSED",  panel->getID()-1,false);
                    }else if (panel->GetStatus()=="HOVER"){
                    //      updateAllData("HOVER","PUSH_BUTTON_TOOL",cycle);
                       SetSSDWT("PANEL_ROUND","PUSH_BUTTON_TOOL", "HOVER", panel->getID()-1,false);


                }
            }
            }
        }else if(PanelType=="PANEL_MARGINS"){
            for(int i = 0; i < rightbox->count(); i++){

                Panel *panel = qobject_cast<Panel*>(rightbox->itemAt(i)->widget());
                if(panel->getID()==ID){

                    QString tmpz;
                    QString tmp1z;
                    QString tmp2z;
                    QString tmp3z;
                          tmp2z ="";
                    //QString lastTmp;
                  // QString tmp = "border-width: 1px;"
                            //     "border-radius: 10px;";
                          QString tmpcolor = panel->contentMargins->getColorBorder();
                          tmp2z=    "border-color: "+tmpcolor+ ";\n";
                tmpz="border-width: "+panel->contentMargins->getBoldBorder()+ "px;\n";
                tmp1z =   "border-style: " +panel->contentMargins->getTypeBorder() +";\n";

                tmp3z=    "padding: "+panel->contentMargins->getMArginInside()+"px;\n";

               // if(!panel->contentMargins->getBoldBorder().isEmpty()){
                    SSBuffer.removeAt(MarginWidth);
                    SSBuffer.insert(MarginWidth,tmpz);
               // }else if(!panel->contentMargins->getTypeBorder().isEmpty()){
                    SSBuffer.removeAt(MarginStyle);
                    SSBuffer.insert(MarginStyle,tmp1z);

                if(!panel->contentMargins->getColorBorder().isEmpty()){
                    SSBuffer.removeAt(MarginColor);
                    SSBuffer.insert(MarginColor,tmp2z);
                }
                 //     }else if(!panel->contentMargins->getMArginInside().isEmpty()){
                    SSBuffer.removeAt(MarginPadding);
                    SSBuffer.insert(MarginPadding,tmp3z);
                //}
                   // qDebug()<<tmp;




                  //  tmp = "background-color: red";
                //    qDebug()<<tmp;

                      int count;
                    count =  SSBuffer.count();
                      if(panel->GetStatus()=="NORMAL"){
                     //      updateAllData("NORMAL","PUSH_BUTTON_TOOL",cycle);
                     SetSSDWT("PANEL_MARGINS","PUSH_BUTTON_TOOL", "NORMAL", panel->getID()-1,false);

                      }else if (panel->GetStatus()=="PRESSED"){
                        //     updateAllData("PRESSED","PUSH_BUTTON_TOOL",cycle);
                 SetSSDWT("PANEL_MARGINS","PUSH_BUTTON_TOOL", "PRESSED", panel->getID()-1,false);
                      }else if (panel->GetStatus()=="HOVER"){
                       //      updateAllData("HOVER","PUSH_BUTTON_TOOL",cycle);
                SetSSDWT("PANEL_MARGINS","PUSH_BUTTON_TOOL", "HOVER", panel->getID()-1,false);

                }
                }
            }

        }

    }else if(ToolType=="CHECK_BOX_TOOL"){
        qDebug()<<"ToolType check box tool !!!";
        if(PanelType=="PANEL_TEXT"){
           // SSBuffer.insert(0,"QCheckBox{\n");
            // :)
            for(int i = 0; i < rightbox->count(); i++){
                /* Производим каст элемента слоя объект panel нужный находим
             * */
                Panel *panel = qobject_cast<Panel*>(rightbox->itemAt(i)->widget());

                if(panel->getID()==ID){

                    qDebug()<<"FROM WIDGET WIDGET PANEL_SIZE!!!: "<<panel->pn->getSizeF();
                    QString TEXT_SS = panel->pn->getSizeF();
                    QString size = "font: " + panel->pn->getBoldText() + " "+ TEXT_SS+"pt" + " '" + panel->pn->getFont() +"'" +";\n";
                    QString color = "color: " + panel->pn->getColor() + ";\n";
                    QString align= "text-align: left;\n";

                    if(panel->pn->getAlignmentF()==0){ //left
                        align= "text-align: left;\n";
                    }else if(panel->pn->getAlignmentF()==1){ //вверх центр
                        align= "text-align: top;\n";
                    }else if (panel->pn->getAlignmentF()==2){ //центр
                        align= "text-align: centre;\n";
                    }else if(panel->pn->getAlignmentF()==3){ //вниз центр
                        align= "text-align: bottom;\n";
                    }else if(panel->pn->getAlignmentF()==4){ //право

                        align= "text-align: right;\n";
                    }
                    //if(!panel->pn->enableText->isChecked()){
                     //   check = false;
                   // }else{

                     //   check = true;
                   // }
                 //   SSBuffer="";

                   QString temp="QCheckBox{\n";
                    if(panel->GetStatus()=="NORMAL"){
                       temp = "QCheckBox{\n";
                    }else if(panel->GetStatus()=="HOVER"){
                          temp = "QCheckBox::checked{\n";
                    }
                     SSBuffer.removeAt(CheckBox);
                    SSBuffer.insert(CheckBox,temp);
                    SSBuffer.removeAt(CloseCheckBox);
                    SSBuffer.insert(CloseCheckBox,"}\n");


                   SSBuffer.removeAt(TextFont);
                   SSBuffer.insert(TextFont,  size);
                   SSBuffer.removeAt(TextColor);
                  SSBuffer.insert(TextColor,color);
                    SSBuffer.removeAt(TextAlign);
                   SSBuffer.insert(TextAlign,align);


                   // += size += color += align;
qDebug()<<SSBuffer;
         int count;
       count =  SSBuffer.count();

       qDebug()<<"COUNT "<<count;
                    if(panel->GetStatus()=="NORMAL"){
                          //updateAllData("NORMAL","PUSH_BUTTON_TOOL",cycle);
                   SetSSDWT("PANEL_BACKGROUND","CHECK_BOX_TOOL", "NORMAL", panel->getID()-1, false);

                    }else if (panel->GetStatus()=="PRESSED"){
                          //updateAllData("PRESSED","PUSH_BUTTON_TOOL",cycle);
                       SetSSDWT("PANEL_BACKGROUND","CHECK_BOX_TOOL", "PRESSED",panel->getID()-1,false);
                    }else if (panel->GetStatus()=="HOVER"){
                      // updateAllData("HOVER","CHECK_BOX_TOOL",cycle);
                      SetSSDWT("PANEL_BACKGROUND","CHECK_BOX_TOOL", "HOVER",panel->getID()-1,false);
                    }
                }
            }
        }else if(PanelType=="PANEL_ROUND"){
            for(int i = 1; i < rightbox->count(); i++){

                Panel *panel = qobject_cast<Panel*>(rightbox->itemAt(i)->widget());
                if(panel->getID()==ID){

                  QString tmp="";
                  QString lastTmp;
                // QString tmp = "border-width: 1px;"
                //               "border-radius: 10px;";
                //  tmp+="border-style: outset; \n";

                  if(!panel->contentRound->getRound().isEmpty()){
                           tmp= "border-radius: "+  panel->contentRound->getRound()+"px; \n";
                     SSBuffer.removeAt(Round);
                     SSBuffer.insert(Round,tmp);
                  }

                // if(!panel->contentRound->enableRound->isChecked()){

                //  lastTmp = tmp;
                //          tmp="";
               //  }else{
                //     tmp = lastTmp;
                 //}


                //  tmp = "background-color: red";
                  qDebug()<<tmp;

                    int count;
                  count =  SSBuffer.count();
                    if(panel->GetStatus()=="NORMAL"){
                 //         updateAllData("NORMAL","PUSH_BUTTON_TOOL",cycle);
                   SetSSDWT("PANEL_ROUND","CHECK_BOX_TOOL", "NORMAL",  panel->getID()-1, false);
                    }else if (panel->GetStatus()=="PRESSED"){
                   //       updateAllData("PRESSED","PUSH_BUTTON_TOOL",cycle);
                     SetSSDWT("PANEL_ROUND","CHEK_BOX_TOOL", "PRESSED",  panel->getID()-1,false);
                    }else if (panel->GetStatus()=="HOVER"){
                    //      updateAllData("HOVER","PUSH_BUTTON_TOOL",cycle);
                       SetSSDWT("PANEL_ROUND","CHECK_BOX_TOOL", "HOVER", panel->getID()-1,false);


                }
            }
            }


    }else if(PanelType=="PANEL_BACKGROUND"){
        for(int i = 0; i < rightbox->count(); i++){
            /* Производим каст элемента слоя в объект panel нужный находим
         * */
            Panel *panel = qobject_cast<Panel*>(rightbox->itemAt(i)->widget());
            if(panel->getID()==ID){
                QString tmp_color;
                QString tmpCl = panel->contentBackground->getColor()+";\n";
                tmp_color="background-color: " + tmpCl;
                QString gradient_tmp = panel->contentBackground->getGradient()+";\n";
              //  SSBuffer+=tmp_color+=gradient_tmp;


               if(!panel->contentBackground->getGradient().isEmpty()){
                   SSBuffer.removeAt(BackgroundColor);
                   SSBuffer.insert(BackgroundColor,gradient_tmp);

               }else if(!panel->contentBackground->getColor().isEmpty()){
                   SSBuffer.removeAt(BackgroundColor);
                    SSBuffer.insert(BackgroundColor,tmp_color);
               }

                int count;
              count =  SSBuffer.count();
                if(panel->GetStatus()=="NORMAL"){
                 //     updateAllData("NORMAL","PUSH_BUTTON_TOOL",cycle);
                SetSSDWT("PANEL_BACKGROUND","CHECK_BOX_TOOL", "NORMAL", panel->getID()-1,false);
                }else if (panel->GetStatus()=="PRESSED"){
                  //    updateAllData("PRESSED","PUSH_BUTTON_TOOL",cycle);
               SetSSDWT("PANEL_BACKGROUND","CHECK_BOX_TOOL", "PRESSED", panel->getID()-1,false);
                }else if (panel->GetStatus()=="HOVER"){
                  //    updateAllData("HOVER","PUSH_BUTTON_TOOL",cycle);
                 SetSSDWT("PANEL_BACKGROUND","CHECK_BOX_TOOL", "HOVER",  panel->getID()-1,false);

        }
            }
        }

        }else if(PanelType=="PANEL_ICON"){
            for(int i = 1; i < rightbox->count(); i++){
                /* Производим каст элемента слоя в объект panel нужный находим
             * */
                Panel *panel = qobject_cast<Panel*>(rightbox->itemAt(i)->widget());
                if(panel->getID()==ID){
                    QString tmp;
                    QString tmp1;
                    QString tmp2;
                    QString tmp3;
                  // tmp="image: url(" + panel->contentIcon->getIconPath() +"); \n";

int CBOX;
int CBOXC;
                    if(status=="NORMAL"){
                           tmp=      "QCheckBox::indicator{\n";
                           CBOX=CheckBoxIndicator;
                             CBOXC=CloseCheckBoxIndicator;
                    }else if(status=="HOVER"){
                        tmp=      "QCheckBox::indicator:checked{\n";
                        CBOX=CheckBoxChecked;
                        CBOXC=CloseCheckBoxChecked;
                    }
                    tmp1= "image: url("+ panel->contentIcon->getIconPath()+");\n";

                                                                               ;
                   tmp2  =          "width: " +panel->contentIcon->getWidth()+";\n";
                          tmp3  =          "height: " +panel->contentIcon->getHeight()+";\n";
                   // tmp3 =           "background-position: " +panel->contentIcon->getPos() +";\n";
//QString tmp4;
// tmp4="}\n";
// tmp3+=tmp4;

                       if(!panel->contentIcon->getIconPath().isEmpty()){
                           SSBuffer.removeAt(CBOX);
                           SSBuffer.insert(CBOX,tmp);

                           SSBuffer.removeAt(Image);
                           SSBuffer.insert(Image,tmp1);
                    //   }else if(!panel->contentIcon->getRepeat().isEmpty()){
                           SSBuffer.removeAt(PWidth);
                          SSBuffer.insert(PWidth,tmp2);

                    //   }else if(!panel->contentIcon->getPos().isEmpty()){
                           SSBuffer.removeAt(PHeight);
                          SSBuffer.insert(PHeight,tmp3);
                          SSBuffer.removeAt(CBOXC);
                          SSBuffer.insert(CBOXC,"}\n");
                       }


                    SetSSDWT(PanelType,currentToolchain, status, panel->getID()-1,false);

                }
            }
        }

}else if(ToolType=="LABEL_TOOL"){
        if(PanelType=="PANEL_TEXT"){
            // :)
            for(int i = 1; i < rightbox->count(); i++){
                /* Производим каст элемента слоя объект panel нужный находим
             * */
                Panel *panel = qobject_cast<Panel*>(rightbox->itemAt(i)->widget());

                if(panel->getID()==ID){

                    qDebug()<<"FROM WIDGET WIDGET PANEL_SIZE!!!: "<<panel->pn->getSizeF();
                    QString TEXT_SS =panel->pn->getSizeF();
                    QString size = "font: " + panel->pn->getBoldText() + " "+ TEXT_SS+"pt" + " '" + panel->pn->getFont() +"'" +";\n";
                    QString color = "color: " + panel->pn->getColor() + ";\n";
                    QString align= "text-align: left;\n";

                    if(panel->pn->getAlignmentF()==0){ //left
                        align= "text-align: left;\n";
                    }else if(panel->pn->getAlignmentF()==1){ //вверх центр
                        align= "text-align: top;\n";
                    }else if (panel->pn->getAlignmentF()==2){ //центр
                        align= "text-align: centre;\n";
                    }else if(panel->pn->getAlignmentF()==3){ //вниз центр
                        align= "text-align: bottom;\n";
                    }else if(panel->pn->getAlignmentF()==4){ //право

                        align= "text-align: right;\n";
                    }
                    if(!panel->pn->enableText->isChecked()){
                        check = false;
                    }else{

                        check = true;
                    }
                 //   SSBuffer="";

                   SSBuffer.removeAt(TextFont);
                   SSBuffer.insert(TextFont,size);
                   SSBuffer.removeAt(TextColor);
                  SSBuffer.insert(TextColor,color);
                    SSBuffer.removeAt(TextAlign);
                   SSBuffer.insert(TextAlign,align);

                   // += size += color += align;
qDebug()<<SSBuffer;
         int count;
       count =  SSBuffer.count();

       qDebug()<<"COUNT "<<count;
                    if(panel->GetStatus()=="NORMAL"){
                          //updateAllData("NORMAL","PUSH_BUTTON_TOOL",cycle);
                   SetSSDWT("PANEL_BACKGROUND","LABEL_TOOL", "NORMAL", panel->getID()-1, false);

                    }else if (panel->GetStatus()=="PRESSED"){
                          //updateAllData("PRESSED","PUSH_BUTTON_TOOL",cycle);
                       SetSSDWT("PANEL_BACKGROUND","LABEL_TOOL", "PRESSED",panel->getID()-1,false);
                    }else if (panel->GetStatus()=="HOVER"){
                         // updateAllData("HOVER","PUSH_BUTTON_TOOL",cycle);
                       SetSSDWT("PANEL_BACKGROUND","LABEL_TOOL", "HOVER",panel->getID()-1,false);
                    }
                }
            }


        }else if(PanelType=="PANEL_BACKGROUND"){
            for(int i = 1; i < rightbox->count(); i++){
                /* Производим каст элемента слоя в объект panel нужный находим
             * */
                Panel *panel = qobject_cast<Panel*>(rightbox->itemAt(i)->widget());
                if(panel->getID()==ID){
                    QString tmp_color="";
                    QString tmpCl = panel->contentBackground->getColor()+";\n";
                    tmp_color="background-color: " + tmpCl;
                    QString gradient_tmp = panel->contentBackground->getGradient()+";\n";
                  //  SSBuffer+=tmp_color+=gradient_tmp;

                    if(!panel->contentBackground->getGradient().isEmpty()){
                        SSBuffer.removeAt(BackgroundColor);
                        SSBuffer.insert(BackgroundColor,gradient_tmp);

                    }else if(!panel->contentBackground->getColor().isEmpty()){
                        SSBuffer.removeAt(BackgroundColor);
                         SSBuffer.insert(BackgroundColor,tmp_color);
                    }

                    int count;
                  count =  SSBuffer.count();
                    if(panel->GetStatus()=="NORMAL"){
                     //     updateAllData("NORMAL","PUSH_BUTTON_TOOL",cycle);
                    SetSSDWT("PANEL_BACKGROUND","LABEL_TOOL", "NORMAL", panel->getID()-1,false);
                    }else if (panel->GetStatus()=="PRESSED"){
                      //    updateAllData("PRESSED","PUSH_BUTTON_TOOL",cycle);
                   SetSSDWT("PANEL_BACKGROUND","LABEL_TOOL", "PRESSED", panel->getID()-1,false);
                    }else if (panel->GetStatus()=="HOVER"){
                      //    updateAllData("HOVER","PUSH_BUTTON_TOOL",cycle);
                     SetSSDWT("PANEL_BACKGROUND","LABEL_TOOL", "HOVER",  panel->getID()-1,false);

            }
                }
            }
        }else if(PanelType=="PANEL_ICON"){
            for(int i = 1; i < rightbox->count(); i++){
                /* Производим каст элемента слоя в объект panel нужный находим
             * */
                Panel *panel = qobject_cast<Panel*>(rightbox->itemAt(i)->widget());
                if(panel->getID()==ID){
                    QString tmp;
                    QString tmp1;
                    QString tmp2;
                    QString tmp3;
                  // tmp="image: url(" + panel->contentIcon->getIconPath() +"); \n";
                    tmp1=      "background-image: url("+ panel->contentIcon->getIconPath()+");\n";
                    tmp2  =          "background-repeat: " +panel->contentIcon->getRepeat()+";\n";
                    tmp3 =           "background-position: " +panel->contentIcon->getPos() +";\n";


                       if(!panel->contentIcon->getIconPath().isEmpty()){
                           SSBuffer.removeAt(BackgroundImage);
                           SSBuffer.insert(BackgroundImage,tmp1);
                    //   }else if(!panel->contentIcon->getRepeat().isEmpty()){
                           SSBuffer.removeAt(BackgroundRepeate);
                           SSBuffer.insert(BackgroundRepeate,tmp2);

                    //   }else if(!panel->contentIcon->getPos().isEmpty()){
                           SSBuffer.removeAt(BackgroundPosition);
                           SSBuffer.insert(BackgroundPosition,tmp3);
                       }

          //              qDebug()<<"ICON: "<<tmp;
                      //  int count;
                  //    count =  SSBuffer.count();
                      if(panel->GetStatus()=="NORMAL"){
                       //     updateAllData("NORMAL","LABEL_TOOL",cycle);
                      SetSSDWT("PANEL_ICON","PUSH_BUTTON_TOOL", "NORMAL", panel->getID()-1,false);
                      }else if (panel->GetStatus()=="PRESSED"){
                        //    updateAllData("PRESSED","LABEL_TOOL",cycle);
                     SetSSDWT("PANEL_ICON","PUSH_BUTTON_TOOL", "PRESSED", panel->getID()-1,false);
                      }else if (panel->GetStatus()=="HOVER"){
                        //    updateAllData("HOVER","PUSH_BUTTON_TOOL",cycle);
                       SetSSDWT("PANEL_ICON","LABEL_TOOL", "HOVER",  panel->getID()-1,false);

              }
                }
            }
        }else if(PanelType=="PANEL_ROUND"){
            for(int i = 1; i < rightbox->count(); i++){

                Panel *panel = qobject_cast<Panel*>(rightbox->itemAt(i)->widget());
                if(panel->getID()==ID){

                  QString tmp="";
                  QString lastTmp;
                // QString tmp = "border-width: 1px;"
                //               "border-radius: 10px;";
                //  tmp+="border-style: outset; \n";

                  if(!panel->contentRound->getRound().isEmpty()){
                        tmp= "border-radius: "+  panel->contentRound->getRound()+"px; \n";
                     SSBuffer.removeAt(Round);
                     SSBuffer.insert(Round,tmp);
                  }

                // if(!panel->contentRound->enableRound->isChecked()){

                //  lastTmp = tmp;
                //          tmp="";
               //  }else{
                //     tmp = lastTmp;
                 //}


                //  tmp = "background-color: red";
                  qDebug()<<tmp;

                    int count;
                  count =  SSBuffer.count();
                    if(panel->GetStatus()=="NORMAL"){
                 //         updateAllData("NORMAL","PUSH_BUTTON_TOOL",cycle);
                   SetSSDWT("PANEL_ROUND","LABEL_TOOL", "NORMAL",  panel->getID()-1, false);
                    }else if (panel->GetStatus()=="PRESSED"){
                   //       updateAllData("PRESSED","PUSH_BUTTON_TOOL",cycle);
                     SetSSDWT("PANEL_ROUND","LABEL_TOOL", "PRESSED",  panel->getID()-1,false);
                    }else if (panel->GetStatus()=="HOVER"){
                    //      updateAllData("HOVER","PUSH_BUTTON_TOOL",cycle);
                       SetSSDWT("PANEL_ROUND","LABEL_TOOL", "HOVER", panel->getID()-1,false);


                }
            }
            }
        }else if(PanelType=="PANEL_MARGINS"){
            for(int i = 0; i < rightbox->count(); i++){

                Panel *panel = qobject_cast<Panel*>(rightbox->itemAt(i)->widget());
                if(panel->getID()==ID){

                    QString tmpz;
                    QString tmp1z;
                    QString tmp2z;
                    QString tmp3z;
                          tmp2z ="";
                    //QString lastTmp;
                  // QString tmp = "border-width: 1px;"
                            //     "border-radius: 10px;";
                          QString tmpcolor = panel->contentMargins->getColorBorder();
                          tmp2z=    "border-color: "+tmpcolor+ ";\n";
                tmpz="border-width:"+panel->contentMargins->getBoldBorder()+ "px;\n";
                tmp1z =   "border-style:" +panel->contentMargins->getTypeBorder() +";\n";

                tmp3z=    "padding: "+panel->contentMargins->getMArginInside()+"px;\n";

               // if(!panel->contentMargins->getBoldBorder().isEmpty()){
                    SSBuffer.removeAt(MarginWidth);
                    SSBuffer.insert(MarginWidth,tmpz);
               // }else if(!panel->contentMargins->getTypeBorder().isEmpty()){
                    SSBuffer.removeAt(MarginStyle);
                    SSBuffer.insert(MarginStyle,tmp1z);

                if(!panel->contentMargins->getColorBorder().isEmpty()){
                    SSBuffer.removeAt(MarginColor);
                    SSBuffer.insert(MarginColor,tmp2z);
                }
                 //     }else if(!panel->contentMargins->getMArginInside().isEmpty()){
                    SSBuffer.removeAt(MarginPadding);
                    SSBuffer.insert(MarginPadding,tmp3z);
                //}
                   // qDebug()<<tmp;




                  //  tmp = "background-color: red";
                //    qDebug()<<tmp;

                      int count;
                    count =  SSBuffer.count();
                      if(panel->GetStatus()=="NORMAL"){
                     //      updateAllData("NORMAL","PUSH_BUTTON_TOOL",cycle);
                     SetSSDWT("PANEL_MARGINS","LABEL_TOOL", "NORMAL", panel->getID()-1,false);

                      }else if (panel->GetStatus()=="PRESSED"){
                        //     updateAllData("PRESSED","PUSH_BUTTON_TOOL",cycle);
                 SetSSDWT("PANEL_MARGINS","LABEL_TOOL", "PRESSED", panel->getID()-1,false);
                      }else if (panel->GetStatus()=="HOVER"){
                       //      updateAllData("HOVER","PUSH_BUTTON_TOOL",cycle);
                SetSSDWT("PANEL_MARGINS","LABEL_TOOL", "HOVER", panel->getID()-1,false);

                }
                }
            }

        }

}
}






void Widget::on_code_edit_textChanged()
{
    if(codeCycle==false){
 QStringList list;
    codeEdit(false,list);

    }else if(codeCycle==true){
        codeCycle=false;
        qDebug()<<"edit RETURN BREAK!!11";
        return;

    }
}



void Widget::newPanel( QString type, QString status) // 1)type 2)toolType 3)statusPanel
{
    statusWidget = status;
    qDebug()<<"RIGHTBOX.COUNT DO: "<<rightbox->count();
    removeAllPanels();
   // if(currentTool==PUSH_BUTTON_TOOL){
        //    if(type=="PANEL_TEXT"){

  //if(first_hover)



        if(currentTool==PUSH_BUTTON_TOOL){
            first_hover=btnh;
            first_pressed=btnp;
            first_normal=btnn;
        }else if(currentTool==CHECK_BOX_TOOL){
            first_hover=cboxh;
           // first_pressed=cboxp;
            first_normal=cboxn;
        }else if(currentTool==LABEL_TOOL){
            first_hover=labelh;
            first_normal=labeln;
        }
        //if(btn=true){

        //}

  if (status=="NORMAL"){
           codeCycle=true;
           ui->code_edit->clear();
        QString tmpN="";
        SSBuffer.clear();

        for(int i = 0; i < box->count(); i++){

            DynamicWidgetTool *wdt = qobject_cast<DynamicWidgetTool*>(box->itemAt(i)->widget());
            if(wdt->getID()==wdt_ID){
               // if(statusWidget=="HOVER"){
                 TextFont =   wdt->NTextFont;
                    TextColor=wdt->NTextColor;
                   TextAlign=wdt->NTextAlign;
                  BackgroundColor= wdt->NBackgroundColor;
                  BackgroundImage=wdt->NBackgroundImage;
                 BackgroundRepeate= wdt->NBackgroundRepeate;
                 BackgroundPosition=  wdt->NBackgroundPosition;
                Round= wdt->NRound;
                 MarginWidth=wdt->NMarginWidth;
                 MarginStyle= wdt->NMarginStyle;
                 MarginColor=  wdt->NMarginColor;
                  MarginPadding= wdt->NMarginPadding;
                  Image =    wdt->NImage;
                    PWidth =   wdt->Nwidth;
                    PHeight =   wdt->NHeight;
                   CloseCheckBoxIndicator =    wdt->NCloseCBoxIndicatorClose;
                  CheckBoxIndicator =    wdt->NCheckBoxIndicator;
                  CheckBox =      wdt->NCheckBox;
                  CloseCheckBox =  wdt->NCloseCheckBox;

                  for(int i=0; i<wdt->SSBuffer_nor.count();i++){
                      SSBuffer.removeAt(i);
                      SSBuffer.insert(i,wdt->SSBuffer_nor.at(i));
                  }
                  for(int i=0; i<wdt->SSBuffer_nor.count(); i++){
                   tmpN+= wdt->SSBuffer_nor.at(i);
                  }






        }
        }



        ui->code_edit->setText(tmpN);

        if(first_normal==true){

            addPanel(status);
            first_normal=false;
             SSBuffer.clear();
              insertTOList(12);
              if(currentToolchain=="PUSH_BUTTON_TOOL"){
                  btnn=first_normal;
              }else if(currentToolchain=="CHECK_BOX_TOOL"){
                       cboxn=first_normal;

              }else if(currentToolchain=="CHECK_BOX_TOOL"){
                       labeln=first_normal;

              }

        }else if(first_normal==false){

            for(int i = 0; i < rightbox->count(); i++){
                /* Производим каст элемента слоя в объект динамической кнопки
                 * */
                Panel *panel = qobject_cast<Panel*>(rightbox->itemAt(i)->widget());
                if(panel->getStatus()==status){
    if(panel->getTool()==currentToolchain){
                    codeCycle=true;
                    ui->code_edit->clear();
                    ui->code_edit->setText(tmpN);
                    //codeEdit();
                    panel->setVisible(true);
                     //      SetSSDWT("PANEL_BACKGROUND","PUSH_BUTTON_TOOL", "HOVER",  panel->getID()-1,false);
                }
                }
            }
        }

              }else if (status=="HOVER"){
            QString tmp="";
            SSBuffer.clear();
            codeCycle=true;
            ui->code_edit->clear();
            for(int i=0;i<SSBuffer.count();i++) SSBuffer.removeAt(i);
            for(int i = 0; i < box->count(); i++){

                DynamicWidgetTool *wdt = qobject_cast<DynamicWidgetTool*>(box->itemAt(i)->widget());

                if(wdt->getID()==wdt_ID){

                   // if(statusWidget=="HOVER"){
                     TextFont =   wdt->HTextFont;
                        TextColor=wdt->HTextColor;
                       TextAlign=wdt->HTextAlign;
                      BackgroundColor= wdt->HBackgroundColor;
                      BackgroundImage=wdt->HBackgroundImage;
                     BackgroundRepeate= wdt->HBackgroundRepeate;
                     BackgroundPosition=  wdt->HBackgroundPosition;
                    Round= wdt->HRound;
                     MarginWidth=wdt->HMarginWidth;
                     MarginStyle= wdt->HMarginStyle;
                     MarginColor=  wdt->HMarginColor;
                      MarginPadding= wdt->HMarginPadding;
                      Image =  wdt->HImage;
                     PWidth =   wdt->Hwidth ;
                       PHeight =  wdt->HHeight;
                       CheckBoxChecked =  wdt->HCheckBoxChecked;
                      CloseCheckBoxChecked =  wdt->HCloseCheckBoxChecked;
                      CheckBox =  wdt->HCheckBox;
                      CloseCheckBox = wdt->HCloseCheckBox;

                      for(int i=0; i<wdt->SSBuffer_hover.count();i++){
                          SSBuffer.insert(i,wdt->SSBuffer_hover.at(i));
                      }
                      for(int i=0; i<wdt->SSBuffer_hover.count(); i++){
                       tmp+= wdt->SSBuffer_hover.at(i);
                      }

            }

}

 codeCycle=true;
            ui->code_edit->setText(tmp);
            if(first_hover==true){
                addPanel(status);
                first_hover=false;
                 SSBuffer.clear();
                  insertTOList(12);
                  if(currentToolchain=="PUSH_BUTTON_TOOL"){
                      btnh=first_hover;
                  }else if(currentToolchain=="CHECK_BOX_TOOL"){
                           cboxh=first_hover;

                  }else if(currentToolchain=="LABEL_TOOL"){
                           labelh=first_hover;

                  }
            }else if(first_hover==false){

                for(int i = 0; i < rightbox->count(); i++){
                    /* Производим каст элемента слоя в объект динамической кнопки
                     * */
                    Panel *panel = qobject_cast<Panel*>(rightbox->itemAt(i)->widget());
                    if(panel->getStatus()==status){
if(panel->getTool()==currentToolchain){
                        codeCycle=true;
                        ui->code_edit->clear();

                        ui->code_edit->setText(tmp);
                        //codeEdit();
                        panel->setVisible(true);
                         //      SetSSDWT("PANEL_BACKGROUND","PUSH_BUTTON_TOOL", "HOVER",  panel->getID()-1,false);
                    }
                    }
                }
            }



        }else if (status=="PRESSED"){
            SSBuffer.clear();
            for(int i=0;i<SSBuffer.count();i++) SSBuffer.removeAt(i);
                codeCycle=true;
                 ui->code_edit->clear();
                QString tmpc ="";
            for(int i = 0; i < box->count(); i++){

                DynamicWidgetTool *wdt = qobject_cast<DynamicWidgetTool*>(box->itemAt(i)->widget());

                if(wdt->getID()==wdt_ID){
                    //if(statusWidget=="PRESSED"){
                     TextFont =   wdt->PTextFont;
                     TextColor=  wdt->PTextColor;
                      TextAlign =  wdt->PTextAlign;
                       BackgroundColor= wdt->PBackgroundColor;
                      BackgroundImage=wdt->PBackgroundImage;
                     BackgroundRepeate= wdt->PBackgroundRepeate;
                      BackgroundPosition=  wdt->PBackgroundPosition;
                      Round= wdt->PRound;
                     MarginWidth=wdt->PMarginWidth;
                      MarginStyle=wdt->PMarginStyle;
                      MarginColor= wdt->PMarginColor;
                       MarginPadding=wdt->PMarginPadding;
                       for(int i=0; i<wdt->SSBuffer_pressed.count();i++){
                           SSBuffer.removeAt(i);
                           SSBuffer.insert(i,wdt->SSBuffer_pressed.at(i));
                       }
                       for(int i=0; i<wdt->SSBuffer_pressed.count(); i++){
                        tmpc+= wdt->SSBuffer_pressed.at(i);
                       }
                   // }

            }
            }

              codeCycle=true;
           ui->code_edit->setText(tmpc);





            if(first_pressed==true){
                        //  SSBuffer.clear();
                addPanel(status);
                first_pressed=false;
                if(currentToolchain=="PUSH_BUTTON_TOOL"){
                    btnp=first_pressed;
                }else if(currentToolchain=="CHECK_BOX_TOOL"){
                         cboxp=first_pressed;
                         qDebug("CHECKBOX-TOOLCHAIN-MAKING!");

                }
                  insertTOList(12);
            }else if(first_pressed==false){
                for(int i = 0; i < rightbox->count(); i++){
                    /* Производим каст элемента слоя в объект динамической кнопки
                     * */
                    Panel *panel = qobject_cast<Panel*>(rightbox->itemAt(i)->widget());
                    if(panel->getStatus()==status){
if(panel->getTool()==currentToolchain){

                       // codeEdit();

                          //    updateAllData("HOVER","PUSH_BUTTON_TOOL",cycle);


                    qDebug()<<"SSPREssed: "<< tmpc;
                    ui->code_edit->clear();
                   ui->code_edit->setText(tmpc);


                        panel->setVisible(true);
                    }
                    }
                }
          //  }

        }




        //}
    }
}

void Widget::tabContextMenuOpen(QPoint points)
{

}

void Widget::close()
{
    this->close();
}

void Widget::saveAs()
{
    qDebug()<<"SAveAS!";
    QString snormal="";
    QString shover="";
    QString spressed="";
    QRegExp trim("[]|[ ]+");
    QtDesignerSS="";
    for(int i = 0; i < box->count(); i++){

        DynamicWidgetTool *wdt = qobject_cast<DynamicWidgetTool*>(box->itemAt(i)->widget());
       // if(wdt->getID()==wdt_ID){

            if(wdt->getType()=="PUSH_BUTTON_TOOL"){
                snormal="QPushButton{\n";
                 shover="QPushButton::hover{\n";
                  spressed="QPushButton::pressed{\n";
                  QtDesignerSS="";
                  for(int i=0; i<wdt->SSBuffer_nor.count(); i++){
                      if(trim.exactMatch(wdt->SSBuffer_nor.at(i))==false){
                          snormal+= wdt->SSBuffer_nor.at(i).trimmed()+"\n";
                      }
                  }
                  for(int i=0; i<wdt->SSBuffer_hover.count(); i++){
                      if(trim.exactMatch(wdt->SSBuffer_hover.at(i))==false){
                          shover+= wdt->SSBuffer_hover.at(i).trimmed()+"\n";
                      }
                  }
                  for(int i=0; i<wdt->SSBuffer_pressed.count(); i++){
                      if(trim.exactMatch(wdt->SSBuffer_pressed.at(i))==false){
                          spressed+= wdt->SSBuffer_pressed.at(i).trimmed()+"\n";
                      }
                  }
                   QtDesignerSS+= snormal.append("\n}\n");
                   QtDesignerSS+= shover.append("\n}\n");
                   QtDesignerSS+= spressed.append("\n}\n");
                  projectCodeFile+="PUSH_BUTTON_TOOL begin\n";
                   projectCodeFile+=QtDesignerSS;
                   projectCodeFile.append("end\n");
                   //qDebug()<<"projectCodeFile";
            }else if(wdt->getType()=="CHECK_BOX_TOOL"){
                snormal="CHECK_BOX_TOOL::UNCHECKED begin\n";
                 shover="CHECK_BOX_TOOL::CHECKED begin\n";
                 QtDesignerSS="";
                 //spressed="";


                                  for(int i=0; i<wdt->SSBuffer_nor.count(); i++){
                                      if(trim.exactMatch(wdt->SSBuffer_nor.at(i))==false){
                                      snormal+= wdt->SSBuffer_nor.at(i).trimmed()+"\n";
                                      }
                                  }
                                  for(int i=0; i<wdt->SSBuffer_hover.count(); i++){
                                      if(trim.exactMatch(wdt->SSBuffer_hover.at(i))==false){
                                      shover+= wdt->SSBuffer_hover.at(i).trimmed()+"\n";
                                      }
                                  }
                 //for(int i=0; i<wdt->SSBuffer_pressed.count(); i++){
                 //  spressed+= wdt->SSBuffer_pressed.at(i);
                 //}
                 QtDesignerSS+= snormal.append("end::unchecked\n");
                 QtDesignerSS+= shover.append("end::checked\n");


                 projectCodeFile+=QtDesignerSS;
                 projectCodeFile+="end::tools";

            }else if(wdt->getType()=="LABEL_TOOL"){
                snormal="QLabel{\n";
                 shover="QLabel::hover{\n";
                 QtDesignerSS="";
                 //spressed="";

QRegExp trim("[]|[ ]+");
                 for(int i=0; i<wdt->SSBuffer_nor.count(); i++){
                     if(trim.exactMatch(wdt->SSBuffer_nor.at(i))==false){
                     snormal+= wdt->SSBuffer_nor.at(i).trimmed()+"\n";
                     }
                 }
                 for(int i=0; i<wdt->SSBuffer_hover.count(); i++){
                     if(trim.exactMatch(wdt->SSBuffer_hover.at(i))==false){
                     shover+= wdt->SSBuffer_hover.at(i).trimmed()+"\n";
                     }
                 }
                 //for(int i=0; i<wdt->SSBuffer_pressed.count(); i++){
                 //  spressed+= wdt->SSBuffer_pressed.at(i);
                 //}
                 QtDesignerSS+= snormal.append("\n}\n");
                 QtDesignerSS+= shover.append("\n}\n");

                 projectCodeFile+="LABEL_TOOL begin\n";
                 projectCodeFile+=QtDesignerSS;

                 projectCodeFile.append("end\n");
            }
    }
    if(fileProject->open(QIODevice::WriteOnly|QIODevice::Text))
    {
        QFileInfo info(fileNames);
        this->setWindowTitle("QSS - "+info.fileName());
        fileProject->write(projectCodeFile.toUtf8());
        fileProject->close();
    }
}

void Widget::home()
{

  //  main_screen *main = new QWidget(this);
   // main->show();
     //   this->close();
}


void Widget::on_copyWidgetSS_clicked()
{
    QtDesignerSS="";
    notificationPopUp *notify = new notificationPopUp;
    notify->textOglav = "Для вставки Виджета";
             notify->textNotify = "CTRL+V в QtDesigner";
             notify->setN();
             notify->setOglav();
     notify->show();

    QClipboard *clipboard = QApplication::clipboard();
  //  QString originalText = clipboard->text();

   QString tmpXml ="";
    for(int i = 0; i < box->count(); i++){

        DynamicWidgetTool *wdt = qobject_cast<DynamicWidgetTool*>(box->itemAt(i)->widget());
        if(wdt->getID()==wdt_ID){
            //if(statusWidget=="PRESSED"){
            QString snormal="";
            QString shover="";
            QString spressed="";
            if(currentToolchain=="PUSH_BUTTON_TOOL"){
                snormal="QPushButton{\n";
                          shover="QPushButton::hover{\n";
                           spressed="QPushButton::pressed{\n";

               for(int i=0; i<wdt->SSBuffer_nor.count(); i++){
                snormal+= wdt->SSBuffer_nor.at(i);
               }
               for(int i=0; i<wdt->SSBuffer_hover.count(); i++){
                shover+= wdt->SSBuffer_hover.at(i);
               }
               for(int i=0; i<wdt->SSBuffer_pressed.count(); i++){
                spressed+= wdt->SSBuffer_pressed.at(i);
               }
              QtDesignerSS+= snormal.append("\n}\n");
              QtDesignerSS+= shover.append("\n}\n");
              QtDesignerSS+= spressed.append("\n}\n");

              tmpXml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
                     "<ui version=\"4.0\">"
                      "<widget name=\"__qt_fake_top_level\">"
                       "<widget class=\"QPushButton\" name=\"pushButton\">"
                        "<property name=\"geometry\">"
                         "<rect>"
                          "<x>60</x>"
                       "<y>120</y>"
                       "<width>211</width>"
                       "<height>41</height>"
                       "</rect>"
                       "</property>"
                       "<property name=\"styleSheet\">"
                       "<string notr=\"true\">";
              tmpXml+=QtDesignerSS;
              tmpXml.append("</string>"
                            "</property>"
                            "<property name=\"text\">"
                            "<string>PushButton</string>"
                            "</property>"
                            "</widget>"
                            "</widget>"
                            "<resources/>"
                            "</ui>\""
                            );


            }else if(currentToolchain=="CHECK_BOX_TOOL"){
                snormal="";
                          shover="";
                           spressed="";

               for(int i=0; i<wdt->SSBuffer_nor.count(); i++){
                snormal+= wdt->SSBuffer_nor.at(i);
               }
               for(int i=0; i<wdt->SSBuffer_hover.count(); i++){
                shover+= wdt->SSBuffer_hover.at(i);
               }

              QtDesignerSS+= snormal;
              QtDesignerSS+= shover;


              tmpXml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
                      "<ui version=\"4.0\">"
                       "<widget name=\"__qt_fake_top_level\">"
                        "<widget class=\"QCheckBox\" name=\"checkBox\">"
                         "<property name=\"geometry\">"
                          "<rect>"
                           "<x>80</x>"
                           "<y>160</y>"
                           "<width>101</width>"
                           "<height>31</height>"
                          "</rect>"
                        "</property>"
                         "<property name=\"styleSheet\">"
                          "<string notr=\"true\">";
              tmpXml+=QtDesignerSS;
              tmpXml.append(" </string>"
                            "</property>"
                            "<property name=\"text\">"
                             "<string>on</string>"
                            "</property>"
                           "</widget>"
                          "</widget>"
                          "<resources/>"
                         "</ui>"
                            );



            }else if(currentToolchain=="LABEL_TOOL"){
                snormal="QLabel{\n";
                          shover="QLabel::hover{";
                           spressed="";

               for(int i=0; i<wdt->SSBuffer_nor.count(); i++){
                snormal+= wdt->SSBuffer_nor.at(i);
               }
               for(int i=0; i<wdt->SSBuffer_hover.count(); i++){
                shover+= wdt->SSBuffer_hover.at(i);
               }

              QtDesignerSS+= snormal.append("\n}\n");
              QtDesignerSS+= shover.append("\n}\n");


              tmpXml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
                      "<ui version=\"4.0\">"
                       "<widget name=\"__qt_fake_top_level\">"
                        "<widget class=\"QLabel\" name=\"label\">"
                         "<property name=\"geometry\">"
                          "<rect>"
                           "<x>40</x>"
                           "<y>170</y>"
                           "<width>111</width>"
                           "<height>31</height>"
                          "</rect>"
                         "</property>"
                         "<property name=\"styleSheet\">"
                          "<string notr=\"true\">";
              tmpXml+=QtDesignerSS;
              tmpXml.append(" </string>"
                            "</property>"
                            "<property name=\"text\">"
                             "<string>TextLabel</string>"
                            "</property>"
                           "</widget>"
                          "</widget>"
                          "<resources/>"
                         "</ui>"
                            );
        }
    }
    }


    clipboard->setText(tmpXml);

}


void Widget::on_copySS_clicked()
{
    notificationPopUp *notify = new notificationPopUp;
     notify->textOglav = "SS "+currentToolchain;
              notify->textNotify = "qss скопирован";
              notify->setN();
              notify->setOglav();
     notify->show();

QtDesignerSS ="";

    QClipboard *clipboard = QApplication::clipboard();
  //  QString originalText = clipboard->text();


    for(int i = 0; i < box->count(); i++){

        DynamicWidgetTool *wdt = qobject_cast<DynamicWidgetTool*>(box->itemAt(i)->widget());
        if(wdt->getID()==wdt_ID){

           QString snormal;
           QString shover;
           QString spressed;

            if(currentToolchain=="PUSH_BUTTON_TOOL"){
                snormal="QPushButton{\n";
            shover="QPushButton{\n";
         spressed="QPushButton::pressed{\n";

               for(int i=0; i<wdt->SSBuffer_nor.count(); i++){
                snormal+= wdt->SSBuffer_nor.at(i);
               }
               for(int i=0; i<wdt->SSBuffer_hover.count(); i++){
                shover+= wdt->SSBuffer_hover.at(i);
               }
               for(int i=0; i<wdt->SSBuffer_pressed.count(); i++){
                spressed+= wdt->SSBuffer_pressed.at(i);
               }
              QtDesignerSS+= snormal.append("\n}\n");
              QtDesignerSS+= shover.append("\n}\n");
              QtDesignerSS+= spressed.append("\n}\n");

            }else if (currentToolchain=="CHECK_BOX_TOOL"){



                     snormal="";
                 shover="";
              spressed="";

                    for(int i=0; i<wdt->SSBuffer_nor.count(); i++){
                     snormal+= wdt->SSBuffer_nor.at(i);
                    }
                    for(int i=0; i<wdt->SSBuffer_hover.count(); i++){
                     shover+= wdt->SSBuffer_hover.at(i);
                    }
                    //for(int i=0; i<wdt->SSBuffer_pressed.count(); i++){
                    // spressed+= wdt->SSBuffer_pressed.at(i);
                    //}
                   QtDesignerSS+= snormal;
                   QtDesignerSS+= shover;
                 //  QtDesignerSS+= spressed.append("\n}\n");
            }else if(currentToolchain=="LABEL_TOOL"){
                snormal="QLabel{\n";
            shover="QLabel::hover{\n";

               for(int i=0; i<wdt->SSBuffer_nor.count(); i++){
                snormal+= wdt->SSBuffer_nor.at(i);
               }
               for(int i=0; i<wdt->SSBuffer_hover.count(); i++){
                shover+= wdt->SSBuffer_hover.at(i);
               }

              QtDesignerSS+= snormal.append("\n}\n");
              QtDesignerSS+= shover.append("\n}\n");
             // QtDesignerSS+= spressed.append("\n}\n");
}

    }
    }
     clipboard->setText(QtDesignerSS);
    saveAs();
 }



void Widget::on_pushButton_3_clicked()
{
QPoint points(0,29);
    QMenu *menu = new QMenu(this);
 //   menu->setStyleSheet("")
    QIcon saveAs(":/images/save.png");
     QIcon home(":/images/redo.png");
      QIcon close(":/images/out.png");
    QAction * saveAsTab = new QAction(saveAs,"Сохранить как", this);
    QAction * homeTab = new QAction(home,"Главная", this);
    QAction * exitTab = new QAction(close, "Выход", this);
    exitTab->setShortcut(tr("alt+f4"));
     homeTab->setShortcut(tr("alt+A"));
      saveAsTab->setShortcut(tr("ctrl+S"));
   connect(exitTab, &QAction::triggered, this, &Widget::close);
      connect(homeTab, &QAction::triggered, this, &Widget::home);
         connect(saveAsTab, &QAction::triggered, this, &Widget::saveAs);
   // connect(saveTab, &QAction::triggered, this, &MainWindow::saveAsTabSlot);
    //connect(renameTab, &QAction::triggered, this, &MainWindow::renameTabSlot);
    menu->addAction(saveAsTab);
    menu->addAction(homeTab);
    menu->addAction(exitTab);
    menu->popup(ui->pushButton_3->mapToGlobal(points)); //ui->tabWidget->mapToGlobal(points)
}


void Widget::on_checkbox_b_clicked()
{

}

