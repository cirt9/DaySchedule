#ifndef MAINMENUBUTTON_H
#define MAINMENUBUTTON_H

#include <QWidget>
#include <QPainter>

class MainMenuButton : public QWidget
{
    Q_OBJECT

private:
    int buttonWidth;
    int buttonHeight;
    int tiltAngle;

public:
    explicit MainMenuButton(int width, int height, int tAngle, QWidget * parent = nullptr);

    void paintEvent(QPaintEvent *);
};

#endif // MAINMENUBUTTON_H
