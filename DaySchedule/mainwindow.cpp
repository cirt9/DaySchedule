#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGridLayout>
#include <QSpacerItem>

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

    connect(menu->getBottomButton(), SIGNAL(clicked()), this, SLOT(close()));
}
