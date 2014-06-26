#include "QOmgLeaf.h"
#include "./QOmgPopUp.h"

#include "OmgEntities/OmgPlayerContainer.h"
#include "OmgEntities/OmgEnemyContainer.h"
#include "OmgEntities/OmgSceneObjContainer.h"
#include "OmgEntities/OmgItemContainer.h"
#include "OmgEntities/OmgWeaponsContainer.h"
#include "OmgEntities/OmgMapContainer.h"
#include "OmgEntities/OmgGameContainer.h"

// QT Stuff
#include <QDrag>
#include <QMimeData>
#include <QByteArray>
#include <QDataStream>
#include <QApplication>




QOmgLeaf::QOmgLeaf(QTreeWidget* ap_parent,
                   Omega::LeafType a_type,
                   QString a_name,
                   QIcon a_icon) : QTreeWidgetItem( ap_parent )
{
    setText(0,a_name);
    entity_name = a_name;
    setIcon(0,a_icon);
    icon = a_icon;
    _type = a_type;
}

QOmgLeaf::QOmgLeaf(QTreeWidgetItem* ap_parent,
                   Omega::LeafType a_type,
                   QString a_name,
                   QIcon a_icon) : QTreeWidgetItem( ap_parent )
{
    setText(0,a_name);
    entity_name = a_name;
    setIcon(0,a_icon);
    icon = a_icon;
    _type = a_type;
}

void
QOmgLeaf::ShowPopUp( QPoint point )
{
    bool exist(false);

    switch (_type)
    {
    case Omega::FolderLeaf:
        exist = true;
        break;
    case Omega::PlayerLeaf:
        exist = (OmgPlayerContainer::Instance()->getPlayer(entity_name) != NULL );
        break;
    case Omega::EnemyLeaf:
       exist = (OmgEnemyContainer::Instance()->getEnemy(entity_name) != NULL );
        break;
    case Omega::ItemLeaf:
        exist = (OmgItemContainer::Instance()->getItem(entity_name) != NULL );
        break;
    case Omega::SceneObjLeaf:
        exist = (OmgSceneObjContainer::Instance()->getSceneObj(entity_name) != NULL );
        break;
    case Omega::WeaponLeaf:
        exist = (OmgWeaponsContainer::Instance()->getWeapon(entity_name) != NULL ) ;
        break;
	  case Omega::MapLeaf:
		    exist = (OmgMapContainer::Instance()->getMap(entity_name) != NULL ) ;
		    break;
	  case Omega::GameLeaf:
		    exist = (OmgGameContainer::Instance()->getGame(entity_name) != NULL ) ;
		    break;
    default:
        return;
        break;
    }

    QOmgPopUp *pop_up = new QOmgPopUp();
    pop_up->ShowPopUp( exist, _type, entity_name, point );
}

Omega::LeafType
QOmgLeaf::GetLeafType()
{
    return _type;
}

QString
QOmgLeaf::GetLeafName()
{
    return entity_name;
}
