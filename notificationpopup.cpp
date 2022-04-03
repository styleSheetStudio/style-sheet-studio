#include "notificationpopup.h"
#include "ui_notificationpopup.h"
#include "QMovie"
#include "QLabel"
#include <QPainter>
#include <QApplication>
#include <QDesktopWidget>
#include <QTimer>

notificationPopUp::notificationPopUp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::notificationPopUp)
{
    ui->setupUi(this);

    ui->label_2->setText(textOglav);
      ui->label->setText(textNotify);
    setWindowFlags(Qt::FramelessWindowHint |        // Отключаем оформление окна
                      Qt::Tool |                       // Отменяем показ в качестве отдельного окна
                      Qt::WindowStaysOnTopHint);       // Устанавливаем поверх всех окон
    //   setAttribute(Qt::WA_TranslucentBackground);     // Указываем, что фон будет прозрачным
       setAttribute(Qt::WA_ShowWithoutActivating);

       this->setGeometry(QApplication::desktop()->availableGeometry().width() - 36 - width() + QApplication::desktop() -> availableGeometry().x(),
                   QApplication::desktop()->availableGeometry().height() - 36 - height() + QApplication::desktop() -> availableGeometry().y(),
                 width(),
                   height());


 movie = new QMovie(":/icons/images/copyanim.gif");

    ui->animation->setMovie(movie);
    QSize size;
    size.setHeight(71);
    size.setWidth(71);
       movie->setScaledSize(size);
       movie->start();
       QTimer * movietime;
       movietime = new QTimer();
         QTimer * close;
             close = new QTimer();

                  close->start(3450); // И запустим таймер
                    movietime->start(2450); // И запустим таймер
          connect(movietime, SIGNAL(timeout()), this, SLOT(stop()));

             connect(close, SIGNAL(timeout()), this, SLOT(closen()));








    //movie->start();
    //connect (movie,&QMovie::,this,&notificationPopUp::stop);

   // setWindowOpacity(0.0);  // Устанавливаем прозрачность в ноль

      //  animation.setDuration(150);     // Настраиваем длительность анимации
      //  animation.setStartValue(0.0);   // Стартовое значение будет 0 (полностью прозрачный виджет)
      //  animation.setEndValue(1.0);     // Конечное - полностью непрозрачный виджет


       // QWidget::show();                // Отображаем виджет, который полностью прозрачен

      //  animation.start();

}

notificationPopUp::~notificationPopUp()
{
    delete ui;
}

void notificationPopUp::setOglav()
{
    ui->label_2->setText(textOglav);
}

void notificationPopUp::setN()
{
 ui->label->setText(textNotify);
}

void notificationPopUp::stop()
{
   // this->close();
    movie->stop();
}

void notificationPopUp::closen()
{
 this->close();
}
