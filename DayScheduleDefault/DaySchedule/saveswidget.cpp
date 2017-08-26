#include "saveswidget.h"

SavesWidget::SavesWidget(QString responseButtonText,size_t maxFileNameSize,QWidget * parent) : QGroupBox(parent)
{
    setObjectName("SavesWidget");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    maximumFileNameSize = maxFileNameSize;
    layout = new QVBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    QLabel * title = new QLabel("Saves");
    title->setObjectName("SavesHeader");
    title->setFixedHeight(80);
    title->setMinimumWidth(520);
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);

    saveNamesLayout = new QVBoxLayout();
    saveNamesLayout->setContentsMargins(21, 0, 21, 0);
    saveNamesLayout->setAlignment(Qt::AlignTop);

    createScroll();
    createFooter(responseButtonText);
}

void SavesWidget::createScroll()
{
    QScrollArea * scroll = new QScrollArea();
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scroll->setWidgetResizable(true);
    scroll->setObjectName("SaveWidgetScroll");

    QWidget * scrollArea = new QWidget();
    scrollArea->setObjectName("SaveWidgetScrollArea");
    scrollArea->setLayout(saveNamesLayout);
    scroll->setWidget(scrollArea);

    layout->addWidget(scroll);
    layout->setAlignment(scrollArea, Qt::AlignTop);
}

void SavesWidget::createFooter(QString responseText)
{
    QHBoxLayout * footerLayout = new QHBoxLayout();
    footerLayout->setSpacing(0);

    saveNameLineEdit = new QLineEdit();
    saveNameLineEdit->setObjectName("SavesSaveNameLineEdit");
    saveNameLineEdit->setFixedHeight(80);
    saveNameLineEdit->setAlignment(Qt::AlignCenter);
    footerLayout->addWidget(saveNameLineEdit);

    QPushButton * responseButton = new QPushButton(responseText);
    responseButton->setObjectName("SavesResponseButton");
    responseButton->setFixedHeight(80);
    responseButton->setMinimumWidth(120);
    connect(responseButton, SIGNAL(clicked()), this, SLOT(responseButtonClicked()));
    footerLayout->addWidget(responseButton);

    layout->addLayout(footerLayout);
}

void SavesWidget::createSaveName(QString name)
{
    FileNameWidget * saveName = new FileNameWidget(name, maximumFileNameSize);
    saveName->setObjectName("SavesSaveName");
    saveName->setFixedHeight(80);
    connect(saveName, SIGNAL(clicked(QString&)), this, SLOT(setFileNime(QString&)));

    saveNamesLayout->addWidget(saveName);
}

void SavesWidget::setFileNime(QString &fileName)
{
    saveNameLineEdit->setText(fileName);
}

void SavesWidget::responseButtonClicked()
{
    emit fileNameChosen(saveNameLineEdit->text());
}
