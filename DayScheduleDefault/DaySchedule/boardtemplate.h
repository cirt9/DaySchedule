#ifndef BOARDTEMPLATE_H
#define BOARDTEMPLATE_H

#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QList>
#include <QDate>
#include <QSharedPointer>

class BoardTemplate : public QGroupBox
{
    Q_OBJECT

protected:
    QSharedPointer<QDate> currentlyUsedDate;

    QVBoxLayout * boardLayout;
    QHBoxLayout * headerLayout;
    QHBoxLayout * footerLayout;

    void createHeaderLayout(QString headerText);
    void createFooterLayout(QString footerText);

public:
    explicit BoardTemplate(QSharedPointer<QDate> currUsedDate, QWidget * parent = nullptr);
    virtual ~BoardTemplate() = 0;

    static void roundCornersOfTheGrid(QGridLayout * layout, QString objectName,
                                      int rows = -1, int columns = -1);

signals:
    void currentlyUsedDateHasChanged();
};

#endif // BOARDTEMPLATE_H
