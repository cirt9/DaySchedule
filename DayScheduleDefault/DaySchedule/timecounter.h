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

private slots:
    void updateTimeText();

public:
    explicit TimeCounter(QWidget * parent = nullptr);
    ~TimeCounter() {}
};

#endif // TIMECOUNTER_H
