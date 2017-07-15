#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget * parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);
    MainWindow::setWindowTitle(QString("Day Schedule"));

    centralWidgetLayout = nullptr;
    currentlyUsedDate = QSharedPointer<QDate>(new QDate);
    setCurrentlyUsedDate(QDate::currentDate());

    clearMainWindow();

    sqlTest();
}

MainWindow::~MainWindow()
{
    delete ui;
}
//

void MainWindow::sqlTest()
{
    DatabaseManager & db = DatabaseManager::getInstance();
    db.connect("dayScheduleTest.dsch");

}
//
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
    setIconsInTheMenu(menu);
    connectMenuToSlots(menu);

    showWidgetOnCenter(menu);
}

void MainWindow::setIconsInTheMenu(MainMenu * menu)
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
    connect(menu->getCentralButton(), SIGNAL(clicked()), this, SLOT(showYearsList()));
}

void MainWindow::showYearsList()
{
    resetCentralWidget();
    showMenuBar();

    ListOfYearsBoard * years = new ListOfYearsBoard("Your goal or note", currentlyUsedDate, this);
    connect(years, SIGNAL(currentlyUsedDateHasChanged()), this, SLOT(showYear()));

    years->load();

    connect(years, SIGNAL(currentlyUsedDateHasChanged()), this, SIGNAL(yearsBoardWillBeDestroyed()));
    connect(this, SIGNAL(yearsBoardWillBeDestroyed()), years, SLOT(save()));

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

    connect(year, SIGNAL(currentlyUsedDateHasChanged()), this, SIGNAL(yearBoardWillBeDestroyed()));
    connect(this, SIGNAL(yearBoardWillBeDestroyed()), year, SLOT(save()));

    showWidgetOnCenter(year);
}

void MainWindow::showMonth()
{
    resetCentralWidget();
    showMenuBar();

    MonthBoard * month = new MonthBoard("Your goal or note", currentlyUsedDate, this);
    connect(month, SIGNAL(currentlyUsedDateHasChanged()), this, SLOT(showDay()));

    month->load();

    connect(month, SIGNAL(currentlyUsedDateHasChanged()), this, SIGNAL(monthBoardWillBeDestroyed()));
    connect(this, SIGNAL(monthBoardWillBeDestroyed()), month, SLOT(save()));

    showWidgetOnCenter(month);
}

void MainWindow::showDay()
{
    resetCentralWidget();
    showMenuBar();

    DayBoard * day = new DayBoard(currentlyUsedDate, this);

    showWidgetOnCenter(day);
}

void MainWindow::showWidgetOnCenter(QWidget * widget)
{
    QGridLayout * centeringLayout = new QGridLayout();
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

        QToolButton * shortcutsButton = createShortcutsButton();
        menuBar->addWidget(shortcutsButton);

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

QToolButton * MainWindow::createPagesButton()
{
    QMenu * pagesMenu = new QMenu();
    pagesMenu->setObjectName("MenuToolButton");

    QAction * yearsAction = new QAction("Years List", this);
    connect(yearsAction, SIGNAL(triggered()), this, SLOT(showYearsList()));

    QAction * yearAction = new QAction("Year", this);
    connect(yearAction, SIGNAL(triggered()), this, SLOT(showYear()));

    QAction * monthAction = new QAction("Month", this);
    connect(monthAction, SIGNAL(triggered()), this, SLOT(showMonth()));

    QAction * dayAction = new QAction("Day", this);
    connect(dayAction, SIGNAL(triggered()), this, SLOT(showDay()));

    pagesMenu->addAction(yearsAction);
    pagesMenu->addAction(yearAction);
    pagesMenu->addAction(monthAction);
    pagesMenu->addAction(dayAction);

    QToolButton * pagesButton = new QToolButton();
    pagesButton->setText(QString("Pages"));
    pagesButton->setMenu(pagesMenu);
    pagesButton->setObjectName("BarMiddleWidget");
    pagesButton->setPopupMode(QToolButton::InstantPopup);
    return pagesButton;
}

QToolButton * MainWindow::createShortcutsButton()
{
    QMenu * shortcutsMenu = new QMenu();
    shortcutsMenu->setObjectName("MenuToolButton");

    QAction * yesterdayAction = new QAction("Yesterday", this);
    connect(yesterdayAction, &QAction::triggered, this, [=]{setCurrentlyUsedDate(QDate::currentDate().addDays(-1));} );
    connect(yesterdayAction, SIGNAL(triggered()), this, SLOT(showDay()));

    QAction * todayAction = new QAction("Today", this);
    connect(todayAction, &QAction::triggered, this, [=]{setCurrentlyUsedDate(QDate::currentDate());} );
    connect(todayAction, SIGNAL(triggered()), this, SLOT(showDay()));

    QAction * tomorrowAction = new QAction("Tomorrow", this);
    connect(tomorrowAction, &QAction::triggered, this, [=]{setCurrentlyUsedDate(QDate::currentDate().addDays(1));} );
    connect(tomorrowAction, SIGNAL(triggered()), this, SLOT(showDay()));

    shortcutsMenu->addAction(yesterdayAction);
    shortcutsMenu->addAction(todayAction);
    shortcutsMenu->addAction(tomorrowAction);

    QToolButton * shortcutsButton = new QToolButton();
    shortcutsButton->setText(QString("Shortcuts"));
    shortcutsButton->setMenu(shortcutsMenu);
    shortcutsButton->setObjectName("BarMiddleWidget");
    shortcutsButton->setPopupMode(QToolButton::InstantPopup);
    return shortcutsButton;
}

void MainWindow::initializeCentralWidgetLayout()
{
    centralWidgetLayout = new QVBoxLayout();
    centralWidgetLayout->setContentsMargins(11, 0, 11, 11);

    QWidget * container = new QWidget();
    container->setLayout(centralWidgetLayout);
    setCentralWidget(container);
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
    LayoutDeleter deleter(this->layout());
    deleter.clearLayout();
}

void MainWindow::errorReaction(QString errorText)
{
    QMessageBox::critical(this, QString("Error"), errorText);
    close();
}
