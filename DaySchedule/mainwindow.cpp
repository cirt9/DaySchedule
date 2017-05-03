#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <mainmenubutton.h>

#include <QPushButton>
#include <mainmenu.h>
#include <QGridLayout>

MainWindow::MainWindow(QWidget * parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setGeometry(0, 0, 1900, 1000);
    setMinimumSize(600, 600);
    move(0, 0);

    MainMenu * menu = new MainMenu(this);
    MainWindow::setCentralWidget(menu);

    delete ui->mainToolBar;
    delete ui->statusBar;
}

MainWindow::~MainWindow()
{
    delete ui;
}
