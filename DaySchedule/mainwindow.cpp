#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <mainmenubutton.h>

#include <QPushButton>
#include <mainmenu.h>

MainWindow::MainWindow(QWidget * parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMinimumSize(100, 100);

    //MainMenuButton * button = new MainMenuButton(200, 50, -45, this);

    //QPushButton * but = new QPushButton(this);
    //MainWindow::setCentralWidget(button);
    //button->move(width()/2, height()/2);

    MainMenu * menu = new MainMenu(this);
    MainWindow::setCentralWidget(menu);

    delete ui->mainToolBar;
    delete ui->statusBar;
}

MainWindow::~MainWindow()
{
    delete ui;
}
