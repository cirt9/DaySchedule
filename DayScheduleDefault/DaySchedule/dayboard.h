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
#include <dateselectingwidget.h>
#include <QMessageBox>

class DayBoard : public BoardTemplate
{
    Q_OBJECT

private:
    QVBoxLayout * activitiesLayout;
    QList<Activity *> activities;
    int currentActivityIndex;
    QSharedPointer<TimeRangeSystem> timeSystem;
    QGroupBox * footerButtonsBarContainer;
    bool defaultAlarmsEnabledState;

    QLabel * progress;
    QCheckBox * alarmsButton;

    void createDateAndProgressLayout();
    QString createHeaderDate();
    void createActivitiesLayout();
    void createScrollBar();
    void createBottomMenuLayout();

    Activity * createActivity();
    void assignActivitesToCurrentlyUsedDate();
    void clearAllActivities();
    int calculateProgress();

    void deleteCopyDateSelectingWidget();
    bool somethingChanged();
    bool defaultValuesChanged();
    int getProgress();

    void saveActivities();
    void loadActivities();

    int findCurrentActivityIndex();
    void setCurrentActivityIndex(int index);

private slots:
    void addNewActivity();
    void clearInactiveActivities();
    void selectDateToCopyActivity();
    void copyingConfirmed(QDate selectedDate);
    void copyingCanceled();
    void eraseActivityFromList(QWidget * activity = nullptr);

public:
    explicit DayBoard(QSharedPointer<QDate> currUsedDate, bool alarmsEnabled, QWidget * parent = nullptr);
    ~DayBoard() {;}

public slots:
    void updateProgress();

    void save();
    void load();
    void updateCurrentActivity();

signals:
    void currentActivityChanged(QTime fromTime, QTime toTime, QString description);
};

#endif // DAYBOARD_H
