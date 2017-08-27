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
#include <QSound>
#include <QSystemTrayIcon>
#include <statswidget.h>
#include <statistics.h>
#include <saveswidget.h>

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
    QSystemTrayIcon * traySystem;

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

    void setupDatabase(QString fileName);
    void initializeTraySystem();
    QString getResultsTitle(int successRate);

    void vacuumApp();
    void prepareAppToWork();
    QString cutFileExtension(const QString & fileName);

    bool eventFilter(QObject * obj, QEvent * event);

private slots:
    void errorReaction(QString errorText);

    void start(QString filename);

    void showYearsList();
    void showYear();
    void showMonth();
    void showDay();
    void showExactDay(QDate date);
    void showResults();
    void showSavingScreen();
    void showLoadingScreen();

    void showAboutScreen();
    void showSettingsScreen();

    void setAlarmsEnabledByDefault(bool newAlarmsEnabledState);
    void saveSettings();
    void loadSettings();

    void taskStartCatched();
    void taskEndCatched();
    void closeNotification(Notification * notification);
    void activateDoubleClickForTray(QSystemTrayIcon::ActivationReason reason);

    void save(QString fileName);

public:
    explicit MainWindow(QWidget * parent = nullptr);
    ~MainWindow();

public slots:
    void displayMainMenu();

signals:
    void centralWidgetWillBeDestroyed();
};

#endif // MAINWINDOW_H
