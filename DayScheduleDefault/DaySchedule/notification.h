#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QGroupBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QTime>
#include <QGraphicsDropShadowEffect>

class Notification : public QGroupBox
{
    Q_OBJECT

private:
    QVBoxLayout * notificationLayout;
    QPushButton * leftButton;
    QPushButton * rightButton;
    bool intervalTextAlreadyExists;

    void createShadow();
    QWidget * createButtons();

public:
    explicit Notification(QString description, QWidget * parent = 0);

    void createTimeIntervalText(QTime from, QTime to);
    void setLeftButtonText(QString text);
    void setRightButtonText(QString text);

signals:
    void leftButtonClicked();
    void rightButtonClicked();

};

#endif // NOTIFICATION_H
