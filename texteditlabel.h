#ifndef TEXTEDITLABEL_H
#define TEXTEDITLABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QLineEdit>
#include <QLabel>
#include <colorpicker.h>
class QWidget;
class QLineEdit;

class TextEditLabel : public QLabel
{
    Q_OBJECT
public:
    TextEditLabel(QWidget *parent=nullptr);
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void setEdit(QLineEdit *edit);
    QLabel *name;

QLineEdit *edit;


private:
    int lastX;
    int value = 10;
    bool start = false;



protected:

};

#endif // TEXTEDITLABEL_H
