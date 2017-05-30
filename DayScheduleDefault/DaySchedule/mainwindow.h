#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <mainmenu.h>
#include <QGridLayout>
#include <QSpacerItem>
#include <layoutdeleter.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    MainMenu * menu;

    void initializeCenteredMenu();
    void customizeMenu();
    void connectMenuToSlots();

    void clearMainWindow();

private slots:
    void start();

public:
    explicit MainWindow(QWidget * parent = nullptr);
    ~MainWindow();

public slots:
    void displayMainMenu();
};

#endif // MAINWINDOW_H
