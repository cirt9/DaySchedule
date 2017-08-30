#include "mainwindowtemplate.h"

MainWindowTemplate::MainWindowTemplate(QString titleText, int width, QWidget * parent)
                                       : QGroupBox(parent)
{
    centralObjectAlreadyExists = false;

    templateLayout = new QVBoxLayout();
    templateLayout->setAlignment(Qt::AlignTop);
    setLayout(templateLayout);

    QLabel * title = new QLabel(titleText);
    title->setMinimumWidth(width);
    title->setObjectName("MainWindowTemplateTitle");
    title->setAlignment(Qt::AlignCenter);

    QPushButton * backButton = new QPushButton("Back");
    backButton->setObjectName("MainWindowTemplateBackButton");
    connect(backButton, SIGNAL(clicked()), this, SIGNAL(backClicked()));

    templateLayout->addWidget(title);
    templateLayout->addWidget(backButton);
}

void MainWindowTemplate::setMainWidget(QWidget * mainWidget)
{
    if(!centralObjectAlreadyExists)
    {
        mainWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        templateLayout->insertWidget(templateLayout->count()-1, mainWidget);
        centralObjectAlreadyExists = true;
    }
}
