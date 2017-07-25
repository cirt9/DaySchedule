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
#include <QLocale>
#include <databasemanager.h>

class DayBoard : public BoardTemplate
{
    Q_OBJECT

private:
    QVBoxLayout * activitiesLayout;
    QList<Activity *> activities;
    QSharedPointer<TimeRangeSystem> timeSystem;

    QLabel * progress;
    QCheckBox * alarmsButton;

    void createDateAndProgressLayout();
    QString createHeaderDate();
    void createActivitiesLayout();
    void createScrollBar();
    void createBottomMenuLayout();

    Activity * createActivity();
    int calculateProgress();

    bool somethingChanged();
    int getProgress();

    void saveActivities();
    void loadActivities();

private slots:
    void addNewActivity();
    void clearActivities();
    void copyActivity();
    void eraseActivityFromList(QWidget * activity = nullptr);

public:
    explicit DayBoard(QSharedPointer<QDate> currUsedDate, QWidget * parent = nullptr);
    ~DayBoard() {;}

public slots:
    void updateProgress();

    void save();
    void load();
};

#endif // DAYBOARD_H
