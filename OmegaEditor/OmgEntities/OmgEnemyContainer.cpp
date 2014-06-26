#include "OmgEnemyContainer.h"

#include "Folders/OmgFoldersMngr.h"
#include <QDebug>

OmgEnemyContainer * OmgEnemyContainer::_p_instance = NULL;

OmgEnemyContainer::OmgEnemyContainer()
{
}

OmgEnemyContainer::~OmgEnemyContainer()
{

}

OmgEnemyContainer * OmgEnemyContainer::Instance( void )
{
    if(!_p_instance)
        _p_instance = new OmgEnemyContainer();

    return _p_instance;
}

OmgEnemy*
OmgEnemyContainer::getEnemy(QString aName)
{
    if(_map_enemies.find(aName) != _map_enemies.end() )
    {
        return _map_enemies[aName];
    }
    return NULL;
}

bool
OmgEnemyContainer::addEnemy(OmgEnemy *apEnemy)
{
    // Pre- Condition
    if(!apEnemy)
        return false;

    _map_enemies[apEnemy->getName()] = apEnemy;

    return true;
}

bool
OmgEnemyContainer::deleteEnemy(QString a_name)
{
    std::map< QString, OmgEnemy*>::iterator it = _map_enemies.find(a_name);
    if( it != _map_enemies.end() )
    {
        _map_enemies.erase( it );
        return true;
    }
    return false;
}

Omega::EntityVector
OmgEnemyContainer::availableEnemies( void)
{
    // The vector to return
    Omega::EntityVector v_enemies;

    // Pre- Condition
    if(_map_enemies.empty())
        return v_enemies;

    std::map<QString,OmgEnemy*>::iterator it = _map_enemies.begin(), it_end = _map_enemies.end();

    // Iterate over the scene objects that are inside the container
    for(;it != it_end; ++it)
        v_enemies.push_back((*it).second);

    // Return the vector with all the QOmgListItem's of the container
    return v_enemies;
}

Omega::ListItemVector
OmgEnemyContainer::availableItemsEnemies( void )
{
    // The vector to return
    Omega::ListItemVector v_items;

    // Pre- Condition
    if(_map_enemies.empty())
        return v_items;

    std::map<QString,OmgEnemy*>::iterator it = _map_enemies.begin(), it_end = _map_enemies.end();

    // Iterate over the scene objects that are inside the container
    for(; it != it_end; ++it)
    {
        OmgEnemy* p_obj = (*it).second;

        // Add the QOmgListItem to the vector to return
        v_items.push_back(  p_obj->listItem() );
    }

    // Return the vector with all the QOmgListItem's of the container
    return v_items;
}

Omega::EntityVector
OmgEnemyContainer::enemiesInFolder(QString aFolderName)
{
    Omega::EntityVector vEnemies;

    // Pre- Condition
    if(_map_enemies.empty())
        return vEnemies;

    std::map< QString,OmgEnemy*>::iterator it = _map_enemies.begin(), it_end = _map_enemies.end();

    // Iterate over the scene objects that are inside the container
    for(; it != it_end; ++it)
    {
        OmgEnemy* p_obj = (*it).second;

        if(p_obj->getFolderName() == aFolderName )
            vEnemies.push_back(  p_obj );
    }

    // Return the vector with all the QOmgListItem's of the container
    return vEnemies;
}

void
OmgEnemyContainer::buildEnemy( QStringList aEnemyParams )
{

  int nParams = aEnemyParams.size();

  if( nParams < 2 )
    return;

  if( !OmgFoldersMngr::Instance()->getFolder(aEnemyParams[1]))
  {
    OmgFolder *folder = new OmgFolder( aEnemyParams[1], Omega::PlayerFolder );
    OmgFoldersMngr::Instance()->addFolder( folder );
  }

  OmgEnemy *enemy = new OmgEnemy( aEnemyParams[0], aEnemyParams[1]);

  if( nParams < 3 )
    return;

  QColor color(aEnemyParams[2].toInt(), aEnemyParams[3].toInt(), aEnemyParams[4].toInt());
  enemy->setColor(color);

  enemy->setTotalLife( aEnemyParams[5].toInt());

  std::map<std::string, std::map<std::string, std::string>> textures;
  textures[aEnemyParams[6].toStdString()] = getPartTextures(7, aEnemyParams );
  textures[aEnemyParams[19].toStdString()] = getPartTextures(20, aEnemyParams );
  textures[aEnemyParams[32].toStdString()] = getPartTextures(33, aEnemyParams );
  textures[aEnemyParams[45].toStdString()] = getPartTextures(46, aEnemyParams );
  textures[aEnemyParams[58].toStdString()] = getPartTextures(59, aEnemyParams );
  textures[aEnemyParams[71].toStdString()] = getPartTextures(72, aEnemyParams );

  enemy->setTextures( textures );

  enemy->setPoints( aEnemyParams[85].toInt());
  
  addEnemy(enemy);
}

std::map<std::string, std::string>
OmgEnemyContainer::getPartTextures( int beginIndex, QStringList aEnemyParams )
{
  std::map<std::string, std::string> partTextures;
  partTextures[aEnemyParams[beginIndex].toStdString()]    = aEnemyParams[beginIndex+1].toStdString();
  partTextures[aEnemyParams[beginIndex+2].toStdString()]  = aEnemyParams[beginIndex+3].toStdString();
  partTextures[aEnemyParams[beginIndex+4].toStdString()]  = aEnemyParams[beginIndex+5].toStdString();
  partTextures[aEnemyParams[beginIndex+6].toStdString()]  = aEnemyParams[beginIndex+7].toStdString();
  partTextures[aEnemyParams[beginIndex+8].toStdString()]  = aEnemyParams[beginIndex+9].toStdString();
  partTextures[aEnemyParams[beginIndex+10].toStdString()] = aEnemyParams[beginIndex+11].toStdString();
  return partTextures;
}