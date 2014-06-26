#include "QOmgPopUp.h"
#include "ui_QOmgPopUp.h"
#include "QOmgStyle.h"
#include <QCursor>
#include <QDir>
#include "QOmgDialogEnemy.h"
#include "QOmgDialogPlayer.h"
#include "OmgEntities/OmgPlayerContainer.h"
#include "OmgEntities/OmgEnemyContainer.h"
#include "OmgEntities/OmgItemContainer.h"
#include "OmgEntities/OmgSceneObjContainer.h"
#include "OmgEntities/OmgWeaponsContainer.h"
#include "Saver/OmgSaverMngr.h"
#include "QOmgWindowMngr.h"
#include <QDesktopWidget>
#include <QMenu>
#include <QMessageBox>
#include "Input/InputManager.h"
#include "Input/MouseScenaryEdit.h"
#include <QDebug>
#include "OmgEntities/OmgGameContainer.h"
#include "OmgEntities/OmgMapContainer.h"


QOmgPopUp::QOmgPopUp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QOmgPopUp)
{
    ui->setupUi(this);
    setStyleSheet(QOmgStyle::CurrentStyleSheet());

}

QOmgPopUp::~QOmgPopUp()
{
    delete ui;
}

void
QOmgPopUp::ShowPopUp(bool a_exist , Omega::LeafType a_type, QString a_name, QPoint a_pos)
{

    setWindowFlags(Qt::Popup);

    QMenu *menu = new QMenu();
    menu->setMinimumWidth(118);

    if( a_exist )
    {
        actionNew = new QAction(menu);
        actionNew->setIcon( QIcon(":/OmegaEditor/Resources/Icons/add.png"));
        actionNew->setText("Copy");
        menu->addAction(actionNew);
        connect(actionNew, SIGNAL(triggered()), this, SLOT(on_New_clicked()));

        actionEdit = new QAction(menu);
        actionEdit->setIcon( QIcon(":/OmegaEditor/Resources/Icons/edit.png"));
        actionEdit->setText("Edit");
        menu->addAction(actionEdit);
        connect(actionEdit, SIGNAL(triggered()), this, SLOT(on_Edit_clicked()));

        actionDelete = new QAction(menu);
        actionDelete->setIcon( QIcon(":/OmegaEditor/Resources/Icons/delete.png"));
        actionDelete->setText("Delete");
        menu->addAction(actionDelete);
        connect(actionDelete, SIGNAL(triggered()), this, SLOT(on_Delete_clicked()));
    } else {

        actionNew = new QAction(menu);
        actionNew->setIcon( QIcon(":/OmegaEditor/Resources/Icons/add.png"));
        actionNew->setText("New");
        menu->addAction(actionNew);
        connect(actionNew, SIGNAL(triggered()), this, SLOT(on_New_clicked()));
    }

    ui->_layout_actions->addWidget( menu );

    _type = a_type;
    switch (a_type)
    {
    case Omega::FolderLeaf:
        ui->icon->setPixmap(QPixmap(":Media/folder.png"));
        break;
    case Omega::PlayerLeaf:
        ui->icon->setPixmap(QPixmap(":Media/character.png"));
        break;
    case Omega::EnemyLeaf:
        ui->icon->setPixmap(QPixmap(":Media/enemy.png"));
        break;
    case Omega::ItemLeaf:
        ui->icon->setPixmap(QPixmap(":Media/item.png"));
        break;
    case Omega::SceneObjLeaf:
        ui->icon->setPixmap(QPixmap(":Media/sceneobj.png"));
        break;
    case Omega::WeaponLeaf:
        ui->icon->setPixmap(QPixmap(":Media/gun.png"));
        break;
    case Omega::MapLeaf:
        ui->icon->setPixmap(QPixmap(":Media/map.png"));
        break;
    case Omega::GameLeaf:
        ui->icon->setPixmap(QPixmap(":Media/game.png"));
        break;
    default:
        break;
    }

    _name = a_name;
    ui->entity_name->setText(a_name);

    show();
    move(a_pos);
    adjustSize();
}


