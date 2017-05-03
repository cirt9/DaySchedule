#include "mainmenubutton.h"

#include <QtCore/qmath.h>
#include <QDebug>

MainMenuButton::MainMenuButton(int width, int height, QWidget * parent) : QWidget(parent)
{
    buttonWidth = width;
    buttonHeight = height;

    setGeometry(0, 0, buttonWidth+6, buttonHeight+6);
}

void MainMenuButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setPen(QPen(QColor(0,58,70), 3, Qt::SolidLine, Qt::RoundCap));

    QRect rect(3, 3, buttonWidth, buttonHeight);
    painter.drawRect(rect);
    painter.fillRect(rect, QBrush(QColor(36,92,81)));
}

void MainMenuButton::mousePressEvent(QMouseEvent *)
{
    qDebug() << "pressed";
}
