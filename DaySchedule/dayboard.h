#ifndef DAYBOARD_H
#define DAYBOARD_H

#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <activity.h>
#include <QList>
#include <QPushButton>
#include <QScrollArea>
#include <QCheckBox>
#include <layoutdeleter.h>

class DayBoard : public QGroupBox
{
    Q_OBJECT

private:
    QVBoxLayout * dayBoardLayout;
    QVBoxLayout * activitiesLayout;
    QList <Activity *> activities;
    bool alarmsEnabled;

    void createDateAndProgressLayout();
    void createActivitiesLayout();
    void createActivitiesTitle();
    void createScrollBar();
    void createBottomMenuLayout();

private slots:
    void addNewActivity();
    void deleteAllActivities();
    void setAlarmsState(bool state);
    void eraseActivityFromList(QWidget * activity = nullptr);

public:
    explicit DayBoard(QWidget * parent = nullptr);
    ~DayBoard() {}

    bool getAlarmsEnabled() const;
    void setAlarmsEnabled(bool value);
};

#endif // DAYBOARD_H
