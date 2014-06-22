#include "OmgFoldersMngr.h"

OmgFoldersMngr * OmgFoldersMngr::_p_instance = NULL;

OmgFoldersMngr::OmgFoldersMngr()
{
    //! Init the default folders
    addFolder( new OmgFolder("DefaultObjects", Omega::SceneObjFolder));
    addFolder( new OmgFolder("DefaultPlayers", Omega::PlayerFolder));
    addFolder( new OmgFolder("DefaultItems", Omega::ItemFolder));
    addFolder( new OmgFolder("DefaultEnemies", Omega::EnemyFolder));
    addFolder( new OmgFolder("DefaultWeapons", Omega::WeaponFolder));
    addFolder( new OmgFolder("DefaultMaps", Omega::MapFolder) );
    addFolder( new OmgFolder("DefaultGames", Omega::GameFolder) );

    std::map<QString,OmgFolder*>::iterator it = _map_folders.begin(),
                                           it_end = _map_folders.end();
    for( ; it != it_end; ++it )
    {
        OmgFolder* folder  = (*it).second;
        folder->setDefault();
    }
}

OmgFoldersMngr * OmgFoldersMngr::Instance( void )
{
    if(!_p_instance)
       _p_instance =  new OmgFoldersMngr();

    return _p_instance;
}

OmgFolder*
OmgFoldersMngr::getFolder( QString a_name)
{
    if(_map_folders.find(a_name) != _map_folders.end() )
    {
        return _map_folders[a_name];
    }
    return NULL;
}

void
OmgFoldersMngr::addFolder(OmgFolder *aFolder)
{
    // Pre- Condition
    if(!aFolder)
        return;

    _map_folders[aFolder->getName()] = aFolder;
}

void
OmgFoldersMngr::deleteFolder(QString aFolder)
{
    std::map<QString, OmgFolder*>::iterator it = _map_folders.find(aFolder);
    if( it != _map_folders.end() )
    {
        _map_folders.erase( it );

    }
}


Omega::FolderVector
OmgFoldersMngr::getAvailableFolders(Omega::FolderType aType)
{
    Omega::FolderVector vector;
    std::map<QString,OmgFolder*>::iterator it = _map_folders.begin(),
                                it_end = _map_folders.end();
    for( ; it != it_end; ++it )
    {
        OmgFolder* folder  = (*it).second;

        if( folder->getType() == aType )
            vector.push_back((*it).second);
    }

    return vector;
}
