#include "activity.h"

Activity::Activity(QWidget * parent) : QGroupBox(parent)
{
    fromTime = nullptr;
    toTime = nullptr;
    description = nullptr;
    setFixedHeight(170);

    QHBoxLayout * timeRangeLayout = createTimeRangeLayout();
    QHBoxLayout * iconsLayout = createControlButtonsLayout();

    QHBoxLayout * timeAndIconsLayout = new QHBoxLayout();
    timeAndIconsLayout->addLayout(timeRangeLayout);
    timeAndIconsLayout->addLayout(iconsLayout);
    timeAndIconsLayout->setSpacing(20);

    QHBoxLayout * descriptionLayout = createDescriptionLayout();
    QHBoxLayout * summaryLayout = createSummaryLayout();

    QVBoxLayout * activityLayout = new QVBoxLayout();
    activityLayout->addLayout(timeAndIconsLayout);
    activityLayout->addLayout(descriptionLayout);
    activityLayout->addLayout(summaryLayout);

    setLayout(activityLayout);
}

QHBoxLayout * Activity::createTimeRangeLayout()
{
    QHBoxLayout * timeRangeLayout = new QHBoxLayout();

    QLabel * fromTimeLabel = new QLabel();
    fromTimeLabel->setText(QString("From: "));
    fromTimeLabel->setAlignment(Qt::AlignVCenter);
    fromTimeLabel->setFixedHeight(50);
    fromTimeLabel->setObjectName("ActivityFromTimeLabel");

    fromTime = new QTimeEdit();
    fromTime->setFixedHeight(50);
    fromTime->setObjectName("ActivityFromTimeEdit");

    QLabel * toTimeLabel = new QLabel();
    toTimeLabel->setText(QString("To: "));
    toTimeLabel->setAlignment(Qt::AlignCenter);
    toTimeLabel->setFixedHeight(50);
    toTimeLabel->setObjectName("ActivityToTimeLabel");

    toTime = new QTimeEdit();
    toTime->setFixedHeight(50);
    toTime->setObjectName("ActivityToTimeEdit");

    timeRangeLayout->addWidget(fromTimeLabel);
    timeRangeLayout->addWidget(fromTime);
    timeRangeLayout->addWidget(toTimeLabel);
    timeRangeLayout->addWidget(toTime);
    timeRangeLayout->setSpacing(0);

    return timeRangeLayout;
}

QHBoxLayout * Activity::createControlButtonsLayout()
{
    QHBoxLayout * controlButtonsLayout = new QHBoxLayout();

    QPushButton * readyButton = new QPushButton();
    readyButton->setFixedSize(40, 40);
    readyButton->setObjectName("ActivityReadyButton");

    QPushButton * deleteButton = new QPushButton();
    deleteButton->setFixedSize(40, 40);
    deleteButton->setObjectName("ActivityDeleteButton");
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteActivity()));

    controlButtonsLayout->addWidget(readyButton);
    controlButtonsLayout->addWidget(deleteButton);

    return controlButtonsLayout;
}

QHBoxLayout * Activity::createDescriptionLayout()
{
    QHBoxLayout * descriptionLayout = new QHBoxLayout();
    descriptionLayout->setSpacing(0);

    QLabel * descriptionLabel = new QLabel();
    descriptionLabel->setText(QString("Description: "));
    descriptionLabel->setAlignment(Qt::AlignCenter);
    descriptionLabel->setFixedHeight(50);
    descriptionLabel->setObjectName("ActivityDescriptionLabel");

    description = new QLineEdit();
    description->setFixedHeight(50);
    description->setObjectName("ActivityDescriptionLineEdit");

    descriptionLayout->addWidget(descriptionLabel);
    descriptionLayout->addWidget(description);

    return descriptionLayout;
}

QHBoxLayout * Activity::createSummaryLayout()
{
    QHBoxLayout * summaryLayout = new QHBoxLayout();

    QPushButton * doneButton = new QPushButton("I did it!");
    doneButton->setObjectName("ActivityButton");

    QPushButton * failedButton = new QPushButton("I failed!");
    failedButton->setObjectName("ActivityButton");

    summaryLayout->addWidget(doneButton);
    summaryLayout->addWidget(failedButton);

    return summaryLayout;
}

void Activity::deleteActivity()
{
    emit activityDeleted(this);

    LayoutDeleter deleter(this->layout(), true);
    deleter.clearLayout();

    delete this;
}
