#ifndef DATESELECTINGWIDGET_H
#define DATESELECTINGWIDGET_H

#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDateEdit>

class DateSelectingWidget : public QGroupBox
{
    Q_OBJECT

private:
    QDateEdit * selectedDate;
    QPushButton * confirmButton;
    QPushButton * cancelButton;

private slots:
    void confirmButtonClicked();

public:
    explicit DateSelectingWidget(QWidget * parent = 0);
    ~DateSelectingWidget() {}

    void setConfirmButtonText(QString text);
    void setCancelButtonText(QString text);
    void setDateRanges(QDate min, QDate max);
    QDate getSelectedDate() const;

signals:
    void confirmed(QDate selectedDate);
    void canceled();
};

#endif // DATESELECTINGWIDGET_H
