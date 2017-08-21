#ifndef STATSWIDGET_H
#define STATSWIDGET_H

#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

class StatsWidget : public QGroupBox
{
    Q_OBJECT

private:
    QVBoxLayout * layout;
    QVBoxLayout * statsLayout;

public:
    explicit StatsWidget(QString headerText, QString footerText, QWidget * parent = nullptr);
    ~StatsWidget() {}

    void createStat(QString description, QString value);
};

#endif // STATSWIDGET_H
