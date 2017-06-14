#ifndef YEARBOARD_H
#define YEARBOARD_H

#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

class YearBoard : public QGroupBox
{
    Q_OBJECT

private:
    QVBoxLayout * yearBoardLayout;

public:
    explicit YearBoard(QWidget * parent = nullptr);
    ~YearBoard() {;}
};

#endif // YEARBOARD_H
