#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget * parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);
    setMinimumSize(600, 600);

    MainMenu * menu = new MainMenu(500, 500, this);
    MainWindow::setCentralWidget(menu);

    menu->setBackgroundColor(QColor(23, 23, 34));
}

MainWindow::~MainWindow()
{
    delete ui;
}
