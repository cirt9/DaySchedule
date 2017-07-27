#include "dateselectingwidget.h"

DateSelectingWidget::DateSelectingWidget(QWidget * parent) : QGroupBox(parent)
{
    setObjectName("DateSelectingWidget");

    QHBoxLayout * dateSelectingLayout = new QHBoxLayout();
    setLayout(dateSelectingLayout);

    selectedDate = new QDateEdit();
    selectedDate->setObjectName("DateSelectingDateEdit");
    selectedDate->setAlignment(Qt::AlignCenter);
    selectedDate->setDate(QDate::currentDate());
    selectedDate->setDisplayFormat("dd.MM.yyyy");

    confirmButton = new QPushButton(QString("Confirm"));
    confirmButton->setObjectName("DateSelectingButton");
    connect(confirmButton, SIGNAL(clicked()), this, SLOT(confirmButtonClicked()));

    cancelButton = new QPushButton(QString("Cancel"));
    cancelButton->setObjectName("DateSelectingButton");
    connect(cancelButton, SIGNAL(clicked()), this, SIGNAL(canceled()));

    dateSelectingLayout->addWidget(selectedDate);
    dateSelectingLayout->addWidget(confirmButton);
    dateSelectingLayout->addWidget(cancelButton);
}

void DateSelectingWidget::setConfirmButtonText(QString text)
{
    confirmButton->setText(text);
}

void DateSelectingWidget::setCancelButtonText(QString text)
{
    cancelButton->setText(text);
}

void DateSelectingWidget::setDateRanges(QDate min, QDate max)
{
    selectedDate->setMinimumDate(min);
    selectedDate->setMaximumDate(max);
}

QDate DateSelectingWidget::getSelectedDate() const
{
    return selectedDate->date();
}

void DateSelectingWidget::confirmButtonClicked()
{
    emit confirmed(selectedDate->date());
}
