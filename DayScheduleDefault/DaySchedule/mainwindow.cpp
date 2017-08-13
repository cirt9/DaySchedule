#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget * parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);
    MainWindow::setWindowTitle(QString("Day Schedule"));

    setupDatabase();

    centralWidgetLayout = nullptr;
    centeringLayout = nullptr;
    currentlyUsedDate = QSharedPointer<QDate>(new QDate);
    setCurrentlyUsedDate(QDate::currentDate());
    alarmsEnabledByDefault = false;

    taskManager.updateTask();
    connect(&taskManager, SIGNAL(newTaskStarted()), this, SLOT(taskStartCatched()));
    connect(&taskManager, SIGNAL(taskEnded()), this, SLOT(taskEndCatched()));

    loadSettings();

    clearMainWindow();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupDatabase()
{
    DatabaseManager & db = DatabaseManager::getInstance();
    db.connect("db.dsch");
}

void MainWindow::setCurrentlyUsedDate(QDate date)
{
    int currentYear = date.year();
    int currentMonth = date.month();
    int currentDay = date.day();

    currentlyUsedDate->setDate(currentYear, currentMonth, currentDay);
}

void MainWindow::displayMainMenu()
{
    resetCentralWidget();

    int menuSize = 500;
    MainMenu * menu = new MainMenu(menuSize, menuSize, this);
    menu->setFixedSize(menuSize, menuSize);
    setMenuIcons(menu);
    connectMenuToSlots(menu);

    showWidgetOnCenter(menu);
}

void MainWindow::setMenuIcons(MainMenu * menu)
{
    menu->getCentralButton()->setIconSize(QSize(100,100));
    menu->getCentralButton()->setIcon(QIcon(":/icons/icons/start.png"));
    menu->getLeftButton()->setIconSize(QSize(100,100));
    menu->getLeftButton()->setIcon(QIcon(":/icons/icons/about.png"));
    menu->getTopButton()->setIconSize(QSize(100,100));
    menu->getTopButton()->setIcon(QIcon(":/icons/icons/load.png"));
    menu->getRightButton()->setIconSize(QSize(100,100));
    menu->getRightButton()->setIcon(QIcon(":/icons/icons/options.png"));
    menu->getBottomButton()->setIconSize(QSize(100,100));
    menu->getBottomButton()->setIcon(QIcon(":/icons/icons/quit.png"));
}

void MainWindow::connectMenuToSlots(MainMenu * menu)
{
    connect(menu->getBottomButton(), SIGNAL(clicked()), this, SLOT(close()));
    connect(menu->getLeftButton(), SIGNAL(clicked()), this, SLOT(showAboutScreen()));
    connect(menu->getRightButton(), SIGNAL(clicked()), this, SLOT(showSettingsScreen()));
    connect(menu->getCentralButton(), SIGNAL(clicked()), this, SLOT(showYearsList()));
}

void MainWindow::showAboutScreen()
{
    QFile file(":/txt/about.txt");

    if(file.open(QIODevice::ReadOnly))
    {
        resetCentralWidget();
        QTextStream fileText(&file);

        QLabel * aboutTitle = new QLabel("About");
        aboutTitle->setObjectName("MainWindowTitle");
        aboutTitle->setAlignment(Qt::AlignCenter);

        QLabel * aboutLabel = new QLabel(fileText.readAll());
        aboutLabel->setObjectName("MainWindowAboutText");
        aboutLabel->setAlignment(Qt::AlignCenter);

        QPushButton * backButton = new QPushButton("Back");
        backButton->setObjectName("MainWindowBackButton");
        connect(backButton, SIGNAL(clicked()), this, SLOT(displayMainMenu()));

        QVBoxLayout * aboutLayout = new QVBoxLayout();
        aboutLayout->addWidget(aboutTitle);
        aboutLayout->addWidget(aboutLabel, Qt::AlignTop);
        aboutLayout->addWidget(backButton);

        QWidget * aboutContainer = new QWidget();
        aboutContainer->setLayout(aboutLayout);
        showWidgetOnCenter(aboutContainer);

        file.close();
    }
    else
        errorReaction(QString("This copy of DaySchedule is corrupted."));
}

