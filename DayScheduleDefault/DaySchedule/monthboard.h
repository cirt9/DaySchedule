#ifndef MONTHBOARD_H
#define MONTHBOARD_H


#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QDate>
#include <QLocale>
#include <QList>
#include <QPushButton>

class MonthBoard : public QGroupBox
{
    Q_OBJECT

private:
    static const int MAX_NUMBER_OF_CARDS = 42;
    static const int MAX_ROW_SIZE = 7;

    QVBoxLayout * monthBoardLayout;
    QDate date;

    void createHeaderLayout();

    void createDayCardsLayout();
    void createDaysNames(QGridLayout * cardsLayout);

    void createBlankCardsOnTheFront(int & row, int & column, QGridLayout * cardsLayout);
    void createDayCards(int & row, int & column, QGridLayout * cardsLayout);
    void createBlankCardsOnTheEnd(int & row, int & column, QGridLayout * cardsLayout);
    void roundEdgesOfTheCornerCards(QGridLayout * cardsLayout);

    void createFooterLayout();

public:
    explicit MonthBoard(QWidget * parent = nullptr);
    ~MonthBoard() {;}
};

#endif // MONTHBOARD_H
