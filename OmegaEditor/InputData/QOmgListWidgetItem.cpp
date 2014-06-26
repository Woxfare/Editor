#include "QOmgListWidgetItem.h"

QOmgListWidgetItem::QOmgListWidgetItem(QIcon aIcon, QString aName, Omega::EntityType aType) :
    QListWidgetItem(aIcon,aName)
{
    _itemType = aType;
}

Omega::EntityType
QOmgListWidgetItem::getType( void )
{
    return _itemType;
}
