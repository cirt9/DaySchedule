#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <mainmenu.h>
#include <QGridLayout>
#include <QSpacerItem>
#include <layoutdeleter.h>
#include <QSharedPointer>
#include <QDate>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    MainMenu * menu;
    QSharedPointer<QDate> currentlyUsedDate;

    void setIconsInTheMenu();
    void connectMenuToSlots();

    void clearMainWindow();

    void showWidgetOnCenter(QWidget * widget);

private slots:
    void start();

    void showMenu();
    void showYearsList();
    void showYear();
    void showMonth();
    void showDay();

public:
    explicit MainWindow(QWidget * parent = nullptr);
    ~MainWindow();

public slots:
    void displayMainMenu();
};

#endif // MAINWINDOW_H
