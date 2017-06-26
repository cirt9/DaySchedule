#ifndef DAYBOARD_H
#define DAYBOARD_H

#include <boardtemplate.h>
#include <activity.h>
#include <QList>
#include <QPushButton>
#include <QScrollArea>
#include <QCheckBox>
#include <layoutdeleter.h>
#include <timerangesystem.h>
#include <QSharedPointer>

class DayBoard : public BoardTemplate
{
    Q_OBJECT

private:
    QVBoxLayout * activitiesLayout;
    QList<Activity *> activities;
    QSharedPointer<TimeRangeSystem> timeSystem;
    bool alarmsEnabled;

    QLabel * progress;

    void createDateAndProgressLayout();
    void createActivitiesLayout();
    void createScrollBar();
    void createBottomMenuLayout();

    int calculateProgress();

private slots:
    void addNewActivity();
    void clearActivities();
    void setAlarmsState(bool state);
    void eraseActivityFromList(QWidget * activity = nullptr);

public:
    explicit DayBoard(QSharedPointer<QDate> currUsedDate, QWidget * parent = nullptr);
    ~DayBoard() {;}

    bool getAlarmsEnabled() const;
    void setAlarmsEnabled(bool value);

public slots:
    void updateProgress();
};

#endif // DAYBOARD_H
