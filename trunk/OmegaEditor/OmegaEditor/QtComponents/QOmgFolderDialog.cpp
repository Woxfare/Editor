#include "QOmgFolderDialog.h"

// Qt Stuff
#include "ui_QOmgFolderDialog.h"
#include "QOmgStyle.h"
#include <QMessageBox>
#include "./QOmgWindowMngr.h"

#include "Saver/OmgSaverMngr.h"
#include "Display/OgreManager.h"

// Entities
#include "OmgEntities/OmgGameContainer.h"
#include "OmgEntities/OmgEnemyContainer.h"
#include "OmgEntities/OmgEnemy.h"
#include "OmgEntities/OmgPlayerContainer.h"
#include "OmgEntities/OmgPlayer.h"
#include "OmgEntities/OmgItemContainer.h"
#include "OmgEntities/OmgPlayer.h"
#include "OmgEntities/OmgSceneObjContainer.h"
#include "OmgEntities/OmgWeaponsContainer.h"
#include "OmgEntities/OmgMapContainer.h"

QOmgFolderDialog::QOmgFolderDialog(QWidget *apParent) :
    QDialog(apParent),
    ui(new Ui::QOmgFolderDialog)
{
    createWidget();
    mFolder = NULL;
    ui->pbEdit->hide();
    OgreManager::getInstance()->selectScene("EditScenary");
}

QOmgFolderDialog::QOmgFolderDialog(OmgFolder* aFolder, QWidget *aParent) :
    QDialog(aParent),
    ui(new Ui::QOmgFolderDialog)
{
    createWidget();
    mFolder = aFolder;

    ui->lineEdit->setText(aFolder->getName());

    switch (aFolder->getType())
    {
    case Omega::EnemyFolder:
        ui->listWidget->setCurrentRow(0);
    break;
    case Omega::PlayerFolder:
        ui->listWidget->setCurrentRow(1);
    break;
    case Omega::SceneObjFolder:
        ui->listWidget->setCurrentRow(2);
    break;
    case Omega::ItemFolder:
        ui->listWidget->setCurrentRow(3);
    break;
    case Omega::WeaponFolder:
        ui->listWidget->setCurrentRow(4);
        break;
    case Omega::MapFolder:
        ui->listWidget->setCurrentRow(5);
        break;
    case Omega::GameFolder:
        ui->listWidget->setCurrentRow(6);
        break;
    }

    ui->pbNew->hide();

    //! The default folders can not be deleted
    if(aFolder)
    {
        if ( aFolder->isDefault() )
        {
            ui->pbEdit->setEnabled(false);
            ui->pbNew->setEnabled(false);
        }
    }

    OgreManager::getInstance()->selectScene("EditScenary");
}


void
QOmgFolderDialog::createWidget( void )
{
    ui->setupUi(this);
    setStyleSheet(QOmgStyle::CurrentStyleSheet());

    ui->listWidget->addItem( new QListWidgetItem(QIcon(":/Media/enemy.png"), "Enemy Folder"));
    ui->listWidget->addItem( new QListWidgetItem(QIcon(":/Media/character.png"), "Player Folder"));
    ui->listWidget->addItem( new QListWidgetItem(QIcon(":/Media/sceneobj.png"), "Scene Object Folder"));
    ui->listWidget->addItem( new QListWidgetItem(QIcon(":/Media/item.png"), "Item Folder"));
    ui->listWidget->addItem( new QListWidgetItem(QIcon(":/Media/gun.png"), "Weapon Folder"));
    ui->listWidget->addItem( new QListWidgetItem(QIcon(":/Media/map.png"), "Map Folder"));
    ui->listWidget->addItem( new QListWidgetItem(QIcon(":/Media/game.png"), "Game Folder"));
}

QOmgFolderDialog::~QOmgFolderDialog()
{
    delete ui;
}

Omega::FolderType
QOmgFolderDialog::getFolderType()
{
    if( ui->listWidget->currentItem()->text().contains("Weapon", Qt::CaseInsensitive ) )
        return Omega::WeaponFolder;
    if( ui->listWidget->currentItem()->text().contains("Obj", Qt::CaseInsensitive ) )
        return Omega::SceneObjFolder;
    if( ui->listWidget->currentItem()->text().contains("Player", Qt::CaseInsensitive ) )
        return Omega::PlayerFolder;
    if( ui->listWidget->currentItem()->text().contains("Enemy", Qt::CaseInsensitive ) )
        return Omega::EnemyFolder;
    if( ui->listWidget->currentItem()->text().contains("Item", Qt::CaseInsensitive ) )
        return Omega::ItemFolder;
    if( ui->listWidget->currentItem()->text().contains("Map", Qt::CaseInsensitive ) )
        return Omega::MapFolder;
    if( ui->listWidget->currentItem()->text().contains("Game", Qt::CaseInsensitive ) )
        return Omega::GameFolder;

    return Omega::PlayerFolder;
}

