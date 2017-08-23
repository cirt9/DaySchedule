#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget * parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);
    MainWindow::setWindowTitle(QString("Day Schedule"));

    installEventFilter(this);
    initializeTraySystem();

    centralWidgetLayout = nullptr;
    centeringLayout = nullptr;
    currentlyUsedDate = QSharedPointer<QDate>(new QDate);
    setCurrentlyUsedDate(QDate::currentDate());
    alarmsEnabledByDefault = false;

    loadSettings();
    clearMainWindow();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupDatabase(QString fileName)
{
    DatabaseManager & db = DatabaseManager::getInstance();
    QString path = QString("profiles//") + fileName;
    db.connect(path);
}

void MainWindow::initializeTraySystem()
{
    traySystem = new QSystemTrayIcon(this);
    connect(traySystem, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
    this, SLOT(activateDoubleClickForTray(QSystemTrayIcon::ActivationReason)));

    traySystem->setIcon(QIcon(":/icons/icons/trayicon.jpg"));
    traySystem->show();

    QAction * showAction = new QAction("Show", this);
    connect(showAction, SIGNAL(triggered()), this, SLOT(showMaximized()));

    QAction * hideAction = new QAction("Hide", this);
    connect(hideAction, SIGNAL(triggered()), this, SLOT(hide()));

    QAction * quitAction = new QAction("Quit", this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    QMenu * traySystemMenu = new QMenu(this);
    traySystemMenu->addAction(showAction);
    traySystemMenu->addAction(hideAction);
    traySystemMenu->addSeparator();
    traySystemMenu->addAction(quitAction);

    traySystem->setContextMenu(traySystemMenu);
}

void MainWindow::activateDoubleClickForTray(QSystemTrayIcon::ActivationReason reason)
{
    if(reason == QSystemTrayIcon::DoubleClick)
        this->show();
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
    vacuumApp();

    int menuSize = 500;
    MainMenu * menu = new MainMenu(menuSize, menuSize, this);
    menu->setFixedSize(menuSize, menuSize);
    setMenuIcons(menu);
    connectMenuToSlots(menu);

    showWidgetOnCenter(menu);
}

void MainWindow::vacuumApp()
{
    DatabaseManager & db = DatabaseManager::getInstance();
    db.closeDatabase();
    taskManager.disconnectTimers();
    disconnect(&taskManager, SIGNAL(newTaskStarted()), this, SLOT(taskStartCatched()));
    disconnect(&taskManager, SIGNAL(taskEnded()), this, SLOT(taskEndCatched()));
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
    connect(menu->getBottomButton(), SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(menu->getLeftButton(), SIGNAL(clicked()), this, SLOT(showAboutScreen()));
    connect(menu->getRightButton(), SIGNAL(clicked()), this, SLOT(showSettingsScreen()));
    connect(menu->getCentralButton(), SIGNAL(clicked()), this, SLOT(start()));
}

void MainWindow::start()
{
    setupDatabase("default.dsch");

    taskManager.connectTimers();
    taskManager.updateTask();
    connect(&taskManager, SIGNAL(newTaskStarted()), this, SLOT(taskStartCatched()));
    connect(&taskManager, SIGNAL(taskEnded()), this, SLOT(taskEndCatched()));

    showYearsList();
}

void MainWindow::startLoaded()
{

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
    settingsTitle->setMinimumWidth(520);

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

void MainWindow::showResults()
{
    resetCentralWidget();
    showMenuBar();

    Statistics statistics;

    QString succeeded = QString::number(statistics.getNumberOfSucceededActivities());
    QString failed = QString::number(statistics.getNumberOfFailedActivities());
    QString blank = QString::number(statistics.getNumberOfBlankActivities());
    QString productiveDays = QString::number(statistics.getNumberOfProductiveDays());
    QString bestYear = statistics.getBestYear();
    int successRate = statistics.getSuccessRate();

    StatsWidget * stats = new StatsWidget(getResultsTitle(successRate),
                                          "Success rate: " + QString::number(successRate) + "%");
    stats->createStat("Number of productive days:", productiveDays);
    stats->createStat("Best year:", bestYear);
    stats->createStat("Succeeded activities:", succeeded);
    stats->createStat("Failed activities:", failed);
    stats->createStat("Blank activities:", blank);

    showWidgetOnCenter(stats);
}

QString MainWindow::getResultsTitle(int successRate)
{
    if(successRate < 25)
        return QString("Don't stop!");
    else if(successRate < 50)
        return QString("Not bad");
    else if(successRate < 75)
        return QString("You are doing great");
    else if(successRate < 100)
        return QString("Wow!");
    else
        return QString("Perfection");
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
        connect(timeCounter, &TimeCounter::clicked, this, [=]{showExactDay(QDate::currentDate());} );
        menuBar->addWidget(timeCounter, 180);

        QPushButton * resultsButton = new QPushButton(QString("Results"));
        resultsButton->setObjectName("BarMiddleWidget");
        connect(resultsButton, SIGNAL(clicked()), this, SLOT(showResults()));
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
    removeEventFilter(this);
    close();
}

void MainWindow::saveSettings()
{
    QFile inputFile("settings.dat");
    if(inputFile.open(QIODevice::WriteOnly))
    {
        QDataStream settings(&inputFile);
        settings << alarmsEnabledByDefault;

        inputFile.close();
    }
}

void MainWindow::loadSettings()
{
    QFile inputFile("settings.dat");

    if(inputFile.open(QIODevice::ReadOnly))
    {
       QDataStream settings(&inputFile);
       settings >> alarmsEnabledByDefault;

       inputFile.close();
    }
    else
    {
        QFile makeFile("settings.dat");
        makeFile.open(QIODevice::WriteOnly);
        makeFile.close();
    }
}

void MainWindow::taskStartCatched()
{
    QString messageTitle = "Task started " + taskManager.getFromTime().toString("hh:mm") +
                    " - " + taskManager.getToTime().toString("hh:mm");

    traySystem->showMessage(messageTitle, taskManager.getDescription());
}

void MainWindow::taskEndCatched()
{
    if(centeringLayout)
    {
        DatabaseManager & db = DatabaseManager::getInstance();

        if(db.getAlarmsStateForToday())
            QSound::play(":/sounds/sounds/notification_sound.wav");

        Notification * notification = new Notification(taskManager.getDescription());
        notification->createTimeIntervalText(taskManager.getFromTime(), taskManager.getToTime());
        notification->setLeftButtonText("More");
        notification->setRightButtonText("Got it");

        connect(notification, &Notification::leftButtonClicked, this,
                [=]{showExactDay(QDate::currentDate());} );

        connect(notification, &Notification::rightButtonClicked, this,
                [=]{closeNotification(notification);} );

        centeringLayout->addWidget(notification, 0, 1, Qt::AlignCenter);
    }
}

void MainWindow::closeNotification(Notification * notification)
{
    centeringLayout->removeWidget(notification);
    notification->deleteLater();
}

bool MainWindow::eventFilter(QObject * obj, QEvent * event)
{
    if (event->type() == QEvent::Close)
    {
        event->ignore();
        hide();

        return true;
    }
    return QMainWindow::eventFilter(obj, event);
}
