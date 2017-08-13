#include "notification.h"

Notification::Notification(QString description, QWidget * parent) : QGroupBox(parent)
{
    setFixedSize(300, 220);
    setObjectName("Notification");
    intervalTextAlreadyExists = false;

    notificationLayout = new QVBoxLayout();
    notificationLayout->setContentsMargins(2, 2, 2, 2);
    setLayout(notificationLayout);

    QLabel * title = new QLabel("Notification");
    title->setFixedHeight(40);
    title->setAlignment(Qt::AlignCenter);
    title->setObjectName("NotificationTitle");

    QTextEdit * descriptionText = new QTextEdit(description);
    descriptionText->setDisabled(true);
    descriptionText->setAlignment(Qt::AlignCenter);
    descriptionText->setObjectName("NotificationText");

    QWidget * buttons = createButtons();

    notificationLayout->addWidget(title);
    notificationLayout->addWidget(descriptionText);
    notificationLayout->setAlignment(descriptionText, Qt::AlignCenter);
    notificationLayout->addWidget(buttons);
    notificationLayout->setAlignment(buttons, Qt::AlignBottom);
}

void Notification::createTimeIntervalText(QTime from, QTime to)
{
    if(intervalTextAlreadyExists == false)
    {
        QString intervalString = from.toString("hh:mm") + QString(" - ") + to.toString("hh:mm");

        QLabel * timeIntervalText = new QLabel(intervalString);
        timeIntervalText->setAlignment(Qt::AlignCenter);
        timeIntervalText->setObjectName("NotificationText");

        notificationLayout->insertWidget(1, timeIntervalText);
        intervalTextAlreadyExists = true;
    }
}

QWidget * Notification::createButtons()
{
    QHBoxLayout * buttonsLayout = new QHBoxLayout();
    QWidget * buttonsContainer = new QWidget();
    buttonsContainer->setFixedHeight(40);
    buttonsContainer->setLayout(buttonsLayout);
    buttonsContainer->setObjectName("NotificationButtonsContainer");

    QPushButton * moreInfoButton = new QPushButton("More info");
    moreInfoButton->setObjectName("NotificationButton");
    buttonsLayout->addWidget(moreInfoButton);
    connect(moreInfoButton, SIGNAL(clicked()), this, SIGNAL(leftButtonClicked()));

    QPushButton * okButton = new QPushButton("Got it");
    okButton->setObjectName("NotificationButton");
    buttonsLayout->addWidget(okButton);
    connect(okButton, SIGNAL(clicked()), this, SIGNAL(rightButtonClicked()));

    return buttonsContainer;
}
