#ifndef DAYBOARD_H
#define DAYBOARD_H

#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

class DayBoard : public QGroupBox
{
    Q_OBJECT

private:
    QVBoxLayout * dayBoardLayout;
    size_t numberOfLayoutsInMainLayout;

    void makeDateAndProgressLayout();
    void makeBottomIconsLayout();

private slots:
    void addNewActivityLayout();

public:
    explicit DayBoard(QWidget * parent = 0);
};

#endif // DAYBOARD_H
