#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <QGroupBox>
#include <QLabel>
#include <QTimeEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <layoutdeleter.h>
#include <activitystate.h>
#include <QMessageBox>
#include <timerangesystem.h>
#include <QSharedPointer>
#include <databasemanager.h>
#include <QDate>

class Activity : public QGroupBox
{
    Q_OBJECT

private:
    static const int FIXED_HEIGHT_ACTIVATED = 170;
    static const int FIXED_HEIGHT_START_END = 130;
    ActivityState state;
    QSharedPointer<TimeRangeSystem> timeSystem;
    QDate assignedDay;

    QVBoxLayout * activityLayout;
    QHBoxLayout * summaryLayout;

    QTimeEdit * fromTime;
    QTimeEdit * toTime;
    QLabel * descriptionLabel;
    QLineEdit * description;
    QPushButton * readyButton;
    QPushButton * deleteButton;

    QHBoxLayout * createTimeRangeLayout();
    QHBoxLayout * createControlButtonsLayout();
    QHBoxLayout * createDescriptionLayout();
    QHBoxLayout * createSummaryLayout();

    bool getConfirmationOfActiveActivityDeletion();
    void checkCorrectnessOfInput();

    void clearSummaryLayout();

    bool stateChanged();
    void deleteActivityFromDatabase();

private slots:
    void deleteActivity();
    void startActivity();
    void failed();
    void succeeded();

public:
    explicit Activity(QSharedPointer<TimeRangeSystem> tSystem, QDate date, QWidget * parent = nullptr);
    ~Activity() {}

    QString getState() const;
    void setAssignedDay(QDate day);
    QTime getFromTime() const;
    QTime getToTime() const;

    void save();
    void load(const QTime & fromT, const QTime & toT);

signals:
    void activityDeleted(QWidget * = nullptr);
    void activityStarted();
    void success();
    void fail();
};

#endif // ACTIVITY_H
