#include "OmgSceneObjContainer.h"
#include "InputData/QOmgListItem.h"
#include <qDebug>
#include "Folders/OmgFoldersMngr.h"
#include <QDebug>

OmgSceneObjContainer* OmgSceneObjContainer::_p_instance = NULL;

OmgSceneObjContainer::OmgSceneObjContainer()
{
    qDebug() << "CREANDO SCENEOBJ 1";
    // Init the widgets of the Scene
    _map_obj.clear();
}

OmgSceneObjContainer*
OmgSceneObjContainer::Instance( void )
{
    if(!_p_instance)
        _p_instance = new OmgSceneObjContainer();

    return _p_instance;
}

OmgSceneObj*
OmgSceneObjContainer::getSceneObj(QString a_name)
{
    if(_map_obj.find(a_name) != _map_obj.end() )
    {
        return _map_obj[a_name];
    }
    return NULL;
}

bool
OmgSceneObjContainer::AddObject(OmgSceneObj *a_obj)
{
    // Pre- Condition
    if(!a_obj)
        return false;

    _map_obj[a_obj->getName()] = a_obj;
    return true;
}

bool
OmgSceneObjContainer::DeleteObject(QString a_name)
{
    std::map< QString, OmgSceneObj* >::iterator it = _map_obj.find(a_name);
    if( it != _map_obj.end() )
    {
        _map_obj.erase( it );
        return true;
    }
    return false;
}

Omega::ListItemVector
OmgSceneObjContainer::GetAvailableSceneItems(void)
{
    // The vector to return
    Omega::ListItemVector v_items;

    // Pre- Condition
    if(_map_obj.empty())
        return v_items;

    std::map<QString,OmgSceneObj*>::iterator it = _map_obj.begin(), it_end = _map_obj.end();

    // Iterate over the scene objects that are inside the container
    for(;it != it_end; ++it)
    {
        OmgSceneObj* p_obj = (*it).second;

        // Add the QOmgListItem to the vector to return
        v_items.push_back(  p_obj->listItem() );
    }

    // Return the vector with all the QOmgListItem's of the container
    return v_items;
}

Omega::EntityVector
OmgSceneObjContainer::GetAvailableSceneObjects(void)
{
    // The vector to return
    Omega::EntityVector v_objects;

    // Pre- Condition
    if(_map_obj.empty())
        return v_objects;

    std::map<QString,OmgSceneObj*>::iterator it = _map_obj.begin(), it_end = _map_obj.end();

    // Iterate over the scene objects that are inside the container
    for(;it != it_end; ++it)
        v_objects.push_back((*it).second);

    // Return the vector with all the QOmgListItem's of the container
    return v_objects;
}

Omega::EntityVector
OmgSceneObjContainer::sceneObjInFolder( QString aFolderName )
{
    Omega::EntityVector vObjects;

    // Pre- Condition
    if(_map_obj.empty())
        return vObjects;

    std::map< QString,OmgSceneObj*>::iterator it = _map_obj.begin(), it_end = _map_obj.end();

    // Iterate over the scene objects that are inside the container
    for(; it != it_end; ++it)
    {
        OmgSceneObj* p_obj = (*it).second;

        if(p_obj->getFolderName() == aFolderName )
            vObjects.push_back(  p_obj );
    }

    return vObjects;
}
