#include "bar.h"

Bar::Bar(QWidget * parent) : QGroupBox(parent)
{
    barHeight = 40;

    barLayout = new QHBoxLayout();
    barLayout->setSpacing(0);
    barLayout->setContentsMargins(0, 0, 0, 0);

    setLayout(barLayout);
}

void Bar::setBarHeight(int height)
{
    barHeight = height;
}

void Bar::addWidget(QWidget * widget)
{
    widget->setFixedHeight(barHeight);

    barLayout->addWidget(widget);
}
