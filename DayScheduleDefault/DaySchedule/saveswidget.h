#ifndef SAVESWIDGET_H
#define SAVESWIDGET_H

#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <filenamewidget.h>
#include <QScrollArea>

class SavesWidget : public QGroupBox
{
    Q_OBJECT
private:
    QVBoxLayout * layout;
    QVBoxLayout * saveNamesLayout;

    QLineEdit * saveNameLineEdit;

    void createScroll();
    void createFooter();

private slots:
    void setFileNime(QString & fileName);

public:
    explicit SavesWidget(QWidget * parent = 0);

    void createSaveName(QString name);
};

#endif // SAVESWIDGET_H
