#include "OmgWeaponsContainer.h"
#include "OmgWeapon.h"
#include "Folders/OmgFoldersMngr.h"
#include <QDebug>

OmgWeaponsContainer* OmgWeaponsContainer::_p_instance = NULL;
OmgWeaponsContainer::OmgWeaponsContainer(){}
OmgWeaponsContainer*
OmgWeaponsContainer::Instance( void ) { return ( _p_instance ) ? _p_instance : _p_instance = new OmgWeaponsContainer; }

OmgWeapon*
OmgWeaponsContainer::getWeapon(QString aName)
{
    if(_mapWeapons.find(aName) != _mapWeapons.end() )
    {
        return _mapWeapons[aName];
    }
    return NULL;
}

bool
OmgWeaponsContainer::addWeapon(OmgWeapon *aWeapon)
{
    // Pre- Condition
    if(!aWeapon)
        return false;

    _mapWeapons[aWeapon->getName()] = aWeapon;

    return true;
}

void
OmgWeaponsContainer::deleteWeapon(QString a_name)
{
    std::map< QString, OmgWeapon*>::iterator it = _mapWeapons.find(a_name);
    if( it != _mapWeapons.end() )
    {
        _mapWeapons.erase( it );
    }
}

Omega::EntityVector
OmgWeaponsContainer::availableWeapons( void )
{
    //! Iterators of the map
    std::map<QString,OmgWeapon*>::iterator it = _mapWeapons.begin(),
                                           it_end = _mapWeapons.end();

    //! Iterates over the map adding the Weapons to the vector
    Omega::EntityVector _vector_to_rtn;

    for(; it != it_end; ++it )
    {
        _vector_to_rtn.push_back((*it).second);
    }


    //! Return the vector
    return _vector_to_rtn;
}


Omega::ListItemVector
OmgWeaponsContainer::availableWeaponsItems( void )
{
    // The vector to return
    Omega::ListItemVector v_items;

    // Pre- Condition
    if(_mapWeapons.empty())
        return v_items;

    std::map<QString,OmgWeapon*>::iterator it = _mapWeapons.begin(), it_end = _mapWeapons.end();

    // Iterate over the scene objects that are inside the container
    for(;it != it_end; ++it)
    {
        OmgWeapon* p_obj = (*it).second;

        // Add the QOmgListItem to the vector to return
        v_items.push_back(  p_obj->listItem() );
    }

    // Return the vector with all the QOmgListItem's of the container
    return v_items;
}

Omega::EntityVector
OmgWeaponsContainer::weaponsInFolder(QString aFolderName)
{
    Omega::EntityVector v_entities;

    // Pre- Condition
    if(_mapWeapons.empty())
        return v_entities;

    std::map<QString,OmgWeapon*>::iterator it = _mapWeapons.begin(), it_end = _mapWeapons.end();

    // Iterate over the scene objects that are inside the container
    for(; it != it_end; ++it)
    {
        OmgWeapon* p_obj = (*it).second;

        if(p_obj->getFolderName() == aFolderName )
            v_entities.push_back(  p_obj );
    }

    // Return the vector with all the QOmgListItem's of the container
    return v_entities;
}

void
OmgWeaponsContainer::buildWeapon(QStringList weaponParams)
{
    /*int nParams = weaponParams.size();
    //qDebug() << "NPARAMS" << nParams;

    if( nParams < 1 )
        return;

    QString weaponName = weaponParams[0];
    qDebug() << "LOADING:" << weaponName;

    if( nParams < 2 )
        return;

    int rgb[3]= {weaponParams[1].toInt(),weaponParams[2].toInt(),weaponParams[3].toInt()};

    qDebug() << "RED:"   << rgb[0];
    qDebug() << "GREEN:" << rgb[1];
    qDebug() << "BLUE:"  << rgb[2];

    if( nParams < 5 )
        return;

    if( !OmgFoldersMngr::Instance()->getFolder(weaponParams[4]))
    {
        OmgFolder *folder = new OmgFolder( weaponParams[4], Omega::WeaponFolder );
        OmgFoldersMngr::Instance()->addFolder( folder );
    }

    if( nParams < 6 )
        return;

    QString weaponType = weaponParams[5];
    Omega::WeaponType type = Omega::SimpleShot;
    if( weaponType.contains("Blast"))
        type= Omega::BlastShot;
    else if(weaponType.contains("Multi"))
        type = Omega::MultiShot;

    if( nParams < 7 )
        return;

    int nBullets = weaponParams[6].toInt();

    OmgWeapon* newWeapon = new OmgWeapon(weaponName);
    newWeapon->setColor(QColor(rgb[0], rgb[1], rgb[2]));
    newWeapon->setDefaultBullets(nBullets);
    newWeapon->setFolderName(weaponParams[4]);
    newWeapon->setWeaponType(type);

    addWeapon(newWeapon); */
}
