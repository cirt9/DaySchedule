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

    int convertMonthNameToMonthValue(QString & name);

private slots:
    void updateCurrentlyUsedDateMonth(QString & monthName);

public:
    explicit YearBoard(QString footerText, QSharedPointer<QDate> currUsedDate, QWidget * parent = nullptr);
    ~YearBoard() {;}

signals:
    void errorDetected(QString errorText);
};

#endif // YEARBOARD_H
