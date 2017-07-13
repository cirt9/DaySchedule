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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow * ui;
    QVBoxLayout * centralWidgetLayout;
    QSharedPointer<QDate> currentlyUsedDate;

    void setIconsInTheMenu(MainMenu * menu);
    void connectMenuToSlots(MainMenu * menu);

    void clearMainWindow();
    void resetCentralWidget();

    void initializeCentralWidgetLayout();
    void showWidgetOnCenter(QWidget * widget);

    void showMenuBar();
    QToolButton * createPagesButton();
    QToolButton * createShortcutsButton();

private slots:
    void errorReaction(QString errorText);

    void setCurrentlyUsedDate(QDate date);

    void showYearsList();
    void showYear();
    void showMonth();
    void showDay();

public:
    explicit MainWindow(QWidget * parent = nullptr);
    ~MainWindow();

    void sqlTest();

public slots:
    void displayMainMenu();

signals:
    void boardWillBeDestroyed();
};

#endif // MAINWINDOW_H
