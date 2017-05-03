#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QPainter>
#include <mainmenubutton.h>

class MainMenu : public QWidget
{
    Q_OBJECT
private:
    MainMenuButton * button1;
    MainMenuButton * button2;
    MainMenuButton * button3;
    MainMenuButton * button4;
    MainMenuButton * button5;

public:
    explicit MainMenu(QWidget * parent = 0);

    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);
};

#endif // MAINMENU_H
