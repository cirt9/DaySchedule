#include "activity.h"

Activity::Activity(QWidget * parent) : QGroupBox(parent)
{
    fromTime = nullptr;
    toTime = nullptr;
    description = nullptr;

    setStyleSheet("background: rgb(51,102,153); margin-left: 20px; margin-right: 20px; border-radius: 3px;");
    setFixedHeight(130);

    QHBoxLayout * timeRangeLayout = makeTimeRangeLayout();
    QHBoxLayout * iconsLayout = makeIconsLayout();

    QHBoxLayout * timeAndIconsLayout = new QHBoxLayout();
    timeAndIconsLayout->addLayout(timeRangeLayout);
    timeAndIconsLayout->addLayout(iconsLayout);
    timeAndIconsLayout->setSpacing(20);

    QHBoxLayout * descriptionLayout = makeDescriptionLayout();

    QVBoxLayout * activityLayout = new QVBoxLayout();
    activityLayout->addLayout(timeAndIconsLayout);
    activityLayout->addLayout(descriptionLayout);

    setLayout(activityLayout);
}

QHBoxLayout * Activity::makeTimeRangeLayout()
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

QHBoxLayout *Activity::makeIconsLayout()
{
    QHBoxLayout * iconsLayout = new QHBoxLayout();

    QPushButton * startIcon = new QPushButton();
    startIcon->setFixedSize(40, 40);
    startIcon->setStyleSheet("background-image:url(:/placeholderimage.jpg);"
                             "border: none; margin: 0px;");

    QPushButton * deleteIcon = new QPushButton();
    deleteIcon->setFixedSize(40, 40);
    deleteIcon->setStyleSheet("background-image:url(:/placeholderimage.jpg);"
                              "border: none; margin: 0px;");

    iconsLayout->addWidget(startIcon);
    iconsLayout->addWidget(deleteIcon);

    return iconsLayout;
}

QHBoxLayout *Activity::makeDescriptionLayout()
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

