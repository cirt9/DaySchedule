#include "activity.h"

Activity::Activity(QWidget * parent) : QGroupBox(parent)
{
    fromTime = nullptr;
    toTime = nullptr;
    description = nullptr;
    setFixedHeight(fixedHeightStartEnd);

    QHBoxLayout * timeRangeLayout = createTimeRangeLayout();
    QHBoxLayout * iconsLayout = createControlButtonsLayout();

    QHBoxLayout * timeAndIconsLayout = new QHBoxLayout();
    timeAndIconsLayout->addLayout(timeRangeLayout);
    timeAndIconsLayout->addLayout(iconsLayout);
    timeAndIconsLayout->setSpacing(20);

    QHBoxLayout * descriptionLayout = createDescriptionLayout();

    activityLayout = new QVBoxLayout();
    activityLayout->addLayout(timeAndIconsLayout);
    activityLayout->addLayout(descriptionLayout);

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

    readyButton = new QPushButton();
    readyButton->setFixedSize(40, 40);
    readyButton->setObjectName("ActivityReadyButton");
    connect(readyButton, SIGNAL(clicked()), this, SLOT(startActivity()));

    deleteButton = new QPushButton();
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

    descriptionLabel = new QLabel();
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
    connect(doneButton, SIGNAL(clicked()), this, SLOT(succeeded()));

    QPushButton * failedButton = new QPushButton("I failed!");
    failedButton->setObjectName("ActivityButton");
    connect(failedButton, SIGNAL(clicked()), this, SLOT(failed()));

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

void Activity::startActivity()
{
    setFixedHeight(fixedHeightActivated);

    fromTime->setDisabled(true);
    toTime->setDisabled(true);
    description->setDisabled(true);
    readyButton->setDisabled(true);

    summaryLayout = createSummaryLayout();
    activityLayout->addLayout(summaryLayout);

    emit activityStarted();
}

void Activity::failed()
{
    clearSummaryLayout();
    deleteButton->setDisabled(true);

    description->setStyleSheet("background: rgb(255, 154, 154);");
    descriptionLabel->setStyleSheet("background: rgb(255, 154, 154);");

    emit fail();
}

void Activity::succeeded()
{
    clearSummaryLayout();
    deleteButton->setDisabled(true);

    description->setStyleSheet("background: rgb(177, 238, 144);");
    descriptionLabel->setStyleSheet("background: rgb(177, 238, 144);");

    emit success();
}

void Activity::clearSummaryLayout()
{
    LayoutDeleter deleter(summaryLayout, true, true);
    deleter.clearLayout();
    summaryLayout = nullptr;
    setFixedHeight(fixedHeightStartEnd);
}
