#include "statistics.h"

#include <QLabel>
#include <QVBoxLayout>

Statistics::Statistics(QWidget * parent) : QGroupBox(parent)
{
    setObjectName("Statistics");
    setMinimumSize(100, 100);

    QVBoxLayout * layout = new QVBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    QLabel * title = new QLabel("Title");
    title->setObjectName("StatisticsTitle");
    title->setFixedHeight(80);
    title->setMinimumWidth(520);
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);
    layout->setAlignment(title, Qt::AlignTop);
}
