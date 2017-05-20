#include "activity.h"

Activity::Activity(QWidget * parent) : QGroupBox(parent)
{
    fromTime = nullptr;
    toTime = nullptr;
    description = nullptr;

    setStyleSheet("background: rgb(51,102,153); margin-left: 20px; margin-right: 20px; border-radius: 3px;");
    setFixedHeight(170);

    QHBoxLayout * timeRangeLayout = createTimeRangeLayout();
    QHBoxLayout * iconsLayout = createIconsLayout();

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
    fromTimeLabel->setStyleSheet("background: rgb(255,240,235); font-size: 20px;"
                                 "border-top-right-radius: 0px; padding-left: 2px;"
                                 "border-bottom-right-radius: 0px; margin: 0px;");

    fromTime = new QTimeEdit();
    fromTime->setFixedHeight(50);
    fromTime->setStyleSheet("background: rgb(255,240,235); font-size: 20px;"
                            "border-radius: 0px; margin: 0px;");

    QLabel * toTimeLabel = new QLabel();
    toTimeLabel->setText(QString("To: "));
    toTimeLabel->setAlignment(Qt::AlignCenter);
    toTimeLabel->setFixedHeight(50);
    toTimeLabel->setStyleSheet("background: rgb(255,240,235); font-size: 20px;"
                               "border-radius: 0px; margin: 0px;");

    toTime = new QTimeEdit();
    toTime->setFixedHeight(50);
    toTime->setStyleSheet("background: rgb(255,240,235); font-size: 20px;border-top-left-radius: 0px;"
                          "border-bottom-left-radius: 0px; margin: 0px;");

    timeRangeLayout->addWidget(fromTimeLabel);
    timeRangeLayout->addWidget(fromTime);
    timeRangeLayout->addWidget(toTimeLabel);
    timeRangeLayout->addWidget(toTime);
    timeRangeLayout->setSpacing(0);

    return timeRangeLayout;
}

QHBoxLayout * Activity::createIconsLayout()
{
    QHBoxLayout * iconsLayout = new QHBoxLayout();

    QPushButton * startIcon = new QPushButton();
    startIcon->setFixedSize(40, 40);
    startIcon->setStyleSheet("QPushButton{border: none; margin: 0px;background-image:url(:/icons/icons/ready.jpg);}"
                             "QPushButton:hover{background-image:url(:/icons/icons/readyHover.jpg);}"
                             "QPushButton:pressed{background-image:url(:/icons/icons/readyPressed.jpg);}");

    QPushButton * deleteIcon = new QPushButton();
    deleteIcon->setFixedSize(40, 40);
    deleteIcon->setStyleSheet("QPushButton{border: none; margin: 0px;background-image:url(:/icons/icons/delete.jpg);}"
                              "QPushButton:hover{background-image:url(:/icons/icons/deleteHover.jpg);}"
                              "QPushButton:pressed{background-image:url(:/icons/icons/deletePressed.jpg);}");

    iconsLayout->addWidget(startIcon);
    iconsLayout->addWidget(deleteIcon);

    return iconsLayout;
}

QHBoxLayout * Activity::createDescriptionLayout()
{
    QHBoxLayout * descriptionLayout = new QHBoxLayout();
    descriptionLayout->setSpacing(0);

    QLabel * descriptionLabel = new QLabel();
    descriptionLabel->setText(QString("Description: "));
    descriptionLabel->setAlignment(Qt::AlignCenter);
    descriptionLabel->setFixedHeight(50);
    descriptionLabel->setStyleSheet("background: rgb(255,240,235); font-size:20px;"
                                    "border-top-right-radius: 0px;  margin: 0px;"
                                    "border-bottom-right-radius: 0px; padding-left: 5px;");

    description = new QLineEdit();
    description->setFixedHeight(50);
    description->setStyleSheet("background: rgb(255,240,235); font-size:20px;"
                               "border-top-left-radius: 0px;"
                               "border-bottom-left-radius: 0px; margin: 0px;");

    descriptionLayout->addWidget(descriptionLabel);
    descriptionLayout->addWidget(description);

    return descriptionLayout;
}

QHBoxLayout * Activity::createSummaryLayout()
{
    QHBoxLayout * summaryLayout = new QHBoxLayout();

    QPushButton * doneButton = new QPushButton("I did it!");
    doneButton->setStyleSheet("QPushButton{background: rgb(46, 48, 51); border: 2px solid transparent;"
                              "border-radius: 3px; font-size: 20px; color: rgb(255,240,235);}"
                              "QPushButton:hover{background: rgb(22, 25, 27); border: 1px solid rgb(255,240,235);}"
                              "QPushButton:pressed{border: 2px solid rgb(255,240,235);}");

    QPushButton * failedButton = new QPushButton("I failed!");
    failedButton->setStyleSheet("QPushButton{background: rgb(46, 48, 51); border: 2px solid transparent;"
                              "border-radius: 3px; font-size: 20px; color: rgb(255,240,235);}"
                              "QPushButton:hover{background: rgb(22, 25, 27); border: 1px solid rgb(255,240,235);}"
                              "QPushButton:pressed{border: 2px solid rgb(255,240,235);}");

    summaryLayout->addWidget(doneButton);
    summaryLayout->addWidget(failedButton);

    return summaryLayout;
}

