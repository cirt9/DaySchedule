#include "filenamewidget.h"

FileNameWidget::FileNameWidget(QString text, QWidget * parent) : QPushButton(parent)
{
    setText(text);
    fullFileName = text;
}

void FileNameWidget::mousePressEvent(QMouseEvent * e)
{
    QPushButton::mousePressEvent(e);
    emit clicked(fullFileName);
}
