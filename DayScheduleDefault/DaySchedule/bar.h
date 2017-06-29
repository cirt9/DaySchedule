#ifndef BAR_H
#define BAR_H

#include <QGroupBox>
#include <QHBoxLayout>

class Bar : public QGroupBox
{
    Q_OBJECT
private:
    QHBoxLayout * barLayout;
    int barHeight;

public:
    explicit Bar(QWidget * parent = 0);
    ~Bar() {}

    void setBarHeight(int height);
    void addWidget(QWidget * widget);
};

#endif // BAR_H
