#include "timecounter.h"

TimeCounter::TimeCounter(QWidget * parent) : QPushButton(parent)
{
    countdownTime = QTime(0, 0, 0);

    oneSecTimer = new QTimer(this);
    connect(oneSecTimer, SIGNAL(timeout()), this, SLOT(showCurrentTime()));
    oneSecTimer->start(1000);

    countdownTimer = new QTimer(this);
    connect(countdownTimer, SIGNAL(timeout()), this, SLOT(updateCountdownTime()));

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
    if(countdownTime > QTime(0, 0))
        countdownTime = countdownTime.addSecs(-1);
    else
    {
        countdownTimer->stop();
        emit countdownCompleted();
    }
}

void TimeCounter::enterEvent(QEvent * e)
{
    disconnect(oneSecTimer, SIGNAL(timeout()), this, SLOT(showCurrentTime()));

    showCountdownTime();
    connect(oneSecTimer, SIGNAL(timeout()), this, SLOT(showCountdownTime()));

    QWidget::enterEvent(e);
}

void TimeCounter::leaveEvent(QEvent * e)
{
    disconnect(oneSecTimer, SIGNAL(timeout()), this, SLOT(showCountdownTime()));

    showCurrentTime();
    connect(oneSecTimer, SIGNAL(timeout()), this, SLOT(showCurrentTime()));

    QWidget::enterEvent(e);
}

void TimeCounter::setCountdownTime(QTime time)
{
    countdownTime = time;
    countdownTime = countdownTime.addMSecs(-countdownTime.msec());
    countdownTimer->start(1000);
}
