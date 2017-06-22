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

public:
    explicit ListOfYearsBoard(QWidget * parent = nullptr);
    ~ListOfYearsBoard() {;}
};

#endif // LISTOFYEARSBOARD_H
