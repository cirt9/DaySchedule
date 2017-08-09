#include "optionwidget.h"

OptionWidget::OptionWidget(QString text, bool defaultValue, QWidget * parent) : QGroupBox(parent)
{
    setObjectName("OptionWidget");

    QLabel * optionText = new QLabel(text);
    optionText->setObjectName("OptionWidgetText");

    checkBox = new QCheckBox();
    checkBox->setChecked(defaultValue);
    checkBox->setObjectName("OptionWidgetCheckBox");

    QHBoxLayout * layout = new QHBoxLayout();
    layout->setSpacing(80);
    layout->addWidget(optionText);
    layout->addWidget(checkBox);
    layout->setAlignment(checkBox, Qt::AlignRight);

    setLayout(layout);
}

QCheckBox * OptionWidget::getCheckBox() const
{
    return checkBox;
}
