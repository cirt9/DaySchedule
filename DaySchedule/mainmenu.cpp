#include "mainmenu.h"

#include <QGridLayout>

MainMenu::MainMenu(QWidget * parent) : QWidget(parent)
{
    QGridLayout * layout = new QGridLayout(this);

    MainMenuButton * button1 = new MainMenuButton(200, 50, -45, this);
    MainMenuButton * button2 = new MainMenuButton(200, 50, 225, this);
    MainMenuButton * button3 = new MainMenuButton(200, 50, 45, this);
    MainMenuButton * button4 = new MainMenuButton(200, 50, -225, this);

    layout->addWidget(button1, 0, 0);
    layout->addWidget(button2, 1, 0);
    layout->addWidget(button3, 0, 1);
    layout->addWidget(button4, 1, 1);
}

void MainMenu::paintEvent(QPaintEvent *)
{
    QPainter backgroundPainter(this);

    QBrush background(Qt::yellow);//QColor(23, 23, 34));

    backgroundPainter.setBrush(background);
    backgroundPainter.setPen(Qt::NoPen );

    backgroundPainter.drawRect(0, 0, width(), height());
}
