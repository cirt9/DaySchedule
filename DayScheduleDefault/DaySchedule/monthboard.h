#ifndef MONTHBOARD_H
#define MONTHBOARD_H

#include <boardtemplate.h>
#include <QGridLayout>
#include <QLabel>
#include <QDate>
#include <QLocale>
#include <QPushButton>

class MonthBoard : public BoardTemplate
{
    Q_OBJECT

private:
    static const int MAX_ROW_SIZE = 7;
    int maxNumberOfCards;

    QDate date;

    void createDayCardsLayout();
    void createDaysNames(QGridLayout * cardsLayout);

    void createBlankCardsOnTheFront(int & row, int & column, QGridLayout * cardsLayout);
    void createDayCards(int & row, int & column, QGridLayout * cardsLayout);
    void createBlankCardsOnTheEnd(int & row, int & column, QGridLayout * cardsLayout);

public:
    explicit MonthBoard(QWidget * parent = nullptr);
    ~MonthBoard() {;}
};

#endif // MONTHBOARD_H
