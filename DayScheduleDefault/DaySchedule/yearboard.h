#ifndef YEARBOARD_H
#define YEARBOARD_H

#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QDate>
#include <QLocale>
#include <QList>

class YearBoard : public QGroupBox
{
    Q_OBJECT

private:
    static const int ROWS = 4;
    static const int COLUMNS = 3;

    QVBoxLayout * yearBoardLayout;

    void createHeaderLayout();

    void createMonthCardsLayout();
    void roundEdgesOfTheCornerCards(QGridLayout * cardsLayout);

    void createFooterLayout();

public:
    explicit YearBoard(QWidget * parent = nullptr);
    ~YearBoard() {;}
};

#endif // YEARBOARD_H
