#ifndef DEFINES_H
#define DEFINES_H
#include <QString>
#include <QVector>
#include <iostream>
/* Перечисление Tools используется для
 * указания выбранного инструмента (слева).
 */


struct Gmarker{
    QString  pos_x;
    QString color_string;

};


enum Tools{
    PUSH_BUTTON_TOOL,
    CHECK_BOX_TOOL,
    LABEL_TOOL,
    COMBO_BOX_TOOL,
    LINE_EDIT_TOOL,
    TEXT_EDIT_TOOL,
    RADIO_BUTTON_TOOL,
    SPIN_BOX_TOOL,
    TAB_WIDGET_TOOL,
    LIST_WIDGET_TOOL,

    SETTINGS_BUTTON_TOOL
};

enum TitleBtnCur{
    GEOMETRY,
    LABEL,
};
const int MY_CONST = 1;
/* Перечисление PanelTypes используется для
 * указания типа панели. Например, PANEL_GEOMETRY указывает,
 * что тип панели содержит поля формы для редактирования ширины и высоты.
 */
enum PanelTypes{
    PANEL_GEOMETRY,
    PANEL_TEXT,
    PANEL_MAGRINGS,
    PANEL_BACKGROUND,
    PANEL_ICON,
    PANEL_ROUND,
};

typedef QStringList posList;
typedef QVector<Gmarker>Markers;


#endif // DEFINES_H
