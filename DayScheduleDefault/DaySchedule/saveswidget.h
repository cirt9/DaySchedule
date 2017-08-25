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
    size_t maximumFileNameSize;

    QLineEdit * saveNameLineEdit;

    void createScroll();
    void createFooter(QString responseText);

private slots:
    void setFileNime(QString & fileName);

public:
    explicit SavesWidget(QString responseButtonText, size_t maxFileNameSize, QWidget * parent = 0);

    void createSaveName(QString name);

signals:
    void fileNameChosen();
};

#endif // SAVESWIDGET_H
