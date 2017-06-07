#ifndef MONTHBOARD_H
#define MONTHBOARD_H


#include <QGroupBox>

class MonthBoard : public QGroupBox
{
    Q_OBJECT

public:
    explicit MonthBoard(QWidget * parent = nullptr);
    ~MonthBoard() {;}
};

#endif // MONTHBOARD_H
