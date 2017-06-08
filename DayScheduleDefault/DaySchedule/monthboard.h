#ifndef MONTHBOARD_H
#define MONTHBOARD_H


#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>

class MonthBoard : public QGroupBox
{
    Q_OBJECT

private:
    QVBoxLayout * monthBoardLayout;

    void createHeaderLayout();
    void createDayCardsLayout();
    void createFooterLayout();

public:
    explicit MonthBoard(QWidget * parent = nullptr);
    ~MonthBoard() {;}
};

#endif // MONTHBOARD_H
