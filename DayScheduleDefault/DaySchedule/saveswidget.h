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

    QString  mode;
    size_t maximumFileNameSize;

    QLineEdit * saveNameLineEdit;

    void createScroll();
    void createFooter(QString responseText);

private slots:
    void setFileName(QString & fileName);
    void responseButtonClicked();

public:
    explicit SavesWidget(QString workingMode, size_t maxFileNameSize, QWidget * parent = 0);

    static const QString LOAD;
    static const QString SAVE;

    void createSaveName(QString name);

signals:
    void fileNameChosen(QString fileName);
    void fileNameClicked(QString & fileName);
};

#endif // SAVESWIDGET_H
