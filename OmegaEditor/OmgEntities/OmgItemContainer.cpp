#include "OmgItemContainer.h"
#include <qDebug>
#include "Folders/OmgFoldersMngr.h"
#include <QDebug>

OmgItemContainer* OmgItemContainer::_p_instance = NULL;

OmgItemContainer::OmgItemContainer()
{
    _map_items.clear();
}

OmgItemContainer::~OmgItemContainer()
{

}

OmgItemContainer*
OmgItemContainer::Instance( void )
{
    if(!_p_instance)
        _p_instance = new OmgItemContainer();

    return _p_instance;
}

OmgItem*
OmgItemContainer::getItem(QString aName)
{
    if(_map_items.find(aName) != _map_items.end() )
    {
        return _map_items[aName];
    }
    return NULL;
}

bool
OmgItemContainer::addItem(OmgItem *aItem)
{
    // Pre- Condition
    if(!aItem)
        return false;

    //qDebug() << "Number of items:" << _map_items.size();

    _map_items[aItem->getName()] = aItem;

    //qDebug() << "Number of items adding "<< aItem->getName()<<":" << _map_items.size();
    return true;
}

bool
OmgItemContainer::deleteItem(QString aName)
{
    std::map< QString, OmgItem *>::iterator it = _map_items.find(aName);
    if( it != _map_items.end() )
    {
        _map_items.erase( it );
        return true;
    }
    return false;
}

Omega::EntityVector
OmgItemContainer::availableItems( void )
{
    //! Iterators of the map
    std::map<QString,OmgItem*>::iterator it = _map_items.begin(),
                                         it_end = _map_items.end();

    //! Iterates over the map adding the players to the vector
    Omega::EntityVector _vector_to_rtn;

    for(; it != it_end; ++it )
    {
        _vector_to_rtn.push_back((*it).second);
    }


    //! Return the vector
    return _vector_to_rtn;
}

Omega::ListItemVector
OmgItemContainer::availableListItems(void)
{
    // The vector to return
    Omega::ListItemVector v_items;

    // Pre- Condition
    if(_map_items.empty())
        return v_items;

    std::map<QString,OmgItem*>::iterator it = _map_items.begin(), it_end = _map_items.end();

    // Iterate over the scene objects that are inside the container
    for(;it != it_end; ++it)
    {
        OmgItem* p_obj = (*it).second;

        // Add the QOmgListItem to the vector to return
        v_items.push_back(  p_obj->listItem() );
    }

    // Return the vector with all the QOmgListItem's of the container
    return v_items;
}

Omega::EntityVector OmgItemContainer::itemsInFolder(QString aFolderName)
{
    Omega::EntityVector vItems;

    // Pre- Condition
    if(_map_items.empty())
        return vItems;

    std::map< QString,OmgItem*>::iterator it = _map_items.begin(), it_end = _map_items.end();

    // Iterate over the scene objects that are inside the container
    for(; it != it_end; ++it)
    {
        OmgItem* p_obj = (*it).second;

        if(p_obj->getFolderName() == aFolderName )
            vItems.push_back(  p_obj );
    }

    return vItems;
}