void QOmgPopUp::on_New_clicked()
{
    switch (_type)
    {
    case Omega::FolderLeaf:
        QOmgWindowMngr::Instance()->GetMainWindow()->on_actionNew_Folder_triggered();
        break;
    case Omega::PlayerLeaf:
        QOmgWindowMngr::Instance()->GetMainWindow()->on_actionNew_Player_triggered();
        break;
    case Omega::EnemyLeaf:
        QOmgWindowMngr::Instance()->GetMainWindow()->on_actionNew_Enemy_triggered();
        break;
    case Omega::ItemLeaf:
        QOmgWindowMngr::Instance()->GetMainWindow()->on_actionNew_Item_triggered();
        break;
    case Omega::SceneObjLeaf:
        QOmgWindowMngr::Instance()->GetMainWindow()->on_actionNew_Scene_Object_triggered();
        break;
    case Omega::WeaponLeaf:
        QOmgWindowMngr::Instance()->GetMainWindow()->on_actionNew_Weapon_triggered();
        break;
    case Omega::MapLeaf:
        QOmgWindowMngr::Instance()->GetMainWindow()->on_actionNew_Map_triggered();
        break;
    case Omega::GameLeaf:
         QOmgWindowMngr::Instance()->GetMainWindow()->on_actionNewGame_triggered();
         break;
    default:
        break;
    }

    hide();
    deleteLater();
}

void QOmgPopUp::on_Edit_clicked()
{

    MouseScenaryEdit * mouseEdit = dynamic_cast<MouseScenaryEdit*>(InputManager::getInstance()->getController("EditScenary"));
    if(mouseEdit)
    {
        QString objectName = QString().fromStdString(mouseEdit->currentObjectName()).remove("0");
        if( _name == objectName )
            QOmgWindowMngr::Instance()->GetMainWindow()->deselectCurrentObj();
    }

    switch (_type)
    {
    case Omega::FolderLeaf:
    {
        OmgFolder* p_folder = OmgFoldersMngr::Instance()->getFolder(_name);
        QOmgWindowMngr::Instance()->GetMainWindow()->on_actionEdit_Folder_triggered(p_folder);
        break;
    }
    case Omega::PlayerLeaf:
    {
        OmgPlayer* player = OmgPlayerContainer::Instance()->getPlayer(_name);
        QOmgWindowMngr::Instance()->GetMainWindow()->on_actionEdit_Player_triggered(player);
        break;
    }
    case Omega::EnemyLeaf:
    {
        OmgEnemy* enemy = OmgEnemyContainer::Instance()->getEnemy(_name);
        QOmgWindowMngr::Instance()->GetMainWindow()->on_actionEdit_Enemy_triggered(enemy);
        break;
    }
    case Omega::ItemLeaf:   
    {
        OmgItem* pItem = OmgItemContainer::Instance()->getItem(_name);
        QOmgWindowMngr::Instance()->GetMainWindow()->on_actionEdit_Item_triggered(pItem);
        break;   
    }
    case Omega::SceneObjLeaf:
    {
        OmgSceneObj* pObject = OmgSceneObjContainer::Instance()->getSceneObj(_name);
        QOmgWindowMngr::Instance()->GetMainWindow()->on_actionEdit_Scene_Object_triggered(pObject);
        break;
    }
    case Omega::WeaponLeaf:
    {
        OmgWeapon* pWeapon = OmgWeaponsContainer::Instance()->getWeapon(_name );
        QOmgWindowMngr::Instance()->GetMainWindow()->on_actionEdit_Weapon_triggered(pWeapon);
        break;
    }
    case Omega::MapLeaf:
    {
        OmgMap* pMap = OmgMapContainer::Instance()->getMap(_name);
        QOmgWindowMngr::Instance()->GetMainWindow()->on_actionEdit_Map_triggered(pMap);
        break;
    }
    case Omega::GameLeaf:
      {
        OmgGame* pGame = OmgGameContainer::Instance()->getGame(_name);
        QOmgWindowMngr::Instance()->GetMainWindow()->on_actionEditGame_triggered(pGame);
        break;
      }

    default:
        break;
    }

    hide();
    deleteLater();
}

