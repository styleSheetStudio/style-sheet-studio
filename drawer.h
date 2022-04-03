#ifndef DRAWER_H
#define DRAWER_H

#include <QWidget>

namespace Ui {
class drawer;
}

class drawer : public QWidget
{
    Q_OBJECT

public:
    explicit drawer(QWidget *parent = nullptr);
    ~drawer();

private:
    Ui::drawer *ui;
};

#endif // DRAWER_H
