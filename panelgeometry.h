#ifndef PANELGEOMETRY_H
#define PANELGEOMETRY_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <texteditlabel.h>
class panelGeometry : public QWidget
{
    Q_OBJECT
public:
    explicit panelGeometry(QWidget *parent = nullptr);
    TextEditLabel *widthEdit = new TextEditLabel(this);
    TextEditLabel *heightEdit = new TextEditLabel(this);
    void updateData();
signals:
  void onDataUpdate();
};

#endif // PANELGEOMETRY_H
