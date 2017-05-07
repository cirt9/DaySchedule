#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QPainter>
#include <QPushButton>
#include <QIcon>

class MainMenu : public QWidget
{
    Q_OBJECT
private:
    int menuWidth;
    int menuHeight;
    QPushButton * topButton;
    QPushButton * leftButton;
    QPushButton * bottomButton;
    QPushButton * rightButton;
    QPushButton * centralButton;

    void initButtons();

public:
    explicit MainMenu(int width, int height, QWidget * parent = nullptr);
    ~MainMenu() {}

    void setButtonsStylesheet(const QString styleSheet);

    QPushButton * getTopButton() const;
    QPushButton * getLeftButton() const;
    QPushButton * getBottomButton() const;
    QPushButton * getRightButton() const;
    QPushButton * getCentralButton() const;
};

#endif // MAINMENU_H
