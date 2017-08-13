#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QGroupBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QTime>

class Notification : public QGroupBox
{
    Q_OBJECT

private:
    QVBoxLayout * notificationLayout;
    bool intervalTextAlreadyExists;

    QWidget * createButtons();

public:
    explicit Notification(QString description, QWidget * parent = 0);

    void createTimeIntervalText(QTime from, QTime to);

signals:
    void leftButtonClicked();
    void rightButtonClicked();

};

#endif // NOTIFICATION_H
