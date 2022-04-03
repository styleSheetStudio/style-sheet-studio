#ifndef NOTIFICATIONPOPUP_H
#define NOTIFICATIONPOPUP_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QMovie>

namespace Ui {
class notificationPopUp;
}

class notificationPopUp : public QWidget
{
    Q_OBJECT

public:
    explicit notificationPopUp(QWidget *parent = nullptr);
    ~notificationPopUp();
QString textOglav;
QString textNotify;
void setOglav();
void setN();
private:
    Ui::notificationPopUp *ui;
    // QPropertyAnimation animation;
     QMovie *movie;
private slots:
    void stop();
    void closen();
};

#endif // NOTIFICATIONPOPUP_H
