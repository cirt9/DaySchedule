#ifndef YEARBOARD_H
#define YEARBOARD_H

#include <boardtemplate.h>
#include <QGridLayout>
#include <QPushButton>
#include <QDate>
#include <QLocale>

class YearBoard : public BoardTemplate
{
    Q_OBJECT

private:
    static const int ROWS = 4;
    static const int COLUMNS = 3;

    void createMonthCardsLayout();

public:
    explicit YearBoard(QWidget * parent = nullptr);
    ~YearBoard() {;}
};

#endif // YEARBOARD_H
