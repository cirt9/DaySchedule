#ifndef TIMECOUNTER_H
#define TIMECOUNTER_H

#include <QPushButton>
#include <QTimer>
#include <QTime>

class TimeCounter : public QPushButton
{
    Q_OBJECT

private:
    QTimer * timer;
    QTime countdownTime;

    void enterEvent(QEvent * e);
    void leaveEvent(QEvent * e);

private slots:
    void showCurrentTime();
    void showCountdownTime();
    void updateCountdownTime();

public:
    explicit TimeCounter(QWidget * parent = nullptr);
    ~TimeCounter() {}

public slots:
    void setCountdownTime(QTime time);

signals:
    void countdownCompleted();
};

#endif // TIMECOUNTER_H
