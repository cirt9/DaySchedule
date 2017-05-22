#include "layoutdeleter.h"

LayoutDeleter::LayoutDeleter(QLayout * layout, bool deleteParentLayout, bool deleteWidgets)
{
    layoutToBeCleared = layout;
    enableDeletingParentLayout = deleteParentLayout;
    enableDeletingWidgets = deleteWidgets;
}

void LayoutDeleter::clear(QLayout * layout, bool deleteWidgets)
{
    while(QLayoutItem * item = layout->takeAt(0))
    {
        if(deleteWidgets)
        {
            if(QWidget * widget = item->widget())
                widget->deleteLater();
        }
        if(QLayout * childLayout = item->layout())
            clear(childLayout, deleteWidgets);
        delete item;
    }
}

void LayoutDeleter::clearLayout()
{
    clear(layoutToBeCleared, enableDeletingWidgets);

    if(enableDeletingParentLayout)
        delete layoutToBeCleared;
}
