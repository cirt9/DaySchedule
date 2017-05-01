#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <mainmenubutton.h>

class MainMenu : public QWidget
{
    Q_OBJECT
private:
    void paintEvent(QPaintEvent *);

public:
    explicit MainMenu(QWidget * parent = 0);

signals:

public slots:
};

#endif // MAINMENU_H
