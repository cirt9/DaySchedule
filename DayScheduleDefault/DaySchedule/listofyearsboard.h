#ifndef LISTOFYEARSBOARD_H
#define LISTOFYEARSBOARD_H

#include <boardtemplate.h>
#include <QGridLayout>
#include <QPushButton>
#include <calendarcard.h>

class ListOfYearsBoard : public BoardTemplate
{
    Q_OBJECT

private:
    static const int ROWS = 11;
    static const int COLUMNS = 7;

    void createYearsCardsLayout();

    bool somethingChanged();

private slots:
    void updateCurrentlyUsedDateYear(QString & yearValue);

public:
    explicit ListOfYearsBoard(QString headerText, QString footerText,
                              QSharedPointer<QDate> currUsedDate, QWidget * parent = nullptr);
    ~ListOfYearsBoard() {;}

public slots:
    void save();
    void load();
};

#endif // LISTOFYEARSBOARD_H
