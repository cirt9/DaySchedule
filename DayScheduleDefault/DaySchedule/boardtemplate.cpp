#include "boardtemplate.h"

BoardTemplate::BoardTemplate(QWidget * parent) : QGroupBox(parent)
{
    boardLayout = new QVBoxLayout();
    boardLayout->setSpacing(20);
    boardLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(boardLayout);
}

BoardTemplate::~BoardTemplate()
{

}

void BoardTemplate::createHeaderLayout(QString headerText)
{
    headerLayout = new QHBoxLayout();

    QLabel * headerLabel = new QLabel(QString(headerText));
    headerLabel->setObjectName("BoardTemplateHeaderLabel");
    headerLabel->setMaximumHeight(80);
    headerLabel->setAlignment(Qt::AlignCenter);

    headerLayout->addWidget(headerLabel);

    boardLayout->insertLayout(0, headerLayout);
}

void BoardTemplate::createFooterLayout(QString footerText)
{
    footerLayout = new QHBoxLayout();

    QLabel * footerLabel = new QLabel(QString(footerText));
    footerLabel->setObjectName("BoardTemplateFooterLabel");
    footerLabel->setMaximumHeight(80);
    footerLabel->setAlignment(Qt::AlignCenter);

    footerLayout->addWidget(footerLabel);

    boardLayout->insertLayout(boardLayout->count(), footerLayout);
}
