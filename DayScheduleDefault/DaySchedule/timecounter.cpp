#include "timecounter.h"

TimeCounter::TimeCounter(QWidget * parent) : QPushButton(parent)
{
    countdownTime = QTime(0, 0, 0);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateCountdownTime()));
    connect(timer, SIGNAL(timeout()), this, SLOT(showCurrentTime()));
    timer->start(1000);

    showCurrentTime();
}

void TimeCounter::showCurrentTime()
{
    QTime time = QTime::currentTime();
    QString timeText = time.toString("hh : mm");
    setText(timeText);
}

void TimeCounter::showCountdownTime()
{
    QString timeText = countdownTime.toString("hh : mm : ss");
    setText(timeText);
}

void TimeCounter::updateCountdownTime()
{
    if(countdownTime > QTime(0, 0, 0))
        countdownTime = countdownTime.addSecs(-1);
}

void TimeCounter::enterEvent(QEvent * e)
{
    disconnect(timer, SIGNAL(timeout()), this, SLOT(showCurrentTime()));

    showCountdownTime();
    connect(timer, SIGNAL(timeout()), this, SLOT(showCountdownTime()));

    QWidget::enterEvent(e);
}

void TimeCounter::leaveEvent(QEvent *e)
{
    disconnect(timer, SIGNAL(timeout()), this, SLOT(showCountdownTime()));

    showCurrentTime();
    connect(timer, SIGNAL(timeout()), this, SLOT(showCurrentTime()));

    QWidget::enterEvent(e);
}

void TimeCounter::setCountdownTime(QTime time)
{
    countdownTime = time;
}
