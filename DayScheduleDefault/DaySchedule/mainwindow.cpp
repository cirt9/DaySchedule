#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget * parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);
    MainWindow::setWindowTitle(QString("Day Schedule"));

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
    connect(year, SIGNAL(errorDetected(QString)), this, SLOT(errorReaction(QString)));

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

    centeringLayout->addItem(leftSpacer, 1, 0);
    centeringLayout->addWidget(widget, 1, 1);
    centeringLayout->addItem(rightSpacer, 1, 2);

    //
    centeringLayout->setContentsMargins(11, 0, 11, 11);
    QSpacerItem * leftSpacer0 = new QSpacerItem(0, QSizePolicy::Expanding, QSizePolicy::Expanding);
    QSpacerItem * rightSpacer0 = new QSpacerItem(0, QSizePolicy::Expanding, QSizePolicy::Expanding);

    Bar * menuBar = new Bar();

    QPushButton * menuButton = new QPushButton(QString("Menu"));
    menuButton->setObjectName("BarLeftWidget");
    menuBar->addWidget(menuButton);

    QPushButton * yearsButton = new QPushButton(QString("Years"));
    yearsButton->setObjectName("BarMiddleWidget");
    menuBar->addWidget(yearsButton);

    QPushButton * yearButton = new QPushButton(QString("Year"));
    yearButton->setObjectName("BarMiddleWidget");
    menuBar->addWidget(yearButton);

    QPushButton * time = new QPushButton(QString("Time"));
    time->setObjectName("BarMiddleWidget");
    menuBar->addWidget(time);

    QPushButton * monthButton = new QPushButton(QString("Month"));
    monthButton->setObjectName("BarMiddleWidget");
    menuBar->addWidget(monthButton);

    QPushButton * dayButton = new QPushButton(QString("Day"));
    dayButton->setObjectName("BarMiddleWidget");
    menuBar->addWidget(dayButton);

    QPushButton * saveButton = new QPushButton(QString("Save"));
    saveButton->setObjectName("BarRightWidget");
    menuBar->addWidget(saveButton);

    centeringLayout->addItem(leftSpacer0, 0, 0);
    centeringLayout->addWidget(menuBar, 0, 1);
    centeringLayout->addItem(rightSpacer0, 0, 2);

    //

    containter->setLayout(centeringLayout);
    setCentralWidget(containter);
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
