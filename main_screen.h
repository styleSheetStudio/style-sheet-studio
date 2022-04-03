#ifndef MAIN_SCREEN_H
#define MAIN_SCREEN_H

#include <QWidget>
#include <widget.h>
#include <QStringListModel>
#include <QSettings>

namespace Ui {
class main_screen;
}

class main_screen : public QWidget
{
    Q_OBJECT

public:
    explicit main_screen(QWidget *parent = nullptr);
    ~main_screen();
   QStringList projectsList;
    void saveSettings();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

private:
    Ui::main_screen *ui;
       QStringList listP;
          QStringListModel *model = new QStringListModel;
          QString path = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
};

#endif // MAIN_SCREEN_H