void MainWindow::showSettingsScreen()
{
    resetCentralWidget();

    QLabel * settingsTitle = new QLabel("Settings");
    settingsTitle->setObjectName("MainWindowTitle");
    settingsTitle->setAlignment(Qt::AlignCenter);

    OptionWidget * alarmsOption = new OptionWidget("Alarms enabled by default", alarmsEnabledByDefault);
    connect(alarmsOption->getCheckBox(), SIGNAL(toggled(bool)), this, SLOT(setAlarmsEnabledByDefault(bool)));
    alarmsOption->setFixedHeight(60);

    QVBoxLayout * optionsLayout = new QVBoxLayout();
    optionsLayout->addWidget(alarmsOption);
    optionsLayout->setAlignment(alarmsOption, Qt::AlignTop);

    QWidget * optionsContainer = new QWidget();
    optionsContainer->setObjectName("MainWindowOptionsContainer");
    optionsContainer->setLayout(optionsLayout);

    QPushButton * backButton = new QPushButton("Back");
    backButton->setObjectName("MainWindowBackButton");
    connect(backButton, SIGNAL(clicked()), this, SLOT(saveSettings()));
    connect(backButton, SIGNAL(clicked()), this, SLOT(displayMainMenu()));

    QVBoxLayout * settingsLayout = new QVBoxLayout();
    settingsLayout->addWidget(settingsTitle);
    settingsLayout->addWidget(optionsContainer, Qt::AlignTop);
    settingsLayout->addWidget(backButton);

    QWidget * settingsContainer = new QWidget();
    settingsContainer->setLayout(settingsLayout);
    showWidgetOnCenter(settingsContainer);
}

void MainWindow::setAlarmsEnabledByDefault(bool newAlarmsEnabledState)
{
    alarmsEnabledByDefault = newAlarmsEnabledState;
}

void MainWindow::showYearsList()
{
    resetCentralWidget();
    showMenuBar();

    ListOfYearsBoard * years = new ListOfYearsBoard("Your goal or note", currentlyUsedDate, this);
    connect(years, SIGNAL(currentlyUsedDateHasChanged()), this, SLOT(showYear()));

    years->load();
    connect(this, SIGNAL(centralWidgetWillBeDestroyed()), years, SLOT(save()));

    showWidgetOnCenter(years);
}

void MainWindow::showYear()
{
    resetCentralWidget();
    showMenuBar();

    YearBoard * year = new YearBoard("Your goal or note", currentlyUsedDate, this);
    connect(year, SIGNAL(currentlyUsedDateHasChanged()), this, SLOT(showMonth()));
    connect(year, SIGNAL(errorDetected(QString)), this, SLOT(errorReaction(QString)));

    year->load();
    connect(this, SIGNAL(centralWidgetWillBeDestroyed()), year, SLOT(save()));

    showWidgetOnCenter(year);
}

void MainWindow::showMonth()
{
    resetCentralWidget();
    showMenuBar();

    MonthBoard * month = new MonthBoard("Your goal or note", currentlyUsedDate, this);
    connect(month, SIGNAL(currentlyUsedDateHasChanged()), this, SLOT(showDay()));

    month->load();
    connect(this, SIGNAL(centralWidgetWillBeDestroyed()), month, SLOT(save()));

    showWidgetOnCenter(month);
}

void MainWindow::showDay()
{
    resetCentralWidget();
    showMenuBar();

    DayBoard * day = createDayBoard();

    showWidgetOnCenter(day); 
}

void MainWindow::showExactDay(QDate date)
{
    resetCentralWidget();
    showMenuBar();

    setCurrentlyUsedDate(date);
    DayBoard * day = createDayBoard();

    showWidgetOnCenter(day);
}

