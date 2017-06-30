#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget * parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);
    MainWindow::setWindowTitle(QString("Day Schedule"));

    centralWidgetLayout = nullptr;
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

    ListOfYearsBoard * years = new ListOfYearsBoard(currentlyUsedDate, this);
    connect(years, SIGNAL(currentlyUsedDateHasChanged()), this, SLOT(showYear()));

    showWidgetOnCenter(years);
}

void MainWindow::showYear()
{
    resetCentralWidget();
    showMenuBar();

    YearBoard * year = new YearBoard(currentlyUsedDate, this);
    connect(year, SIGNAL(currentlyUsedDateHasChanged()), this, SLOT(showMonth()));
    connect(year, SIGNAL(errorDetected(QString)), this, SLOT(errorReaction(QString)));

    showWidgetOnCenter(year);
}

void MainWindow::showMonth()
{
    resetCentralWidget();
    showMenuBar();

    MonthBoard * month = new MonthBoard(currentlyUsedDate, this);
    connect(month, SIGNAL(currentlyUsedDateHasChanged()), this, SLOT(showDay()));

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
        menuButton->setMinimumWidth(110);
        menuBar->addWidget(menuButton);

        QPushButton * yearsButton = new QPushButton(QString("Years"));
        yearsButton->setMinimumWidth(80);
        yearsButton->setObjectName("BarMiddleWidget");
        menuBar->addWidget(yearsButton);

        QPushButton * yearButton = new QPushButton(QString("Year"));
        yearButton->setMinimumWidth(80);
        yearButton->setObjectName("BarMiddleWidget");
        menuBar->addWidget(yearButton);

        QPushButton * time = new QPushButton(QString("Time"));
        time->setMinimumWidth(80);
        time->setObjectName("BarMiddleWidget");
        menuBar->addWidget(time);

        QPushButton * monthButton = new QPushButton(QString("Month"));
        monthButton->setMinimumWidth(80);
        monthButton->setObjectName("BarMiddleWidget");
        menuBar->addWidget(monthButton);

        QPushButton * dayButton = new QPushButton(QString("Day"));
        dayButton->setMinimumWidth(80);
        dayButton->setObjectName("BarMiddleWidget");
        menuBar->addWidget(dayButton);

        QPushButton * saveButton = new QPushButton(QString("Save"));
        saveButton->setObjectName("BarRightWidget");
        saveButton->setMinimumWidth(110);
        menuBar->addWidget(saveButton);

        centralWidgetLayout->insertWidget(0, menuBar);
    }
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
