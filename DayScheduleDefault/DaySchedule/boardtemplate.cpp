#include "boardtemplate.h"

BoardTemplate::BoardTemplate(QSharedPointer<QDate> currUsedDate, QWidget * parent) : QGroupBox(parent)
{
    currentlyUsedDate = currUsedDate;
    defaultFooterText = "";
    footerLineEdit = nullptr;

    boardLayout = new QVBoxLayout();
    boardLayout->setSpacing(20);
    boardLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(boardLayout);
}

BoardTemplate::~BoardTemplate()
{

}

void BoardTemplate::createHeaderLayout(QString headerText)
{
    headerLayout = new QHBoxLayout();

    QLabel * headerLabel = new QLabel(headerText);
    headerLabel->setObjectName("BoardTemplateHeader");
    headerLabel->setMaximumHeight(80);
    headerLabel->setAlignment(Qt::AlignCenter);

    headerLayout->addWidget(headerLabel);

    boardLayout->insertLayout(0, headerLayout);
}

void BoardTemplate::createFooterLayout(QString footerText)
{
    footerLayout = new QHBoxLayout();

    footerLineEdit = new QLineEdit(footerText);
    footerLineEdit->setObjectName("BoardTemplateFooter");
    footerLineEdit->setMaxLength(100);
    footerLineEdit->setMaximumHeight(80);
    footerLineEdit->setAlignment(Qt::AlignCenter);

    footerLayout->addWidget(footerLineEdit);

    boardLayout->insertLayout(boardLayout->count(), footerLayout);
}

void BoardTemplate::roundCornersOfTheGrid(QGridLayout * layout, QString objectName, int rows, int columns)
{
    QList<QWidget *> objects;

    for (int i=0; i<layout->count(); i++)
    {
        if(layout->itemAt(i)->widget()->objectName() == objectName)
        {
            QWidget * object = dynamic_cast<QWidget *>(layout->itemAt(i)->widget());
            objects.push_back(object);
        }
    }

    if(rows == -1 || columns == -1)
    {
        rows = layout->rowCount();
        columns = layout->columnCount();
    }

    if(objects.size() != 0)
    {
        objects[0]->setObjectName(objectName + "TopLeftCorner");
        objects[columns-1]->setObjectName(objectName + "TopRightCorner");
        objects[rows * columns - columns]->setObjectName(objectName + "BottomLeftCorner");
        objects[rows * columns - 1]->setObjectName(objectName + "BottomRightCorner");
    }
}
