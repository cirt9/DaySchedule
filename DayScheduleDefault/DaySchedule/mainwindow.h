#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <mainmenu.h>
#include <QGridLayout>
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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow * ui;
    QSharedPointer<QDate> currentlyUsedDate;

    void setIconsInTheMenu(MainMenu * menu);
    void connectMenuToSlots(MainMenu * menu);

    void clearMainWindow();

    void showWidgetOnCenter(QWidget * widget);

private slots:
    void errorReaction(QString errorText);

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
