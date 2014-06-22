#include "OmgGameContainer.h"
#include "OmgGame.h"
#include "Folders/OmgFoldersMngr.h"
#include <QDebug>
#include "OmgEnemy.h"
#include "OmgEnemyContainer.h"
#include "OmgItem.h"
#include "OmgItemContainer.h"
#include "Folders/OmgFolder.h"

OmgGameContainer* OmgGameContainer::_p_instance = NULL;

OmgGameContainer::OmgGameContainer()
{
}

OmgGameContainer*
OmgGameContainer::Instance( void )
{
    if(!_p_instance)
        _p_instance = new OmgGameContainer();

    return _p_instance;
}

OmgGame*
OmgGameContainer::getGame(QString aName)
{
    if(_map_games.find(aName) != _map_games.end() )
    {
        return _map_games[aName];
    }
    return NULL;
}

void
OmgGameContainer::addGame(OmgGame *aGame)
{
    // Pre- Condition
    if(!aGame)
        return;

    _map_games[aGame->getName()] = aGame;
}

void
OmgGameContainer::deleteGame(QString aName)
{
    std::map< QString, OmgGame*>::iterator it = _map_games.find(aName);
    if( it != _map_games.end() )
        _map_games.erase( it );

}

Omega::EntityVector
OmgGameContainer::availableGames( void )
{
    //! Iterators of the map
    std::map<QString,OmgGame*>::iterator it = _map_games.begin(),
                                        it_end = _map_games.end();

    //! Iterates over the map adding the players to the vector
    Omega::EntityVector _vector_to_rtn;

    for(; it != it_end; ++it )
    {
        _vector_to_rtn.push_back((*it).second);
    }


    //! Return the vector
    return _vector_to_rtn;
}

Omega::EntityVector
OmgGameContainer::gamesInFolder(QString a_folder_name)
{
    Omega::EntityVector vgames;

    // Pre- Condition
    if(_map_games.empty())
        return vgames;

    std::map<QString,OmgGame*>::iterator it = _map_games.begin(), it_end = _map_games.end();

    // Iterate over the scene objects that are inside the container
    for(; it != it_end; ++it)
    {
        OmgGame* pMap = (*it).second;

        if(pMap->getFolderName() == a_folder_name )
            vgames.push_back(  pMap );
    }

    // Return the vector with all the QOmgListItem's of the container
    return vgames;
}