#include "mainmenubutton.h"

MainMenuButton::MainMenuButton(int width, int height, int tAngle, QWidget * parent) : QWidget(parent)
{
    buttonWidth = width;
    buttonHeight = height;
    tiltAngle = tAngle;
    //setGeometry(0, 0, 300, 300);
}

void MainMenuButton::paintEvent(QPaintEvent *)
{
    QRect rect(0, 0, buttonWidth, buttonHeight);
    QPainter painter(this);

    QBrush color(QColor(23, 23, 34));

    painter.setBrush(color);
    painter.setPen(Qt::NoPen);

    painter.translate(buttonWidth, buttonWidth);
    painter.rotate(tiltAngle);
    painter.translate(-rect.width()/2,-rect.height()/2);
    //painter.fillRect(rect, Qt::blue);
    painter.drawRect(rect);
}
