#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <QGroupBox>
#include <QLabel>
#include <QTimeEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

class Activity : public QGroupBox
{
    Q_OBJECT

private:
    QTimeEdit * fromTime;
    QTimeEdit * toTime;
    QLineEdit * description;

    QHBoxLayout * createTimeRangeLayout();
    QHBoxLayout * createIconsLayout();
    QHBoxLayout * createDescriptionLayout();
    QHBoxLayout * createSummaryLayout();

public:
    explicit Activity(QWidget * parent = nullptr);
    ~Activity() {}
};

#endif // ACTIVITY_H
