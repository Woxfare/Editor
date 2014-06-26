#include "OmgPlayerContainer.h"
#include "OmgPlayer.h"

#include "Folders/OmgFoldersMngr.h"
#include <QDebug>

OmgPlayerContainer* OmgPlayerContainer::_p_instance = NULL;

OmgPlayerContainer::OmgPlayerContainer()
{
}

OmgPlayerContainer*
OmgPlayerContainer::Instance( void )
{
    if(!_p_instance)
        _p_instance = new OmgPlayerContainer();

    return _p_instance;
}

OmgPlayer*
OmgPlayerContainer::getPlayer(QString aName)
{
    if(_map_players.find(aName) != _map_players.end() )
    {
        return _map_players[aName];
    }
    return NULL;
}

bool
OmgPlayerContainer::addPlayer(OmgPlayer *a_player)
{
    // Pre- Condition
    if(!a_player)
        return false;

    _map_players[a_player->getName()] = a_player;

    return true;
}

void
OmgPlayerContainer::deletePlayer(QString a_name)
{
    std::map< QString, OmgPlayer*>::iterator it = _map_players.find(a_name);
    if( it != _map_players.end() )
        _map_players.erase( it );

}

Omega::EntityVector
OmgPlayerContainer::availablePlayers( void )
{
    //! Iterators of the map
    std::map<QString,OmgPlayer*>::iterator it = _map_players.begin(),
                                           it_end = _map_players.end();

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
OmgPlayerContainer::availablePlayerItems()
{
    // The vector to return
    Omega::ListItemVector v_items;

    // Pre- Condition
    if(_map_players.empty())
        return v_items;

    std::map<QString,OmgPlayer*>::iterator it = _map_players.begin(), it_end = _map_players.end();

    // Iterate over the scene objects that are inside the container
    for(;it != it_end; ++it)
    {
        OmgPlayer* p_obj = (*it).second;

        // Add the QOmgListItem to the vector to return
        v_items.push_back(  p_obj->listItem() );
    }

    // Return the vector with all the QOmgListItem's of the container
    return v_items;
}

Omega::EntityVector
OmgPlayerContainer::playersInFolder(QString a_folder_name)
{
    Omega::EntityVector v_entities;

    // Pre- Condition
    if(_map_players.empty())
        return v_entities;

    std::map<QString,OmgPlayer*>::iterator it = _map_players.begin(), it_end = _map_players.end();

    // Iterate over the scene objects that are inside the container
    for(; it != it_end; ++it)
    {
        OmgPlayer* p_obj = (*it).second;

        if(p_obj->getFolderName() == a_folder_name )
            v_entities.push_back(  p_obj );
    }

    // Return the vector with all the QOmgListItem's of the container
    return v_entities;
}


void
OmgPlayerContainer::buildPlayer( QStringList playerParams )
{
    int nParams = playerParams.size();

    if( nParams < 2 )
        return;

    if( !OmgFoldersMngr::Instance()->getFolder(playerParams[1]))
    {
      OmgFolder *folder = new OmgFolder( playerParams[1], Omega::PlayerFolder );
      OmgFoldersMngr::Instance()->addFolder( folder );
    }

    OmgPlayer *player = new OmgPlayer( playerParams[0], playerParams[1]);

    if( nParams < 3 )
        return;

    QColor color(playerParams[2].toInt(), playerParams[3].toInt(), playerParams[4].toInt());
    player->setColor(color);

    player->setTotalLife( playerParams[5].toInt());

    std::map<std::string, std::map<std::string, std::string>> textures;
    textures[playerParams[6].toStdString()] = getPartTextures(7, playerParams );
    textures[playerParams[19].toStdString()] = getPartTextures(20, playerParams );
    textures[playerParams[32].toStdString()] = getPartTextures(33, playerParams );
    textures[playerParams[45].toStdString()] = getPartTextures(46, playerParams );
    textures[playerParams[58].toStdString()] = getPartTextures(59, playerParams );
    textures[playerParams[71].toStdString()] = getPartTextures(72, playerParams );

    player->setTextures( textures );

    addPlayer(player);
}

std::map<std::string, std::string>
OmgPlayerContainer::getPartTextures( int beginIndex, QStringList playerParams )
{
  std::map<std::string, std::string> partTextures;
  partTextures[playerParams[beginIndex].toStdString()]    = playerParams[beginIndex+1].toStdString();
  partTextures[playerParams[beginIndex+2].toStdString()]  = playerParams[beginIndex+3].toStdString();
  partTextures[playerParams[beginIndex+4].toStdString()]  = playerParams[beginIndex+5].toStdString();
  partTextures[playerParams[beginIndex+6].toStdString()]  = playerParams[beginIndex+7].toStdString();
  partTextures[playerParams[beginIndex+8].toStdString()]  = playerParams[beginIndex+9].toStdString();
  partTextures[playerParams[beginIndex+10].toStdString()] = playerParams[beginIndex+11].toStdString();
  return partTextures;
}