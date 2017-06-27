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
    showMenu();
    setIconsInTheMenu();
    connectMenuToSlots();
}

void MainWindow::showMenu()
{
    int menuSize = 500;
    menu = new MainMenu(menuSize, menuSize, this);
    menu->setFixedSize(menuSize, menuSize);

    showWidgetOnCenter(menu);
}

void MainWindow::setIconsInTheMenu()
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
    clearMainWindow();

    ListOfYearsBoard * years = new ListOfYearsBoard(currentlyUsedDate, this);
    connect(years, SIGNAL(currentlyUsedDateHasChanged()), this, SLOT(showYear()));

    showWidgetOnCenter(years);
}

void MainWindow::showYear()
{
    clearMainWindow();

    YearBoard * year = new YearBoard(currentlyUsedDate, this);
    connect(year, SIGNAL(currentlyUsedDateHasChanged()), this, SLOT(showMonth()));

    showWidgetOnCenter(year);
}

void MainWindow::showMonth()
{
    clearMainWindow();

    MonthBoard * month = new MonthBoard(currentlyUsedDate, this);
    connect(month, SIGNAL(currentlyUsedDateHasChanged()), this, SLOT(showDay()));

    showWidgetOnCenter(month);
}

void MainWindow::showDay()
{
    clearMainWindow();

    DayBoard * day = new DayBoard(currentlyUsedDate, this);

    showWidgetOnCenter(day);
}

void MainWindow::showWidgetOnCenter(QWidget * widget)
{
    QGridLayout * centeringLayout = new QGridLayout();
    QSpacerItem * leftSpacer = new QSpacerItem(0, QSizePolicy::Expanding, QSizePolicy::Expanding);
    QSpacerItem * rightSpacer = new QSpacerItem(0, QSizePolicy::Expanding, QSizePolicy::Expanding);
    QWidget * containter = new QWidget(this);

    centeringLayout->addItem(leftSpacer, 0, 0);
    centeringLayout->addWidget(widget, 0, 1);
    centeringLayout->addItem(rightSpacer, 0, 2);

    containter->setLayout(centeringLayout);
    setCentralWidget(containter);
}

void MainWindow::clearMainWindow()
{
    LayoutDeleter deleter(this->layout());
    deleter.clearLayout();
}
