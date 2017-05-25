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

class Activity : public QGroupBox
{
    Q_OBJECT

private:
    static const int fixedHeightActivated = 170;
    static const int fixedHeightStartEnd = 130;

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

    void clearSummaryLayout();

private slots:
    void deleteActivity();
    void startActivity();
    void failed();
    void succeeded();

public:
    explicit Activity(QWidget * parent = nullptr);
    ~Activity() {}

signals:
    void activityDeleted(QWidget * = nullptr);
    void activityStarted();
    void success();
    void fail();
};

#endif // ACTIVITY_H
