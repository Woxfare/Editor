#include "QOmgTreeEntities.h" // Base Class

#include "Omega.h"
#include "OmgEntities/OmgSceneObjContainer.h"
#include "OmgEntities/OmgEnemyContainer.h"
#include "OmgEntities/OmgPlayerContainer.h"
#include "OmgEntities/OmgItemContainer.h"
#include "OmgEntities/OmgSceneObjContainer.h"
#include "OmgEntities/OmgWeaponsContainer.h"
#include "OmgEntities/OmgMapContainer.h"
#include "OmgEntities/OmgPlayer.h"
#include "OmgEntities/OmgGameContainer.h"
#include "OmgEntities/OmgGame.h"
#include "OmgEntities/OmgWeapon.h"


// Qt Stuff
#include "QOmgStyle.h"
#include "QOmgLeaf.h"
#include <QCursor>

QOmgTreeEntities::QOmgTreeEntities(QWidget *parent) :
    QOmgTree( parent )
{
  setStyleSheet(QOmgStyle::CurrentStyleSheet());

  //! Add the entities to the tree
  AddPlayersToTheTree();
  AddEnemiesToTheTree();
  AddItemsToTheTree();
  AddSceneObjectsToTheTree();
  addWeaponsToTheTree();
  addMapsToTheTree();
  addGamesToTheTree();
}

QOmgTreeEntities::~QOmgTreeEntities(){}

void
QOmgTreeEntities::addGamesToTheTree( void )
{
    //! Make the root item
    QOmgLeaf* pItem = new QOmgLeaf( this,
                                    Omega::GameLeaf,
                                    QString("Games"),
                                    QIcon(":/OmegaEditor/Resources/Icons/game.png"));
    pushGames( pItem );

    addTopLevelItem(pItem);
}

void
QOmgTreeEntities::pushGames(QTreeWidgetItem *pItem)
{
  // Get the available scene objects
  Omega::EntityVector vGames = OmgGameContainer::Instance()->availableGames();
  Omega::EntityIterator it = vGames.begin(), it_end = vGames.end();

  //! Sort all the items in folders and add the scene hierarchy
  std::map<QString, QOmgLeaf*> _mapFolders;

  for( ; it != it_end; ++it)
  {
    OmgGame* pGame = dynamic_cast<OmgGame*>(*it);

    QString folder_name = "Default";

    if(pGame)
      folder_name = pGame->getFolderName();

    QOmgLeaf* pLeafFolder;

    if( _mapFolders.find(folder_name) != _mapFolders.end())
    {
      pLeafFolder = _mapFolders[folder_name];
    } else {

      pLeafFolder = new QOmgLeaf( pItem, Omega::FolderLeaf, folder_name, QIcon(":Media/folder.png"));
      _mapFolders[folder_name] = pLeafFolder;
    }

      // New node with the item information
      QOmgLeaf *pLeafChild = new QOmgLeaf( pLeafFolder,
                                           Omega::GameLeaf,
                                           pGame->getName(),
                                           QIcon(":/OmegaEditor/Resources/Icons/game.png"));
  }
}

void
QOmgTreeEntities::addMapsToTheTree( void )
{
    //! Make the root item
    QOmgLeaf* pItem = new QOmgLeaf(this,
                                    Omega::MapLeaf,
                                    QString("Maps"),
                                    QIcon(":/OmegaEditor/Resources/Icons/map.png"));
    pushMaps( pItem );

    addTopLevelItem(pItem);
}

