#ifndef MONTHBOARD_H
#define MONTHBOARD_H

#include <boardtemplate.h>
#include <QGridLayout>
#include <QLabel>
#include <QDate>
#include <QLocale>
#include <calendarcard.h>

class MonthBoard : public BoardTemplate
{
    Q_OBJECT

private:
    static const int MAX_ROW_SIZE = 7;
    int maxNumberOfCards;
    QString defaultFooterDescription;

    QString createHeaderDate();

    void createDayCardsLayout();
    void createDaysNames(QGridLayout * cardsLayout);

    void createBlankCardsOnTheFront(int & row, int & column, QGridLayout * cardsLayout);
    void createDayCards(int & row, int & column, QGridLayout * cardsLayout);
    void createBlankCardsOnTheEnd(int & row, int & column, QGridLayout * cardsLayout);

    int calculateFirstDayOfTheMonthValue();

    bool somethingChanged();

private slots:
    void updateCurrentlyUsedDateDay(QString & dayValue);

public:
    explicit MonthBoard(QString footerText, QSharedPointer<QDate> currUsedDate, QWidget * parent = nullptr);
    ~MonthBoard() {;}

public slots:
    void save();
    void load();
};

#endif // MONTHBOARD_H