DayBoard * MainWindow::createDayBoard()
{
    DayBoard * day = new DayBoard(currentlyUsedDate, alarmsEnabledByDefault, this);
    day->load();

    connect(this, SIGNAL(centralWidgetWillBeDestroyed()), day, SLOT(save()));
    connect(day, SIGNAL(destroyed(QObject*)), &taskManager, SLOT(updateTask()));
    connect(day, SIGNAL(currentActivityChanged(QTime,QTime,QString)),
            &taskManager, SLOT(updateTaskLive(QTime,QTime,QString)));

    if(QDate::currentDate() == *currentlyUsedDate)
        connect(&taskManager, SIGNAL(lookingForTask()), day, SLOT(updateCurrentActivity()));

    return day;
}

void MainWindow::showWidgetOnCenter(QWidget * widget)
{
    centeringLayout = new QGridLayout();
    QSpacerItem * leftSpacer = new QSpacerItem(0, QSizePolicy::Expanding, QSizePolicy::Expanding);
    QSpacerItem * rightSpacer = new QSpacerItem(0, QSizePolicy::Expanding, QSizePolicy::Expanding);

    centeringLayout->addItem(leftSpacer, 0, 0);
    centeringLayout->addWidget(widget, 0, 1);
    centeringLayout->addItem(rightSpacer, 0, 2);

    centralWidgetLayout->addLayout(centeringLayout);
}

void MainWindow::showMenuBar()
{
    if(centralWidgetLayout != nullptr)
    {
        Bar * menuBar = new Bar();

        QPushButton * menuButton = new QPushButton(QString("Menu"));
        menuButton->setObjectName("BarLeftWidget");
        connect(menuButton, SIGNAL(clicked()), this, SLOT(displayMainMenu()));
        menuBar->addWidget(menuButton);

        QToolButton * pagesButton = createPagesButton();
        menuBar->addWidget(pagesButton);

        TimeCounter * timeCounter = createTimeCounter();
        menuBar->addWidget(timeCounter, 180);

        QPushButton * resultsButton = new QPushButton(QString("Results"));
        resultsButton->setObjectName("BarMiddleWidget");
        menuBar->addWidget(resultsButton);

        QPushButton * saveButton = new QPushButton(QString("Save"));
        saveButton->setObjectName("BarRightWidget");
        menuBar->addWidget(saveButton);

        QHBoxLayout * barLayout = new QHBoxLayout();
        QSpacerItem * leftSpacer = new QSpacerItem(0, QSizePolicy::Expanding, QSizePolicy::Expanding);
        QSpacerItem * rightSpacer = new QSpacerItem(0, QSizePolicy::Expanding, QSizePolicy::Expanding);
        barLayout->addItem(leftSpacer);
        barLayout->addWidget(menuBar);
        barLayout->addItem(rightSpacer);

        centralWidgetLayout->insertLayout(0, barLayout);
    }
}

TimeCounter * MainWindow::createTimeCounter()
{
    TimeCounter * timeCounter = new TimeCounter();
    timeCounter->setObjectName("BarTimeCounter");
    timeCounter->setCountdownTime(taskManager.getTimeTillEndOfTask());

    connect(&taskManager, &TaskManager::updated, timeCounter,
    [=]{timeCounter->setCountdownTime(taskManager.getTimeTillEndOfTask());});
    connect(timeCounter, SIGNAL(countdownCompleted()), &taskManager, SLOT(startSeekingForTask()));

    return timeCounter;
}

QToolButton * MainWindow::createPagesButton()
{
    QMenu * pagesMenu = new QMenu();
    pagesMenu->setObjectName("MenuToolButton");
    createPagesActions(pagesMenu);

    QToolButton * pagesButton = new QToolButton();
    pagesButton->setText(QString("Pages"));
    pagesButton->setMenu(pagesMenu);
    pagesButton->setObjectName("BarMiddleWidget");
    pagesButton->setPopupMode(QToolButton::InstantPopup);
    return pagesButton;
}