void
QOmgTreeEntities::pushMaps(QTreeWidgetItem *pItem)
{
    // Get the available scene objects
    Omega::EntityVector vMaps = OmgMapContainer::Instance()->availableMaps();
    Omega::EntityIterator it = vMaps.begin(), it_end = vMaps.end();

    //! Sort all the items in folders and add the scene hierarchy
    std::map<QString, QOmgLeaf*> _mapFolders;

    for( ; it != it_end; ++it)
    {
        OmgMap* pMap = dynamic_cast<OmgMap*>(*it);

        QString folder_name = "Default";

        if(pMap)
            folder_name = pMap->getFolderName();

        QOmgLeaf* pLeafFolder;

        if( _mapFolders.find(folder_name) != _mapFolders.end())
        {
            pLeafFolder = _mapFolders[folder_name];

        } else {

            pLeafFolder = new QOmgLeaf( pItem, Omega::FolderLeaf, folder_name, QIcon(":Media/folder.png"));
            _mapFolders[folder_name] = pLeafFolder;

        }

        // New node with the item information
        QOmgLeaf *pLeafChild = new QOmgLeaf( pLeafFolder,
                                             Omega::MapLeaf,
                                             pMap->getName(),
                                             QIcon(":/OmegaEditor/Resources/Icons/map.png"));
    }
}

void
QOmgTreeEntities::addWeaponsToTheTree( void )
{
    //! Make the root item
    QOmgLeaf* pItem = new QOmgLeaf(this,
                                    Omega::WeaponLeaf,
                                    QString("Weapons"),
                                    QIcon(":/OmegaEditor/Resources/Icons/gun.png"));
    pushWeapons( pItem );

    addTopLevelItem(pItem);
}

void
QOmgTreeEntities::pushWeapons(QTreeWidgetItem *pItem)
{
    //! Get the available scene objects
    Omega::EntityVector vWeapons = OmgWeaponsContainer::Instance()->availableWeapons();
    Omega::EntityIterator it = vWeapons.begin(), it_end = vWeapons.end();

    //! Sort all the items in folders and add the scene hierarchy
    std::map<QString, QOmgLeaf*> _mapFolders;

    for( ; it != it_end; ++it)
    {
        OmgWeapon* pWeapon = dynamic_cast<OmgWeapon*>(*it);

        QString folder_name = "Default";

        if(pWeapon)
            folder_name = pWeapon->getFolderName();

        QOmgLeaf* pLeafFolder;

        if( _mapFolders.find(folder_name) != _mapFolders.end())
        {
            pLeafFolder = _mapFolders[folder_name];

        } else {

            pLeafFolder = new QOmgLeaf( pItem, Omega::FolderLeaf, folder_name,QIcon(":Media/folder.png"));
            _mapFolders[folder_name] = pLeafFolder;

        }

        //! New node with the item information
        QOmgLeaf *pLeafChild = new QOmgLeaf( pLeafFolder,
                                             Omega::WeaponLeaf,
                                             pWeapon->getName(),
                                             QIcon(":/OmegaEditor/Resources/Icons/gun.png"));
    }
}

void
QOmgTreeEntities::AddSceneObjectsToTheTree( void )
{

    //! Make the root item
    QOmgLeaf* p_item = new QOmgLeaf(this,
                                    Omega::SceneObjLeaf,
                                    QString("Objects"),
                                    QIcon(":/OmegaEditor/Resources/Icons/sceneobj.png"));
    PushSceneObj(p_item);

    addTopLevelItem(p_item);
}

void
QOmgTreeEntities::PushSceneObj(QTreeWidgetItem *p_item)
{
    //! Get the available scene objects
    Omega::EntityVector v_objects = OmgSceneObjContainer::Instance()->GetAvailableSceneObjects();
    Omega::EntityIterator it = v_objects.begin(), it_end = v_objects.end();

    //! Sort all the items in folders and add the scene heirarchy
    std::map<QString, QOmgLeaf*> _map_scene_obj;

    for( ; it != it_end; ++it)
    {
        OmgSceneObj* p_obj = dynamic_cast<OmgSceneObj*>(*it);

        if(p_obj->getName()=="ObjectName")
            continue;

        QString folder_name = "Default";

        if(p_obj)
            folder_name = p_obj->getFolderName();

        QOmgLeaf* p_tree_folder;

        if( _map_scene_obj.find(folder_name) != _map_scene_obj.end())
        {
            p_tree_folder = _map_scene_obj[folder_name];

        } else {

            p_tree_folder = new QOmgLeaf(p_item, Omega::FolderLeaf,
                                         folder_name,QIcon(":Media/folder.png"));
            _map_scene_obj[folder_name] = p_tree_folder;

        }
        //! New node with the item information
        QOmgLeaf *p_tree_item = new QOmgLeaf(p_tree_folder,
                                             Omega::SceneObjLeaf,
                                             p_obj->getName(),
                                             QIcon(p_obj->getPixmap()));
    }
}

