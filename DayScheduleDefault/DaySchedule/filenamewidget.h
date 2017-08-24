#ifndef FILENAMEWIDGET_H
#define FILENAMEWIDGET_H

#include <QPushButton>

class FileNameWidget : public QPushButton
{
    Q_OBJECT
private:
    QString fullFileName;

    void mousePressEvent(QMouseEvent * e = nullptr);

public:
    explicit FileNameWidget(QString text, QWidget * parent = 0);

signals:
    void clicked(QString & fileName);
};

#endif // FILENAMEWIDGET_H