void QOmgPopUp::on_Delete_clicked()
{
    MouseScenaryEdit * mouseEdit = dynamic_cast<MouseScenaryEdit*>(InputManager::getInstance()->getController("EditScenary"));

    if(mouseEdit)
    {
        QString objectName = QString().fromStdString(mouseEdit->currentObjectName()).remove("0");
        qDebug()<< objectName;
        if( _name == objectName )
            QOmgWindowMngr::Instance()->GetMainWindow()->deselectCurrentObj();
    }

    switch (_type)
    {
    case Omega::FolderLeaf:
        DeleteFolder(_name);
        break;
    case Omega::PlayerLeaf:
        OmgPlayerContainer::Instance()->deletePlayer(_name);
        break;
    case Omega::EnemyLeaf:
        OmgEnemyContainer::Instance()->deleteEnemy(_name);
        break;
    case Omega::ItemLeaf:
        OmgItemContainer::Instance()->deleteItem(_name);
        break;
    case Omega::SceneObjLeaf:
        OmgSceneObjContainer::Instance()->DeleteObject(_name);
        break;
    case Omega::WeaponLeaf:
        OmgWeaponsContainer::Instance()->deleteWeapon(_name);
        break;
    case Omega::MapLeaf:
        OmgMapContainer::Instance()->deleteMap(_name);
        break;
    case Omega::GameLeaf:
      {
        OmgGameContainer::Instance()->deleteGame(_name);
        if( QDir(_name).exists() )
          QDir().rmdir(_name);
      }
      break;
    default:
        break;
    }

    QOmgWindowMngr::Instance()->GetMainWindow()->UpdateWidgets();
    OmgSaverMngr::Instance()->entityDeleted();

    hide();
    deleteLater();
}

void
QOmgPopUp::DeleteFolder(QString a_name)
{
    OmgFolder* p_folder = OmgFoldersMngr::Instance()->getFolder(a_name);

    if(!p_folder)
        return;

    if(p_folder->isDefault())
    {
        QMessageBox::warning(this,
                             "Error!!",
                             "A default folder can not be deleted...");
        return;
    }

    switch(p_folder->getType())
    {
    case Omega::PlayerFolder:
    {
        Omega::EntityVector vPlayers =  OmgPlayerContainer::Instance()->playersInFolder( a_name );
        Omega::EntityIterator it = vPlayers.begin(), it_end = vPlayers.end();
        for(; it != it_end ; ++it)
        {
            OmgEntity* Player = (*it);
            OmgPlayerContainer::Instance()->deletePlayer( Player->getName() );
        }

        break;
    }
    case Omega::EnemyFolder:
    {
        Omega::EntityVector vEnemies = OmgEnemyContainer::Instance()->enemiesInFolder( a_name );
        Omega::EntityIterator it = vEnemies.begin(), it_end = vEnemies.end();
        for(; it != it_end ; ++it)
        {
            OmgEntity* Enemy = (*it);
            OmgEnemyContainer::Instance()->deleteEnemy(Enemy->getName() );
        }
        break;
    }
    case Omega::ItemFolder:
    {
        Omega::EntityVector vItems = OmgItemContainer::Instance()->itemsInFolder( a_name );
        Omega::EntityIterator it = vItems.begin(), it_end = vItems.end();
        for(; it != it_end ; ++it)
        {
            OmgEntity* item = (*it);
            OmgItemContainer::Instance()->deleteItem(item->getName() );
        }
        break;
    }
    case Omega::SceneObjFolder:
    {
        Omega::EntityVector vObjects = OmgEnemyContainer::Instance()->enemiesInFolder( a_name );
        Omega::EntityIterator it = vObjects.begin(), it_end = vObjects.end();
        for(; it != it_end ; ++it)
        {
            OmgEntity* Enemy = (*it);
            OmgEnemyContainer::Instance()->deleteEnemy(Enemy->getName() );
        }
        break;
    }
    case Omega::WeaponFolder:
      {
        Omega::EntityVector vWeapon = OmgWeaponsContainer::Instance()->weaponsInFolder( a_name );
        Omega::EntityIterator it = vWeapon.begin(), it_end = vWeapon.end();
        for(; it != it_end ; ++it)
        {
          OmgEntity* weapon = (*it);
          OmgEnemyContainer::Instance()->deleteEnemy(weapon->getName() );
        }
        break;
      }
    case Omega::MapFolder:
      {
        Omega::EntityVector vMaps = OmgMapContainer::Instance()->mapsInFolder(a_name);
        Omega::EntityIterator it = vMaps.begin(), it_end = vMaps.end();
        for(; it != it_end ; ++it)
        {
          OmgEntity* map = (*it);
          OmgMapContainer::Instance()->deleteMap(map->getName() );
        }
        break;
      }
    case Omega::GameFolder:
      {
        Omega::EntityVector vGame = OmgGameContainer::Instance()->gamesInFolder(a_name);
        Omega::EntityIterator it = vGame.begin(), it_end = vGame.end();
        for(; it != it_end ; ++it)
        {
          OmgEntity* game = (*it);
          OmgMapContainer::Instance()->deleteMap(game->getName() );
        }
        break;
      }
    }

    OmgFoldersMngr::Instance()->deleteFolder(_name);
}
