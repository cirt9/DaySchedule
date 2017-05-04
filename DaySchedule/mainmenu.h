#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QPainter>
#include <QPushButton>

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
    QColor backgroundColor;

    void initButtons();
    void centerButtons();

    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);

public:
    explicit MainMenu(int width, int height, QWidget * parent = nullptr);
    ~MainMenu() {}

    void setButtonsStylesheet(const QString styleSheet);
    void setBackgroundColor(const QColor & value);

    QPushButton * getTopButton() const;
    QPushButton * getLeftButton() const;
    QPushButton * getBottomButton() const;
    QPushButton * getRightButton() const;
    QPushButton * getCentralButton() const;
};

#endif // MAINMENU_H