void
QOmgTreeEntities::AddEnemiesToTheTree( void )
{
    //! Make the root item
    QOmgLeaf* p_item = new QOmgLeaf(this,
                                    Omega::EnemyLeaf,
                                    QString("Enemies"),
                                    QIcon(":/OmegaEditor/Resources/Icons/enemy.png") );
    PushEnemies(p_item);

    addTopLevelItem(p_item);
}

void
QOmgTreeEntities::PushEnemies( QTreeWidgetItem *p_item )
{
    //! Get the available scene objects
    Omega::EntityVector v_objects = OmgEnemyContainer::Instance()->availableEnemies();
    Omega::EntityIterator it = v_objects.begin(), it_end = v_objects.end();

    //! Sort all the items in folders and add the scene heirarchy
    std::map<QString, QOmgLeaf*> _map_scene_obj;

    for( ; it != it_end; ++it)
    {
        OmgEnemy* p_obj = dynamic_cast<OmgEnemy*>(*it);

        QString folder_name = "Default";

        if(p_obj)
            folder_name = p_obj->getFolderName();

        QOmgLeaf* p_tree_folder;

        if( _map_scene_obj.find(folder_name) != _map_scene_obj.end())
        {
            p_tree_folder = _map_scene_obj[folder_name];

        } else {

            p_tree_folder = new QOmgLeaf(p_item,
                                         Omega::FolderLeaf,
                                         folder_name,QIcon(":Media/folder.png"));
            _map_scene_obj[folder_name] = p_tree_folder;

        }
        //! New node with the item information
        QOmgLeaf *p_tree_item = new QOmgLeaf(p_tree_folder,
                                             Omega::EnemyLeaf,
                                             p_obj->getName(),
                                             QIcon(p_obj->getPixmap()));
    }
}

void
QOmgTreeEntities::AddPlayersToTheTree( void )
{

    //! Make the root item
    QOmgLeaf* p_item = new QOmgLeaf(this, Omega::PlayerLeaf,QString("Players"), QIcon(":/OmegaEditor/Resources/Icons/character.png") );

    PushPlayers(p_item);

    addTopLevelItem(p_item);
}

void
QOmgTreeEntities::PushPlayers(QTreeWidgetItem *p_item)
{
    //! Get the available scene objects
    Omega::EntityVector v_objects = OmgPlayerContainer::Instance()->availablePlayers();
    Omega::EntityIterator it = v_objects.begin(), it_end = v_objects.end();


    //! Sort all the items in folders and add the scene hierarchy
    std::map<QString, QOmgLeaf*> _map_scene_obj;

    for( ; it != it_end; ++it)
    {
        OmgPlayer* p_obj = dynamic_cast<OmgPlayer*>(*it);

        QString folder_name = "Default";

        if(p_obj)
            folder_name = p_obj->getFolderName();

        QOmgLeaf* p_tree_folder;

        if( _map_scene_obj.find(folder_name) != _map_scene_obj.end())
        {
            p_tree_folder = _map_scene_obj[folder_name];

        } else {

            p_tree_folder = new QOmgLeaf(p_item, Omega::FolderLeaf,folder_name,QIcon(":Media/folder.png"));
            _map_scene_obj[folder_name] = p_tree_folder;

        }
        //! New node with the item information
        QOmgLeaf *p_tree_item = new QOmgLeaf(p_tree_folder, Omega::PlayerLeaf, p_obj->getName(), QIcon(p_obj->getPixmap()));
    }
}

void
QOmgTreeEntities::AddItemsToTheTree( void )
{
    //! Make the root item
    QOmgLeaf* p_item = new QOmgLeaf(this, Omega::ItemLeaf,QString("Items"),QIcon(":/OmegaEditor/Resources/Icons/item.png"));

    PushItems(p_item);

    addTopLevelItem(p_item);
}

