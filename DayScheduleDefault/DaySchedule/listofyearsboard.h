#ifndef LISTOFYEARSBOARD_H
#define LISTOFYEARSBOARD_H

#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

class ListOfYearsBoard : public QGroupBox
{
    Q_OBJECT

private:
    static const int ROWS = 11;
    static const int COLUMNS = 7;

    QVBoxLayout * yearsBoardLayout;

    void createHeaderLayout();

    void createYearsCardsLayout();
    void roundEdgesOfTheCornerCards(QGridLayout * cardsLayout);

    void createFooterLayout();

public:
    explicit ListOfYearsBoard(QWidget * parent = nullptr);
    ~ListOfYearsBoard() {;}
};

#endif // LISTOFYEARSBOARD_H