void
QOmgFolderDialog::updateEntitiesInFolder(OmgFolder *aFolder)
{
    bool moveToDefFolder( false );
    if( aFolder->getType() != getFolderType())
        moveToDefFolder = true;

    switch( aFolder->getType())
    {
    case Omega::EnemyFolder:
    {
        QString newFolderName(aFolder->getName());
        if(moveToDefFolder)
            newFolderName = "DefaultEnemies";

        changeFolder( newFolderName, OmgEnemyContainer::Instance()->enemiesInFolder( aFolder->getName() ) );
        break;
    }
    case Omega::PlayerFolder:
    {
        QString newFolderName(aFolder->getName());
        if(moveToDefFolder)
            newFolderName = "DefaultPlayers";
        changeFolder( newFolderName, OmgPlayerContainer::Instance()->playersInFolder( aFolder->getName() ));
        break;
    }
    case Omega::ItemFolder:
    {
        QString newFolderName(aFolder->getName());
        if(moveToDefFolder)
            newFolderName = "DefaultItems";
        changeFolder( newFolderName, OmgItemContainer::Instance()->itemsInFolder( aFolder->getName() ));
        break;
    }
    case Omega::SceneObjFolder:
    {
        QString newFolderName(aFolder->getName());
        if(moveToDefFolder)
            newFolderName = "DefaultSceneObj";
        changeFolder( newFolderName, OmgSceneObjContainer::Instance()->sceneObjInFolder( aFolder->getName() ));
        break;
    }
    case Omega::WeaponFolder:
    {
        QString newFolderName(aFolder->getName());
        if(moveToDefFolder)
            newFolderName = "DefaultWeapons";
        changeFolder( newFolderName, OmgWeaponsContainer::Instance()->weaponsInFolder( aFolder->getName() ));
        break;
    }
    case Omega::GameFolder:
    {
        QString newFolderName(aFolder->getName());
        if(moveToDefFolder)
            newFolderName = "DefaultGames";
        changeFolder( newFolderName, OmgGameContainer::Instance()->gamesInFolder(aFolder->getName()));
        break;
    }
    case Omega::MapFolder:
    {
        QString newFolderName(aFolder->getName());
        if(moveToDefFolder)
            newFolderName = "DefaultMaps";
        changeFolder( newFolderName, OmgMapContainer::Instance()->mapsInFolder( aFolder->getName() ));
        break;
    }
    }
}

void
QOmgFolderDialog::on_pbNew_clicked()
{
    if(!validate())
        return;

    mFolder = new OmgFolder(ui->lineEdit->text(), getFolderType());
    OmgFoldersMngr::Instance()->addFolder(mFolder);
    OgreManager::getInstance()->selectScene("EditScenary");

    hide();
    emit HideInputData();
    deleteLater();
}


void
QOmgFolderDialog::on_pbEdit_clicked()
{
    if(!validate())
        return;

    updateEntitiesInFolder( mFolder );

    OmgFoldersMngr::Instance();

    mFolder->setName( ui->lineEdit->text());
    mFolder->setType(getFolderType());

    QOmgWindowMngr::Instance()->GetMainWindow()->UpdateWidgets();
    OgreManager::getInstance()->selectScene("EditScenary");

    hide();
    emit HideInputData();
    deleteLater();
}

bool
QOmgFolderDialog::validate( void )
{
    if(ui->lineEdit->text() == "")
    {
        QMessageBox::warning(this, "Error!!", "Select a Folder Name.");
        return false;
    }

    if(ui->lineEdit->text().contains("Default", Qt::CaseInsensitive))
    {
      QMessageBox::warning(this, "Error!!", "The Default Folders Already Exist!!!");
      return false;
    }

    if(OmgFoldersMngr::Instance()->getFolder(ui->lineEdit->text()))
    {
        QMessageBox::warning(this, "Error!!", "The Folder Already Exist!!.");
        return false;
    }

    if(!ui->listWidget->currentItem())
    {
        QMessageBox::warning(this, "Error!!", " The folder needs a type.");
        return false;
    }

    return true;
}


void QOmgFolderDialog::on_pbCancel_clicked()
{
    hide();
    emit HideInputData();
    deleteLater();
}

void
QOmgFolderDialog::changeFolder(QString name, Omega::EntityVector vEntities)
{
    Omega::EntityIterator it = vEntities.begin(), it_end = vEntities.end();

    for(; it != it_end ; ++it)
    {
        OmgEntity* entity = (*it);
        entity->setFolderName(name);
    }
}
