#ifndef PANELROUND_H
#define PANELROUND_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <texteditlabel.h>
#include <QCheckBox>

class panelRound : public QWidget
{
    Q_OBJECT
public:
    explicit panelRound(QWidget *parent = nullptr);
    TextEditLabel *roundp = new TextEditLabel(this);
    QString getRound();
    void updateData();
    QCheckBox *enableRound = new QCheckBox(this);


signals:
    void onDataUpdate();
};

#endif // PANELROUND_H
