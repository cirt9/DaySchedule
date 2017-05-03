#include "mainmenu.h"

#include <QGridLayout>
#include <QSpacerItem>
#include <QDebug>

MainMenu::MainMenu(QWidget * parent) : QWidget(parent)
{
    setGeometry(0, 0, 150+3+30+3, 30+3+150+3);
    QWidget * test = new QWidget(this);

    button1 = new MainMenuButton(150, 30, test);
    button2 = new MainMenuButton(30, 150, test);
    button3 = new MainMenuButton(150, 30, test);
    button4 = new MainMenuButton(30, 150, test);
    button5 = new MainMenuButton(118, 118, test);
}

void MainMenu::paintEvent(QPaintEvent *)
{
    QPainter backgroundPainter(this);

    QBrush background(QColor(23, 23, 34));

    backgroundPainter.setBrush(background);
    backgroundPainter.setPen(Qt::NoPen );

    backgroundPainter.drawRect(0, 0, width(), height());
}

void MainMenu::resizeEvent(QResizeEvent *)
{
    int dx = this->width()/2 - 90;
    int dy = this->height()/2 - 90;

    button1->move(0+dx,0+dy);
    button2->move(0+dx, 32+dy);
    button3->move(32+dx, 152+dy);
    button4->move(152+dx, 0+dy);
    button5->move(32+dx, 32+dy);
}
