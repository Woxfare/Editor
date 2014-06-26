#include "OmgMapContainer.h"
#include "OmgMap.h"
#include "Folders/OmgFoldersMngr.h"
#include <Ogre.h>

OmgMapContainer* OmgMapContainer::_p_instance = NULL;

OmgMapContainer::OmgMapContainer()
{
}

OmgMapContainer*
OmgMapContainer::Instance( void )
{
    if(!_p_instance)
        _p_instance = new OmgMapContainer();

    return _p_instance;
}

OmgMap*
OmgMapContainer::getMap(QString aName)
{
    if(_map_maps.find(aName) != _map_maps.end() )
    {
        return _map_maps[aName];
    }
    return NULL;
}

void
OmgMapContainer::addMap(OmgMap *aMap)
{
    // Pre- Condition
    if(!aMap)
        return;

    _map_maps[aMap->getName()] = aMap;
}

void
OmgMapContainer::deleteMap(QString aName)
{
    std::map< QString, OmgMap*>::iterator it = _map_maps.find(aName);
    if( it != _map_maps.end() )
        _map_maps.erase( it );

}

Omega::EntityVector
OmgMapContainer::availableMaps( void )
{
    //! Iterators of the map
    std::map<QString,OmgMap*>::iterator it = _map_maps.begin(),
                                        it_end = _map_maps.end();

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
OmgMapContainer::mapsInFolder(QString a_folder_name)
{
    Omega::EntityVector vMaps;

    // Pre- Condition
    if(_map_maps.empty())
        return vMaps;

    std::map<QString,OmgMap*>::iterator it = _map_maps.begin(), it_end = _map_maps.end();

    // Iterate over the scene objects that are inside the container
    for(; it != it_end; ++it)
    {
        OmgMap* pMap = (*it).second;

        if(pMap->getFolderName() == a_folder_name )
            vMaps.push_back(  pMap );
    }

    // Return the vector with all the QOmgListItem's of the container
    return vMaps;
}


void
OmgMapContainer::buildMap( QStringList mapParams )
{
    //MAP[Prueba1|DefaultMaps|255|0|0|mario2.png|b|4|12,0,9|12,0,-1|2,0,4|17,0,3|]
    int nParams = mapParams.size();

    if( nParams < 2 )
        return;

    if( !OmgFoldersMngr::Instance()->getFolder(mapParams[1]))
    {
      OmgFolder *folder = new OmgFolder( mapParams[1], Omega::MapFolder );
      OmgFoldersMngr::Instance()->addFolder( folder );

    }

    OmgMap* newMap = new OmgMap( mapParams[0], mapParams[1]);

    if( nParams < 5 )
        return;

    newMap->setColor( QColor(mapParams[2].toInt(), mapParams[3].toInt(), mapParams[4].toInt() ));

    if( nParams < 6 )
        return;

    newMap->setTerrainTextureName(mapParams[5]);

    if( nParams < 7 )
        return;

    std::vector< std::pair < std::string, std::vector< Ogre::Vector3 > > > sceneObjects;

    for( int i = 6 ; i < mapParams.size() - 1; ++i )
    {
      std::pair < std::string, std::vector< Ogre::Vector3 > > auxPair;

      std::string cubeName = mapParams[i].toStdString();
      ++i;
      int nCubes = mapParams[i].toInt();
      std::vector< Ogre::Vector3 > auxVector;
      for( int j = 0 ; j < nCubes*3; j+=3 )
      {
        auxVector.push_back( Ogre::Vector3( mapParams[i+j+1].toInt(), mapParams[i+2+j].toInt(), mapParams[i+3+j].toInt() ));
      }

      sceneObjects.push_back(std::make_pair( cubeName, auxVector ));
      i += nCubes*3;
    }

    newMap->setSceneObjectsToTheMap( sceneObjects );

    addMap(newMap);
}
