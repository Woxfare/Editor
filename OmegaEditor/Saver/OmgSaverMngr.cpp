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
	EntitiesXMLWriter xmlWriterPlayers(   OmgPlayerContainer::Instance()->availablePlayers(),           "players.xml" );
	EntitiesXMLWriter xmlWriterEnemies(	  OmgEnemyContainer::Instance()->availableEnemies(),            "enemies.xml" );
	EntitiesXMLWriter xmlWriterSceneObj(  OmgSceneObjContainer::Instance()->GetAvailableSceneObjects(), "sceneobj.xml" );
	EntitiesXMLWriter xmlWriterItems(     OmgItemContainer::Instance()->availableItems(),               "items.xml" );
	EntitiesXMLWriter xmlWriterWeapons(   OmgWeaponsContainer::Instance()->availableWeapons(),          "weapons.xml" );
	EntitiesXMLWriter xmlWriterMaps(      OmgMapContainer::Instance()->availableMaps(),                 "map.xml" );
	EntitiesXMLWriter xmlWriterGames(     OmgGameContainer::Instance()->availableGames(),               "games.xml" );
  _allSaved = true;
}
