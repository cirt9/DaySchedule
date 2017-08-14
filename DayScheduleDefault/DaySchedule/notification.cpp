#include "notification.h"

Notification::Notification(QString description, QWidget * parent) : QGroupBox(parent)
{
    setFixedSize(300, 220);
    setObjectName("Notification");
    intervalTextAlreadyExists = false;
    leftButton = rightButton = nullptr;

    createShadow();

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

void Notification::createShadow()
{
    QGraphicsDropShadowEffect * shadow = new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(15);
    shadow->setXOffset(4);
    shadow->setYOffset(4);
    shadow->setColor(Qt::black);

    setGraphicsEffect(shadow);
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

    leftButton = new QPushButton();
    leftButton->setObjectName("NotificationButton");
    buttonsLayout->addWidget(leftButton);
    connect(leftButton, SIGNAL(clicked()), this, SIGNAL(leftButtonClicked()));

    rightButton = new QPushButton();
    rightButton->setObjectName("NotificationButton");
    buttonsLayout->addWidget(rightButton);
    connect(rightButton, SIGNAL(clicked()), this, SIGNAL(rightButtonClicked()));

    return buttonsContainer;
}

void Notification::setLeftButtonText(QString text)
{
    leftButton->setText(text);
}

void Notification::setRightButtonText(QString text)
{
    rightButton->setText(text);
}
