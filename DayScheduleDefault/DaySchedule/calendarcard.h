#ifndef CALENDARCARD_H
#define CALENDARCARD_H

#include <QPushButton>

class CalendarCard : public QPushButton
{
    Q_OBJECT

private:
    QString text;

    void mousePressEvent(QMouseEvent * e = nullptr);

public:
    CalendarCard(QString cardText, QWidget * parent = nullptr);
    ~CalendarCard() {;}

signals:
    void cardClicked(QString & cardText);
};

#endif // CALENDARCARD_H
