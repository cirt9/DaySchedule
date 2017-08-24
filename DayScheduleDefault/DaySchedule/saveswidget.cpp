#include "saveswidget.h"

SavesWidget::SavesWidget(QWidget * parent) : QGroupBox(parent)
{
    setObjectName("SavesWidget");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

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
    createFooter();
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

void SavesWidget::createFooter()
{
    QHBoxLayout * footerLayout = new QHBoxLayout();
    footerLayout->setSpacing(0);

    saveNameLineEdit = new QLineEdit();
    saveNameLineEdit->setObjectName("SavesSaveNameLineEdit");
    saveNameLineEdit->setFixedHeight(80);
    saveNameLineEdit->setAlignment(Qt::AlignCenter);
    footerLayout->addWidget(saveNameLineEdit);

    QPushButton * saveButton = new QPushButton("Save");
    saveButton->setObjectName("SavesSaveButton");
    saveButton->setFixedHeight(80);
    saveButton->setFixedWidth(120);
    footerLayout->addWidget(saveButton);

    layout->addLayout(footerLayout);
}

void SavesWidget::createSaveName(QString name)
{
    FileNameWidget * saveName = new FileNameWidget(name);
    saveName->setObjectName("SavesSaveName");
    saveName->setFixedHeight(80);
    connect(saveName, SIGNAL(clicked(QString&)), this, SLOT(setFileNime(QString&)));

    saveNamesLayout->addWidget(saveName);
}

void SavesWidget::setFileNime(QString &fileName)
{
    saveNameLineEdit->setText(fileName);
}
