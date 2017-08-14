#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <mainmenu.h>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <layoutdeleter.h>
#include <QSharedPointer>
#include <QDate>
#include <QMessageBox>
#include <dayboard.h>
#include <monthboard.h>
#include <yearboard.h>
#include <listofyearsboard.h>
#include <bar.h>
#include <QToolButton>
#include <databasemanager.h>
#include <timecounter.h>
#include <taskmanager.h>
#include <optionwidget.h>
#include <notification.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow * ui;
    QVBoxLayout * centralWidgetLayout;
    QGridLayout * centeringLayout;
    QSharedPointer<QDate> currentlyUsedDate;
    TaskManager taskManager;
    bool alarmsEnabledByDefault;

    void setMenuIcons(MainMenu * menu);
    void connectMenuToSlots(MainMenu * menu);

    void clearMainWindow();
    void resetCentralWidget();

    void initializeCentralWidgetLayout();
    void showWidgetOnCenter(QWidget * widget);

    void setCurrentlyUsedDate(QDate date);

    void showMenuBar();
    QToolButton * createPagesButton();
    void createPagesActions(QMenu * pagesMenu);

    DayBoard * createDayBoard();
    TimeCounter * createTimeCounter();

    void setupDatabase();

private slots:
    void errorReaction(QString errorText);

    void showYearsList();
    void showYear();
    void showMonth();
    void showDay();
    void showExactDay(QDate date);

    void showAboutScreen();
    void showSettingsScreen();

    void setAlarmsEnabledByDefault(bool newAlarmsEnabledState);
    void saveSettings();
    void loadSettings();

    void closeNotification(Notification * notification);

public:
    explicit MainWindow(QWidget * parent = nullptr);
    ~MainWindow();

public slots:
    void displayMainMenu();

    void taskStartCatched();
    void taskEndCatched();

signals:
    void centralWidgetWillBeDestroyed();
};

#endif // MAINWINDOW_H
