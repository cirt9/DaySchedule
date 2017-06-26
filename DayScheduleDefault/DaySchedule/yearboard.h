#ifndef YEARBOARD_H
#define YEARBOARD_H

#include <boardtemplate.h>
#include <QGridLayout>
#include <QDate>
#include <QLocale>
#include <calendarcard.h>

class YearBoard : public BoardTemplate
{
    Q_OBJECT

private:
    static const int ROWS = 4;
    static const int COLUMNS = 3;

    void createMonthCardsLayout();

private slots:
    void updateCurrentlyUsedDateMonth(QString & monthValue);

public:
    explicit YearBoard(QSharedPointer<QDate> currUsedDate, QWidget * parent = nullptr);
    ~YearBoard() {;}
};

#endif // YEARBOARD_H
