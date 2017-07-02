#include "bar.h"

Bar::Bar(QWidget * parent) : QGroupBox(parent)
{
    barHeight = 40;
    barWidgetsWidth = 110;

    barLayout = new QHBoxLayout();
    barLayout->setSpacing(0);
    barLayout->setContentsMargins(0, 0, 0, 0);

    setLayout(barLayout);
}

void Bar::setBarHeight(int height)
{
    barHeight = height;
}

void Bar::setBarWidgetsWidth(int width)
{
    barWidgetsWidth = width;
}

void Bar::addWidget(QWidget * widget)
{
    widget->setFixedHeight(barHeight);
    widget->setFixedWidth(barWidgetsWidth);

    barLayout->addWidget(widget);
}