void MainWindow::createPagesActions(QMenu * pagesMenu)
{
    QAction * yearsAction = new QAction("Years List", this);
    connect(yearsAction, SIGNAL(triggered()), this, SLOT(showYearsList()));
    pagesMenu->addAction(yearsAction);

    QAction * yearAction = new QAction("Year", this);
    connect(yearAction, SIGNAL(triggered()), this, SLOT(showYear()));
    pagesMenu->addAction(yearAction);

    QAction * monthAction = new QAction("Month", this);
    connect(monthAction, SIGNAL(triggered()), this, SLOT(showMonth()));
    pagesMenu->addAction(monthAction);

    QAction * dayAction = new QAction("Day", this);
    connect(dayAction, SIGNAL(triggered()), this, SLOT(showDay()));
    pagesMenu->addAction(dayAction);

    QAction * yesterdayAction = new QAction("Yesterday", this);
    connect(yesterdayAction, &QAction::triggered, this, [=]{showExactDay(QDate::currentDate().addDays(-1));} );
    pagesMenu->addAction(yesterdayAction);

    QAction * todayAction = new QAction("Today", this);
    connect(todayAction, &QAction::triggered, this, [=]{showExactDay(QDate::currentDate());} );
    pagesMenu->addAction(todayAction);

    QAction * tomorrowAction = new QAction("Tomorrow", this);
    connect(tomorrowAction, &QAction::triggered, this, [=]{showExactDay(QDate::currentDate().addDays(1));} );
    pagesMenu->addAction(tomorrowAction);
}

void MainWindow::initializeCentralWidgetLayout()
{
    centralWidgetLayout = new QVBoxLayout();
    centralWidgetLayout->setContentsMargins(11, 0, 11, 11);

    QScrollArea * scrollArea = new QScrollArea();
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setWidgetResizable(true);
    scrollArea->setObjectName("MainWindowScrollArea");

    QWidget * container = new QWidget();
    container->setLayout(centralWidgetLayout);
    scrollArea->setWidget(container);
    container->setObjectName("MainWindowContainer");

    setCentralWidget(scrollArea);
}

void MainWindow::resetCentralWidget()
{
    if(this->layout())
    {
        clearMainWindow();
        initializeCentralWidgetLayout();
    }
}

void MainWindow::clearMainWindow()
{
    emit centralWidgetWillBeDestroyed();

    LayoutDeleter deleter(this->layout());
    deleter.clearLayout();
}

void MainWindow::errorReaction(QString errorText)
{
    QMessageBox::critical(this, QString("Error"), errorText);
    close();
}

void MainWindow::saveSettings()
{
    DatabaseManager & db = DatabaseManager::getInstance();
    QSqlQuery query = db.settingsCheckIfExistsQuery();

    if(db.recordAlreadyExists(query))
    {
        query = db.settingsUpdateQuery(alarmsEnabledByDefault);
        db.execQuery(query);
    }
}

void MainWindow::loadSettings()
{
    DatabaseManager & db = DatabaseManager::getInstance();
    QSqlQuery query = db.settingsCheckIfExistsQuery();

    if(db.recordAlreadyExists(query))
    {
        query = db.settingsSelectDataQuery();
        db.execQuery(query);

        query.first();
        alarmsEnabledByDefault = query.value(0).toBool();
    }
}

void MainWindow::taskStartCatched()
{
    qDebug() << "Start catched!";
}

void MainWindow::taskEndCatched()
{
    qDebug() << "End catched!";
    if(centeringLayout)
    {
        Notification * notification = new Notification(taskManager.getDescription());
        notification->createTimeIntervalText(taskManager.getFromTime(), taskManager.getToTime());

        centeringLayout->addWidget(notification, 0, 1, Qt::AlignCenter);
    }
}
