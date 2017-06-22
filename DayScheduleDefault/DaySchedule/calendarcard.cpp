#include "calendarcard.h"

CalendarCard::CalendarCard(QString cardText, QWidget * parent) : QPushButton(parent)
{
    text = cardText;

    setText(text);
}

void CalendarCard::mousePressEvent(QMouseEvent * e)
{
    QPushButton::mousePressEvent(e);
    emit cardClicked(text);
}
