#ifndef LAYOUTDELETER_H
#define LAYOUTDELETER_H

#include <QLayout>
#include <QWidget>

class LayoutDeleter
{
private:
    QLayout * layoutToBeCleared;
    bool enableDeletingParentLayout;
    bool enableDeletingWidgets;

    void clear(QLayout * layout, bool deleteWidgets);

public:
    LayoutDeleter(QLayout * layout, bool deleteParentLayout = false, bool deleteWidgets = true);
    ~LayoutDeleter() {}

    void clearLayout();
};

#endif // LAYOUTDELETER_H
