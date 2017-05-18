#ifndef DAYBOARD_H
#define DAYBOARD_H

#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <activity.h>
#include <QList>
#include <QPushButton>

class DayBoard : public QGroupBox
{
    Q_OBJECT

private:
    QVBoxLayout * dayBoardLayout;
    QVBoxLayout * activitiesLayout;
    QList <Activity *> activities;

    void makeDateAndProgressLayout();
    void makeBottomIconsLayout();
    void makeScrollBar();

private slots:
    void addNewActivity();

public:
    explicit DayBoard(QWidget * parent = nullptr);
    ~DayBoard() {}
};

#endif // DAYBOARD_H
