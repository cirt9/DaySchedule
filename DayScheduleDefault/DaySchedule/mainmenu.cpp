#include "mainmenu.h"

MainMenu::MainMenu(int width, int height, QWidget * parent) : QWidget(parent)
{
    menuWidth = width;
    menuHeight = height;
    setGeometry(0, 0, menuWidth, menuHeight);

    initButtons();
}

void MainMenu::initButtons()
{
    int topBottomButtonWidth = menuWidth * 0.75;
    int topBottomButtonHeight = menuHeight * 0.25;

    int leftRightButtonWidth = menuWidth * 0.25;
    int leftRightButtonHeight = menuHeight * 0.75;

    int centralButtonWidth = menuWidth - leftRightButtonWidth * 2;
    int centralButtonHeight = menuHeight - topBottomButtonHeight * 2;

    topButton = new QPushButton(this);
    leftButton = new QPushButton(this);
    bottomButton = new QPushButton(this);
    rightButton = new QPushButton(this);
    centralButton = new QPushButton(this);

    topButton->setGeometry(0, 0, topBottomButtonWidth, topBottomButtonHeight);
    leftButton->setGeometry(0, topBottomButtonHeight, leftRightButtonWidth, leftRightButtonHeight);
    bottomButton->setGeometry(leftRightButtonWidth, leftRightButtonHeight, topBottomButtonWidth, topBottomButtonHeight);
    rightButton->setGeometry(topBottomButtonWidth, 0, leftRightButtonWidth, leftRightButtonHeight);
    centralButton->setGeometry(leftRightButtonWidth, topBottomButtonHeight, centralButtonWidth, centralButtonHeight);
}

void MainMenu::setButtonsStylesheet(const QString styleSheet)
{
    topButton->setStyleSheet(styleSheet);
    leftButton->setStyleSheet(styleSheet);
    bottomButton->setStyleSheet(styleSheet);
    rightButton->setStyleSheet(styleSheet);
    centralButton->setStyleSheet(styleSheet);
}

QPushButton * MainMenu::getTopButton() const
{
    return topButton;
}

QPushButton * MainMenu::getLeftButton() const
{
    return leftButton;
}

QPushButton * MainMenu::getBottomButton() const
{
    return bottomButton;
}

QPushButton * MainMenu::getRightButton() const
{
    return rightButton;
}

QPushButton * MainMenu::getCentralButton() const
{
    return centralButton;
}
