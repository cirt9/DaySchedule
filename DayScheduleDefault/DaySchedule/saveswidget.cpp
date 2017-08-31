#include "saveswidget.h"

const QString SavesWidget::LOAD = QString("load");
const QString SavesWidget::SAVE = QString("save");

SavesWidget::SavesWidget(QString workingMode,size_t maxFileNameSize,QWidget * parent) : QGroupBox(parent)
{
    setObjectName("SavesWidget");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    maximumFileNameSize = maxFileNameSize;
    mode = workingMode;

    layout = new QVBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    saveNamesLayout = new QVBoxLayout();
    saveNamesLayout->setContentsMargins(21, 0, 21, 0);
    saveNamesLayout->setAlignment(Qt::AlignTop);

    createScroll();

    if(mode == SavesWidget::SAVE)
    {
        QLabel * title = new QLabel("Saves");
        title->setObjectName("SavesHeader");
        title->setFixedHeight(80);
        title->setMinimumWidth(520);
        title->setAlignment(Qt::AlignCenter);
        layout->insertWidget(0, title);

        createFooter("Save");
    }
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
    saveNameLineEdit->setPlaceholderText("Your save name");

    QPushButton * responseButton = new QPushButton(responseText);
    responseButton->setObjectName("SavesResponseButton");
    responseButton->setFixedHeight(80);
    responseButton->setMinimumWidth(120);

    if(mode == SavesWidget::SAVE)
        connect(responseButton, SIGNAL(clicked()), this, SLOT(responseButtonClicked()));

    footerLayout->addWidget(responseButton);

    layout->insertLayout(layout->count(), footerLayout);
}

void SavesWidget::createSaveName(QString name)
{
    FileNameWidget * saveName = new FileNameWidget(name, maximumFileNameSize);
    saveName->setObjectName("SavesSaveName");
    saveName->setFixedHeight(80);

    if(mode == SavesWidget::SAVE)
        connect(saveName, SIGNAL(clicked(QString&)), this, SLOT(setFileName(QString&)));

    else if(mode == SavesWidget::LOAD)
        connect(saveName, SIGNAL(clicked(QString&)), this, SIGNAL(fileNameClicked(QString&)));

    saveNamesLayout->addWidget(saveName);
}

void SavesWidget::setFileName(QString & fileName)
{
    saveNameLineEdit->setText(fileName);
}

void SavesWidget::responseButtonClicked()
{
    emit fileNameChosen(saveNameLineEdit->text());
}
