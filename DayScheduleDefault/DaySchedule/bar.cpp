#include "bar.h"

Bar::Bar(QWidget * parent) : QGroupBox(parent)
{
    barHeight = 40;
    barWidgetsWidth = 90;

    barLayout = new QHBoxLayout();
    barLayout->setSpacing(0);
    barLayout->setContentsMargins(0, 0, 0, 0);

    setLayout(barLayout);
}

void Bar::setBarHeight(int height)
{
    barHeight = height;
}

void Bar::setBarWidgetsMinimumWidth(int width)
{
    barWidgetsWidth = width;
}

void Bar::addWidget(QWidget * widget)
{
    widget->setFixedHeight(barHeight);
    widget->setMinimumWidth(barWidgetsWidth);

    barLayout->addWidget(widget);
}
