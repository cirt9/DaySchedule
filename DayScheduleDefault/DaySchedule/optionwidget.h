#ifndef OPTIONWIDGET_H
#define OPTIONWIDGET_H

#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QCheckBox>

class OptionWidget : public QGroupBox
{
    Q_OBJECT
private:
    QCheckBox * checkBox;

public:
    OptionWidget(QString text, bool defaultValue = false, QWidget * parent = nullptr);

    QCheckBox * getCheckBox() const;
};

#endif // OPTIONWIDGET_H
