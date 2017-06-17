#ifndef BOARDTEMPLATE_H
#define BOARDTEMPLATE_H

#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

class BoardTemplate : public QGroupBox
{
    Q_OBJECT

protected:
    QVBoxLayout * boardLayout;
    QHBoxLayout * headerLayout;
    QHBoxLayout * footerLayout;

    void createHeaderLayout(QString headerText);
    void createFooterLayout(QString footerText);

public:
    explicit BoardTemplate(QWidget * parent = nullptr);
    virtual ~BoardTemplate() = 0;

};

#endif // BOARDTEMPLATE_H
