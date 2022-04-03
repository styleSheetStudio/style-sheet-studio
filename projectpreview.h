#ifndef PROJECTPREVIEW_H
#define PROJECTPREVIEW_H

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

class projectPreview : public QWidget
{
    Q_OBJECT
public:
    explicit projectPreview(QWidget *parent = nullptr);


signals:
protected:
        void paintEvent(QPaintEvent *);

};

#endif // PROJECTPREVIEW_H
