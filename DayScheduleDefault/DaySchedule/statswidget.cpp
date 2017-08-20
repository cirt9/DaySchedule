#include "statswidget.h"

StatsWidget::StatsWidget(QString headerText, QString footerText, QWidget * parent) : QGroupBox(parent)
{
    setObjectName("StatsWidget");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layout = new QVBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    QLabel * title = new QLabel(headerText);
    title->setObjectName("StatsHeader");
    title->setFixedHeight(80);
    title->setMinimumWidth(520);
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);

    statsLayout = new QVBoxLayout();
    statsLayout->setContentsMargins(21, 0, 21, 0);
    layout->addLayout(statsLayout);
    layout->setAlignment(statsLayout, Qt::AlignTop);

    QLabel * successRateLabel = new QLabel(footerText);
    successRateLabel->setObjectName("StatsFooter");
    successRateLabel->setFixedHeight(80);
    successRateLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(successRateLabel);
    layout->setAlignment(successRateLabel, Qt::AlignBottom);
}

void StatsWidget::createStat(QString description, QString value)
{
    QHBoxLayout * statLayout = new QHBoxLayout();
    statLayout->setSpacing(0);

    QLabel * statText = new QLabel(description);
    statText->setObjectName("StatsStatText");
    statText->setFixedHeight(80);
    statText->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    statLayout->addWidget(statText);

    QLabel * statData = new QLabel(value);
    statData->setObjectName("StatsStatData");
    statData->setFixedHeight(80);
    statData->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    statLayout->addWidget(statData);

    statsLayout->addLayout(statLayout);
}
