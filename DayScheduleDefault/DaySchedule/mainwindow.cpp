#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <dayboard.h>
#include <monthboard.h>
#include <yearboard.h>
#include <listofyearsboard.h>

MainWindow::MainWindow(QWidget * parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);
    MainWindow::setWindowTitle(QString("Day Schedule"));

    menu = nullptr;
    currentlyUsedDate = QSharedPointer<QDate>(new QDate);
    currentlyUsedDate->setDate(2017, 6, 26);

    clearMainWindow();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayMainMenu()
{
    initializeCenteredMenu();
    customizeMenu();
    connectMenuToSlots();
}

void MainWindow::initializeCenteredMenu()
{
    int menuSize = 500;
    menu = new MainMenu(menuSize, menuSize, this);
    menu->setFixedSize(menuSize, menuSize);

    QGridLayout * centeringLayout = new QGridLayout();
    QSpacerItem * leftSpacer = new QSpacerItem(0, QSizePolicy::Expanding, QSizePolicy::Expanding);
    QSpacerItem * rightSpacer = new QSpacerItem(0, QSizePolicy::Expanding, QSizePolicy::Expanding);
    QWidget * menuContainer = new QWidget(this);

    centeringLayout->addItem(leftSpacer, 0, 0);
    centeringLayout->addWidget(menu, 0, 1);
    centeringLayout->addItem(rightSpacer, 0, 2);

    menuContainer->setLayout(centeringLayout);
    setCentralWidget(menuContainer);
}

void MainWindow::customizeMenu()
{
    if(menu != nullptr)
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
}

void MainWindow::connectMenuToSlots()
{
    if(menu != nullptr)
    {
        connect(menu->getBottomButton(), SIGNAL(clicked()), this, SLOT(close()));
        connect(menu->getCentralButton(), SIGNAL(clicked()), this, SLOT(start()));
    }
}

void MainWindow::start()
{
    clearMainWindow();

    showYearsList();
}

void MainWindow::showYearsList()
{
    ListOfYearsBoard * years = new ListOfYearsBoard(currentlyUsedDate, this);
    connect(years, SIGNAL(currentlyUsedDateHasChanged()), this, SLOT(showYear()));

    QGridLayout * centeringLayout = new QGridLayout();
    QSpacerItem * leftSpacer = new QSpacerItem(0, QSizePolicy::Expanding, QSizePolicy::Expanding);
    QSpacerItem * rightSpacer = new QSpacerItem(0, QSizePolicy::Expanding, QSizePolicy::Expanding);
    QWidget * yearsContainter = new QWidget(this);

    centeringLayout->addItem(leftSpacer, 0, 0);
    centeringLayout->addWidget(years, 0, 1);
    centeringLayout->addItem(rightSpacer, 0, 2);

    yearsContainter->setLayout(centeringLayout);
    setCentralWidget(yearsContainter);
}

void MainWindow::showYear()
{
    clearMainWindow();

    YearBoard * year = new YearBoard(currentlyUsedDate, this);
    connect(year, SIGNAL(currentlyUsedDateHasChanged()), this, SLOT(showMonth()));

    QGridLayout * centeringLayout = new QGridLayout();
    QSpacerItem * leftSpacer = new QSpacerItem(0, QSizePolicy::Expanding, QSizePolicy::Expanding);
    QSpacerItem * rightSpacer = new QSpacerItem(0, QSizePolicy::Expanding, QSizePolicy::Expanding);
    QWidget * yearContainter = new QWidget(this);

    centeringLayout->addItem(leftSpacer, 0, 0);
    centeringLayout->addWidget(year, 0, 1);
    centeringLayout->addItem(rightSpacer, 0, 2);

    yearContainter->setLayout(centeringLayout);
    setCentralWidget(yearContainter);
}

void MainWindow::showMonth()
{
    clearMainWindow();

    MonthBoard * month = new MonthBoard(currentlyUsedDate, this);
    connect(month, SIGNAL(currentlyUsedDateHasChanged()), this, SLOT(showDay()));

    QGridLayout * centeringLayout = new QGridLayout();
    QSpacerItem * leftSpacer = new QSpacerItem(0, QSizePolicy::Expanding, QSizePolicy::Expanding);
    QSpacerItem * rightSpacer = new QSpacerItem(0, QSizePolicy::Expanding, QSizePolicy::Expanding);
    QWidget * monthContainter = new QWidget(this);

    centeringLayout->addItem(leftSpacer, 0, 0);
    centeringLayout->addWidget(month, 0, 1);
    centeringLayout->addItem(rightSpacer, 0, 2);

    monthContainter->setLayout(centeringLayout);
    setCentralWidget(monthContainter);
}

void MainWindow::showDay()
{
    DayBoard * day = new DayBoard(currentlyUsedDate, this);

    QGridLayout * centeringLayout = new QGridLayout();
    QSpacerItem * leftSpacer = new QSpacerItem(0, QSizePolicy::Expanding, QSizePolicy::Expanding);
    QSpacerItem * rightSpacer = new QSpacerItem(0, QSizePolicy::Expanding, QSizePolicy::Expanding);
    QWidget * dayContainter = new QWidget(this);

    centeringLayout->addItem(leftSpacer, 0, 0);
    centeringLayout->addWidget(day, 0, 1);
    centeringLayout->addItem(rightSpacer, 0, 2);

    dayContainter->setLayout(centeringLayout);
    setCentralWidget(dayContainter);
}

void MainWindow::clearMainWindow()
{
    LayoutDeleter deleter(this->layout());
    deleter.clearLayout();
}
