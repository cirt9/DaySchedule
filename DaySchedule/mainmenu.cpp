#include "mainmenu.h"

MainMenu::MainMenu(int width, int height, QWidget * parent) : QWidget(parent)
{
    menuWidth = width;
    menuHeight = height;
    backgroundColor = Qt::transparent;
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

void MainMenu::paintEvent(QPaintEvent *)
{
    QPainter backgroundPainter(this);

    QBrush background(backgroundColor);

    backgroundPainter.setBrush(background);
    backgroundPainter.setPen(Qt::NoPen);

    backgroundPainter.drawRect(0, 0, width(), height());
}

void MainMenu::resizeEvent(QResizeEvent *)
{
    int halfWindowWidth = this->width()/2 - menuWidth/2;
    int halfWindowHeight = this->height()/2 - menuHeight/2;

    topButton->move(halfWindowWidth, halfWindowHeight);
    leftButton->move(halfWindowWidth, topButton->height() + halfWindowHeight);
    bottomButton->move(leftButton->width() + halfWindowWidth, leftButton->height() + halfWindowHeight);
    rightButton->move(topButton->width() + halfWindowWidth, halfWindowHeight);
    centralButton->move(leftButton->width() + halfWindowWidth, topButton->height() + halfWindowHeight);
}

void MainMenu::setButtonsStylesheet(const QString styleSheet)
{
    topButton->setStyleSheet(styleSheet);
    leftButton->setStyleSheet(styleSheet);
    bottomButton->setStyleSheet(styleSheet);
    rightButton->setStyleSheet(styleSheet);
    centralButton->setStyleSheet(styleSheet);
}

void MainMenu::setBackgroundColor(const QColor & value)
{
    backgroundColor = value;
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