void
QOmgTreeEntities::PushItems(QTreeWidgetItem *p_item)
{
    //! Get the available scene objects
    Omega::EntityVector v_objects = OmgItemContainer::Instance()->availableItems();
    Omega::EntityIterator it = v_objects.begin(), it_end = v_objects.end();

    //! Sort all the items in folders and add the scene hierarchy
    std::map<QString, QOmgLeaf*> _map_scene_obj;

    for( ; it != it_end; ++it)
    {
        OmgItem* p_obj = dynamic_cast<OmgItem*>(*it);
        if(p_obj->getName()=="ItemName")
            continue;

        QString folder_name = "Default";

        if(p_obj)
            folder_name = p_obj->getFolderName();

        QOmgLeaf* p_tree_folder;

        if( _map_scene_obj.find(folder_name) != _map_scene_obj.end())
        {
            p_tree_folder = _map_scene_obj[folder_name];

        } else {

            p_tree_folder = new QOmgLeaf(p_item, Omega::FolderLeaf,folder_name,QIcon(":Media/folder.png"));
            _map_scene_obj[folder_name] = p_tree_folder;

        }
        //! New node with the item information
        QOmgLeaf *p_tree_item = new QOmgLeaf(p_tree_folder, Omega::ItemLeaf, p_obj->getName(), QIcon(p_obj->getPixmap()));
    }
}

void
QOmgTreeEntities::UpdateTree( OmgEntity* p_entity )
{
    OmgPlayer* pPlayer = dynamic_cast<OmgPlayer*>(p_entity);
    OmgEnemy* pEnemy = dynamic_cast<OmgEnemy*>(p_entity);
    OmgItem* pItem = dynamic_cast<OmgItem*>(p_entity);
    OmgSceneObj* pSceneObj = dynamic_cast<OmgSceneObj*>(p_entity);
    OmgWeapon* pWeapon = dynamic_cast<OmgWeapon*>(p_entity);
    OmgGame* pGame = dynamic_cast<OmgGame*>(p_entity);
    OmgMap* pMap = dynamic_cast<OmgMap*>(p_entity);

    QTreeWidgetItem* p_root_item;
    if(pPlayer)
    {
        p_root_item = topLevelItem(0);
        qDeleteAll(p_root_item->takeChildren());
        PushPlayers(p_root_item);

    } else if( pEnemy )
    {
        p_root_item = topLevelItem(1);
        qDeleteAll(p_root_item->takeChildren());
        PushEnemies(p_root_item);
    } else if( pItem )
    {
        p_root_item = topLevelItem(2);
        qDeleteAll(p_root_item->takeChildren());
        PushItems(p_root_item);
    } else if( pSceneObj )
    {
        p_root_item = topLevelItem(3);
        qDeleteAll( p_root_item->takeChildren() );
        PushSceneObj( p_root_item);
    } else if( pWeapon )
    {
        p_root_item = topLevelItem(4);
        qDeleteAll( p_root_item->takeChildren() );
        pushWeapons( p_root_item );
    } else if( pMap )
    {
      p_root_item = topLevelItem(5);
      qDeleteAll( p_root_item->takeChildren() );
      pushMaps( p_root_item );
    } else if( pGame )
    {
      p_root_item = topLevelItem(6);
      qDeleteAll( p_root_item->takeChildren() );
      pushGames( p_root_item );
    }
}

void
QOmgTreeEntities::UpdateTree(  )
{
    qDeleteAll( topLevelItem(0)->takeChildren());
    qDeleteAll( topLevelItem(1)->takeChildren());
    qDeleteAll( topLevelItem(2)->takeChildren());
    qDeleteAll( topLevelItem(3)->takeChildren());
    qDeleteAll( topLevelItem(4)->takeChildren());
    qDeleteAll( topLevelItem(5)->takeChildren());
    qDeleteAll( topLevelItem(6)->takeChildren());
    PushPlayers(topLevelItem(0));
    PushEnemies(topLevelItem(1));
    PushItems(topLevelItem(2));
    PushSceneObj(topLevelItem(3));
    pushWeapons(topLevelItem(4));
    pushMaps(topLevelItem(5));
    pushGames(topLevelItem(6));
}
