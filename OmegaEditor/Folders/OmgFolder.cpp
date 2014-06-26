#include "OmgFolder.h"

OmgFolder::OmgFolder(QString aName, Omega::FolderType aType)
{
    _name = aName;
    _type = aType;
    _def = false;
}

QString
OmgFolder::getName( void )
{
    return _name;
}

Omega::FolderType
OmgFolder::getType( void )
{
    return _type;
}

void
OmgFolder::setName(QString aName)
{
    _name = aName;
}

void
OmgFolder::setType(Omega::FolderType aType)
{
    _type = aType;
}

bool
OmgFolder::isDefault( void )
{
    return _def;
}

void
OmgFolder::setDefault( void )
{
    _def = true;
}
