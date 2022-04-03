#ifndef GRADIENTPICKER_H
#define GRADIENTPICKER_H

#include <colorpicker.h>
#include <QWidget>
#include <allstylesheet.h>
#include <marker.h>
#include <defines.h>
#include <QListWidgetItem>
#include <QPainter>
#include <QColorDialog>
#include <QTimer>
#include <threadwhile.h>
#include <QVector>

namespace Ui {
class GradientPicker;
}

class GradientPicker : public QDialog
{
    Q_OBJECT

public:
    explicit GradientPicker(QWidget *parent = nullptr);
    ~GradientPicker();
        QString bufferQSS;
private:
    int Mcur =0;
 double tmpY;

    void showData();
    posList listl;
    QStringList listc;
//QStringList listpos;

QTimer *posT;
private slots:


    void markerNewColor(QColor color);

    void on_comboBox_currentIndexChanged(int index);

    void on_plus_marker_clicked();

    void on_st_clicked();

    void on_end_clicked();

    void on_minus_marker_clicked();


    void posUpdate();



    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);



    void on_dial_valueChanged(int value);

    void on_mrk1_clicked();

    void on_mrk2_clicked();


private:
    Ui::GradientPicker *ui;
    colorPicker *pick1;
    bool Gcurrent = false;
 QTimer *interval;
    int index =0; //индекс всего кол-во маркеров и номер последнего
    QString color; //цветовая часть градиента составная
    QString pos; //часть позиции маркеров


QColor colorDlg;
QString mrk1_color;
QString mrk2_color;
  //  Gmarkers Markers;


    void Liner();

     QVector <Marker*> MarkersVector;



     bool value = false;
     bool valuez = false;
     int color_index = 1;

     void color_chnager();

     void updateSS();
    void list();
     void addMarker();
private slots:
   // void slotGetNumber();
 void color_index_change();
 void out();
     void loadData();
     void on_dialLine_textChanged(const QString &arg1);

     void on_buttonBox_accepted();

     void on_buttonBox_rejected();
private slots:
     void onchange();
signals:
 void changeGradient();

};

#endif // GRADIENTPICKER_H
