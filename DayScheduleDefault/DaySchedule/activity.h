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

class Activity : public QGroupBox
{
    Q_OBJECT

private:
    static const int FIXEDHEIGHTACTIVATED = 170;
    static const int FIXEDHEIGHTSTARTEND = 130;
    ActivityState state;
    QSharedPointer<TimeRangeSystem> timeSystem;

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

private slots:
    void deleteActivity();
    void startActivity();
    void failed();
    void succeeded();

public:
    explicit Activity(QSharedPointer<TimeRangeSystem> tSystem, QWidget * parent = nullptr);
    ~Activity() {}

    QString getState() const;

signals:
    void activityDeleted(QWidget * = nullptr);
    void activityStarted();
    void success();
    void fail();
};

#endif // ACTIVITY_H
