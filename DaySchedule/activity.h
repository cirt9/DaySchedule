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
    QTimeEdit * fromTime;
    QTimeEdit * toTime;
    QLineEdit * description;

    QHBoxLayout * createTimeRangeLayout();
    QHBoxLayout * createControlButtonsLayout();
    QHBoxLayout * createDescriptionLayout();
    QHBoxLayout * createSummaryLayout();

private slots:
    void deleteActivity();

public:
    explicit Activity(QWidget * parent = nullptr);
    ~Activity() {}

signals:
    activityDeleted(QWidget * = nullptr);
};

#endif // ACTIVITY_H
