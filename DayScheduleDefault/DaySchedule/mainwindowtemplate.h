#ifndef MAINWINDOWTEMPLATE_H
#define MAINWINDOWTEMPLATE_H

#include <QLabel>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QPushButton>

class MainWindowTemplate : public QGroupBox
{
    Q_OBJECT

private:
    QVBoxLayout * templateLayout;
    bool centralObjectAlreadyExists;

public:
    explicit MainWindowTemplate(QString titleText, int width, QWidget * parent = nullptr);

    void setMainWidget(QWidget * mainWidget);

signals:
    void backClicked();
};

#endif // MAINWINDOWTEMPLATE_H
