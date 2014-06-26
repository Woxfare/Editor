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

void
OmgSceneObjContainer::buildSceneObj(QStringList aSceneObjParams)
{
    int nParams = aSceneObjParams.size();
    //qDebug() << "NPARAMS" << nParams;

    if( nParams < 1 )
        return;

    QString sceneObjName = aSceneObjParams[0];
    qDebug() << "LOADING:" << sceneObjName;

    if( nParams < 2 )
        return;

    int rgb[3]= {aSceneObjParams[1].toInt(),aSceneObjParams[2].toInt(),aSceneObjParams[3].toInt()};

    qDebug() << "RED:"   << rgb[0];
    qDebug() << "GREEN:" << rgb[1];
    qDebug() << "BLUE:"  << rgb[2];

    if( nParams < 5 )
        return;

    int nTextures = aSceneObjParams[5].toInt();

    int finnishIndex = 6 + ( nTextures*2 ); //! Bear in mind that for each texture we have to read two elements

    //qDebug() << "TEXTURES BETWEEN:" << nTextures << "AND" << finnishIndex;

    std::map<std::string, std::string> m_textures;

    for(int i = 6; i < finnishIndex; i+=2 )
    {
        //qDebug() << "IDTEXTURE:" << aSceneObjParams[i] << "TEXTURENAME:" << aSceneObjParams[i+1];
        m_textures[aSceneObjParams[i].toStdString()] = aSceneObjParams[i+1].toStdString();
        //qDebug() << "SIZEMAP:" << m_textures.size();
    }

    OmgSceneObj *sceneObj = new OmgSceneObj( aSceneObjParams[0], m_textures, rgb);

    if( !OmgFoldersMngr::Instance()->getFolder(aSceneObjParams[4]))
    {
        OmgFolder *folder = new OmgFolder( aSceneObjParams[4], Omega::SceneObjFolder );
        OmgFoldersMngr::Instance()->addFolder( folder );
    }
    sceneObj->setFolderName( aSceneObjParams[4]);

   // qDebug() << "THE SCENE OBJ IS INSIDE THE FOLDER:" << sceneObj->getFolderName();

    if( nParams < finnishIndex )
        return;

    QString sceneObjType = aSceneObjParams[finnishIndex];
    if( sceneObjType.contains("Dyna"))
        sceneObj->setObjectType(Omega::Dynamic);
    else
        sceneObj->setObjectType(Omega::Static);

    qDebug() << sceneObj->getObjectTypeStr();

    AddObject(sceneObj);
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
