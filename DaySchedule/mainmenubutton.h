#ifndef MAINMENUBUTTON_H
#define MAINMENUBUTTON_H

#include <QWidget>
#include <QPainter>
#include <QGraphicsRectItem>

class MainMenuButton : public QWidget
{
    Q_OBJECT

private:
    int buttonWidth;
    int buttonHeight;

public:
    explicit MainMenuButton(int width, int height, QWidget * parent = nullptr);

    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
};

#endif // MAINMENUBUTTON_H
