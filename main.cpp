#include "widget.h"

#include <QApplication>
#include <main_screen.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
  //  Widget w("str");
  //  w.setStyleSheet(AllstyleSheet::getMainWidgetStyle()); //stylesheet на widget W  не ломает qscrollBar
  //  w.show();
    QCoreApplication::setApplicationName("StyleSheetStudio");
    QCoreApplication::setOrganizationName("Alexey-Tikhanov-DDUT-NA-LENSKOY");
     main_screen c;
     c.show();

    return a.exec();
}
