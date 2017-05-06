#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGridLayout>
#include <QSpacerItem>

MainWindow::MainWindow(QWidget * parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);
    setMinimumSize(600, 600);

    MainMenu * menu = new MainMenu(500, 500, this);

    /*this->setStyleSheet("MainWindow {background-color: rgb(23, 23, 34);}");

    QGridLayout * layout = new QGridLayout();

    QSpacerItem * s1 = new QSpacerItem(100, QSizePolicy::Expanding, QSizePolicy::Expanding);

    QSpacerItem * s2 = new QSpacerItem(100, QSizePolicy::Expanding, QSizePolicy::Expanding);

    QWidget * test = new QWidget(this);
    layout->addItem(s1, 0, 0);
    layout->addWidget(menu, 0, 1);
    layout->addItem(s2, 0, 2);

    menu->setFixedSize(500, 500);;

    test->setLayout(layout);
    setCentralWidget(test);*/
}

MainWindow::~MainWindow()
{
    delete ui;
}
