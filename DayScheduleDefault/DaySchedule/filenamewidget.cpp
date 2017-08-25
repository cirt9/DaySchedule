#include "filenamewidget.h"

FileNameWidget::FileNameWidget(QString text, size_t maxTextLength, QWidget * parent) : QPushButton(parent)
{
    fullFileName = text;
    maxLength = maxTextLength;

    if((size_t)fullFileName.size() > maxLength)
        setText(truncateFileName());
    else
        setText(fullFileName);
}

QString FileNameWidget::truncateFileName()
{
    int toCut = fullFileName.size() - maxLength + 3;
    QString preparedFileName = fullFileName;
    preparedFileName.remove(maxLength-1, toCut);
    preparedFileName.append(QString("..."));

    return preparedFileName;
}

void FileNameWidget::mousePressEvent(QMouseEvent * e)
{
    QPushButton::mousePressEvent(e);
    emit clicked(fullFileName);
}
