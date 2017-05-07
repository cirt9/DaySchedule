#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget * parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);
    setMinimumSize(600, 600);
    MainWindow::setWindowTitle(QString("Day Schedule"));
    this->setStyleSheet("MainWindow {background-color: rgb(23, 23, 34);}");

    menu = nullptr;
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
        menu->setButtonsStylesheet(QString("QPushButton{background-color: rgb(36,92,81); border-bottom: 3px solid;}"
                                           "QPushButton:hover{background-color: rgb(30, 85, 75);}"
                                           "QPushButton:pressed{background-color: rgb(36,92,81); border-bottom: 3px solid;}"));

        menu->getCentralButton()->setIconSize(QSize(100,100));
        menu->getCentralButton()->setIcon(QIcon(":/menuIcons/icons/start.png"));
        menu->getLeftButton()->setIconSize(QSize(100,100));
        menu->getLeftButton()->setIcon(QIcon(":/menuIcons/icons/about.png"));
        menu->getTopButton()->setIconSize(QSize(100,100));
        menu->getTopButton()->setIcon(QIcon(":/menuIcons/icons/load.png"));
        menu->getRightButton()->setIconSize(QSize(100,100));
        menu->getRightButton()->setIcon(QIcon(":/menuIcons/icons/options.png"));
        menu->getBottomButton()->setIconSize(QSize(100,100));
        menu->getBottomButton()->setIcon(QIcon(":/menuIcons/icons/quit.png"));
    }
}

void MainWindow::connectMenuToSlots()
{
    if(menu != nullptr)
    {
        connect(menu->getBottomButton(), SIGNAL(clicked()), this, SLOT(close()));
    }
}

