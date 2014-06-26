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

void
OmgItemContainer::buildItem(QStringList aItemParams)
{
    int nParams = aItemParams.size();
   // qDebug() << "NPARAMS" << nParams;

    if( nParams < 1 )
        return;

    QString itemName = aItemParams[0];
    //qDebug() << "LOADING:" << itemName;

    if( nParams < 2 )
        return;

    int rgb[3]= {aItemParams[1].toInt(),aItemParams[2].toInt(),aItemParams[3].toInt()};

    //qDebug() << "RED:"   << rgb[0];
    //qDebug() << "GREEN:" << rgb[1];
    //qDebug() << "BLUE:"  << rgb[2];

    if( nParams < 5 )
        return;

    int nTextures = aItemParams[5].toInt();

    int finnishIndex = 6 + ( nTextures*2 ); //! Bear in mind that for each texture we have to read two elements

    //qDebug() << "TEXTURES BETWEEN:" << nTextures << "AND" << finnishIndex;

    std::map<std::string, std::string> m_textures;

    for(int i = 6; i < finnishIndex; i+=2 )
    {
        //qDebug() << "IDTEXTURE:" << aItemParams[i] << "TEXTURENAME:" << aItemParams[i+1];
        m_textures[aItemParams[i].toStdString()] = aItemParams[i+1].toStdString();
        //qDebug() << "SIZEMAP:" << m_textures.size();
    }

    OmgItem *item = new OmgItem( itemName, m_textures,rgb);

    if( !OmgFoldersMngr::Instance()->getFolder(aItemParams[4]))
    {
        OmgFolder *folder = new OmgFolder( aItemParams[4], Omega::PlayerFolder );
        OmgFoldersMngr::Instance()->addFolder( folder );
    }

    item->setFolderName(aItemParams[4]);
    qDebug() << item->getFolderName() ;

    if( nParams < finnishIndex )
        return;

    QString itemType = aItemParams[finnishIndex];
    if( itemType.contains("Gold"))
        item->setItemType(Omega::Gold);
    else if( itemType.contains("Health"))
       item->setItemType(Omega::Health);
    else
        item->setItemType(Omega::Ammo);

    qDebug() << item->itemTypeStr();

    OmgItemContainer::Instance()->addItem(item);
}
