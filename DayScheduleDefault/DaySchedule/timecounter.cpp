#include "timecounter.h"

TimeCounter::TimeCounter(QWidget * parent) : QPushButton(parent)
{
    updateTimeText();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimeText()));
    timer->start(1000);
}

void TimeCounter::updateTimeText()
{
    QTime time = QTime::currentTime();
    QString time_text = time.toString("hh : mm");
    setText(time_text);
}
