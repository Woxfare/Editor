#include "OmgSaverMngr.h"
#include "EntitiesXMLWriter.h"
#include "OmgEntities/OmgPlayerContainer.h"
#include "OmgEntities/OmgEnemyContainer.h"
#include "OmgEntities/OmgSceneObjContainer.h"
#include "OmgEntities/OmgItemContainer.h"
#include "OmgEntities/OmgWeaponsContainer.h"
#include "OmgEntities/OmgMapContainer.h"
#include "OmgEntities/OmgGameContainer.h"


OmgSaverMngr * OmgSaverMngr::_p_instance = NULL;

OmgSaverMngr::OmgSaverMngr()
{
    _allSaved = true;
}

OmgSaverMngr*
OmgSaverMngr::Instance( void )
{
    if(!_p_instance)
        _p_instance = new OmgSaverMngr();

    return _p_instance;
}

bool
OmgSaverMngr::isAllSaved()
{
    return _allSaved;
}

void
OmgSaverMngr::entityDeleted( void )
{
    _allSaved = false;
}

void
OmgSaverMngr::addEntityToSave(OmgEntity *aEntity)
{
    _allSaved = false;
    _mapEntitiesToSave[aEntity->getName()] = aEntity;
}

void
OmgSaverMngr::saveAll( void )
{
    //!
    //! Get all the entities..
    //!
    Omega::EntityVector vEntities;

    Omega::EntityVector vPlayers = OmgPlayerContainer::Instance()->availablePlayers();
    Omega::EntityVector vEnemies = OmgEnemyContainer::Instance()->availableEnemies();
    Omega::EntityVector vSceneObj = OmgSceneObjContainer::Instance()->GetAvailableSceneObjects();
    Omega::EntityVector vItems = OmgItemContainer::Instance()->availableItems();
    Omega::EntityVector vWeapons = OmgWeaponsContainer::Instance()->availableWeapons();
    Omega::EntityVector vMaps = OmgMapContainer::Instance()->availableMaps();
    Omega::EntityVector vGames = OmgGameContainer::Instance()->availableGames();

    Omega::EntityIterator it;

    it = vWeapons.begin(); // The rest of the entities need the weapons, first write the weapons
    for(; it!= vWeapons.end(); ++it )
      vEntities.push_back(*it);

    it = vPlayers.begin();
    for(; it!= vPlayers.end(); ++it )
        vEntities.push_back(*it);

    it = vEnemies.begin();

    for(; it!= vEnemies.end(); ++it )
        vEntities.push_back(*it);

    it = vSceneObj.begin();

    for(; it!= vSceneObj.end(); ++it )
        vEntities.push_back(*it);

    it = vItems.begin();

    for(; it!= vItems.end(); ++it )
        vEntities.push_back(*it);

    it = vMaps.begin();
    for(; it!= vMaps.end(); ++it )
      vEntities.push_back(*it);

    it = vGames.begin();
    for(; it!= vGames.end(); ++it )
      vEntities.push_back(*it);

    EntitiesXMLWriter xmlWriter( vEntities, "entities.xml" );

    _allSaved = true;
}
