#include "QOmgDialogPlayer.h"
#include "OmgEntities/OmgPlayerContainer.h"
#include <QMessageBox>
#include "QColorButton.h"
#include "QOmgWindowMngr.h"
#include <QList>
#include <QListWidgetItem>
#include "Saver/OmgSaverMngr.h"
#include "Utils/OgreManager.h"
#include "EditionManagers/EditCharacterManager.h"
#include "OmgEntities/OmgWeapon.h"
#include "OmgEntities/OmgWeaponsContainer.h"

QOmgDialogPlayer::QOmgDialogPlayer(QWidget *ap_parent ):
                  QOmgDialogCharacter( ap_parent, false )
{
    ChangeWidgetsForPlayer();
    _p_player = new OmgPlayer("PlayerName", "DefaultPlayers");
    putPlayerInQt();
    EditCharacterManager::getInstance()->clearCharacter();
}

QOmgDialogPlayer::QOmgDialogPlayer( QWidget* ap_parent , OmgPlayer* ap_player ):
                  QOmgDialogCharacter(ap_parent, true)
{
    ChangeWidgetsForPlayer();
    _p_player = ap_player;
    putPlayerInQt();
    EditCharacterManager::getInstance()->setEditCharacter(ap_player->getTextures());
    int rgb[3] = {
      ap_player->getColor().red(),
      ap_player->getColor().green(),
      ap_player->getColor().blue()
    };
    EditCharacterManager::getInstance()->changeCharacterColor( rgb );
}

void
QOmgDialogPlayer::on__new_char_clicked( void )
{
  if(OmgPlayerContainer::Instance()->getPlayer(_p_player->getName()))
  {
    QMessageBox::warning(this,"Error!!", "The player already exist, select another name");
    return;
  }

  if( Validate() )
      storeAndFinish( createPlayer( ));
}

void
QOmgDialogPlayer::on__edit_char_clicked()
{
     if( Validate() )
     {
       OmgPlayerContainer::Instance()->deletePlayer(_p_player->getName());
       storeAndFinish( createPlayer( ));
     }
}

bool
QOmgDialogPlayer::Validate( void )
{
    // Fill the player data
    QString name = ui->_name->text();

    if( name == "" )
    {
        QMessageBox::warning(this, "Error!!", "Select a name for the player");
        return false;
    }

    if( name == "PlayerName" )
    {
      QMessageBox::warning(this, "Error!!", "Select another name" );
      return false;
    }
    
    QListWidgetItem * p_item = ui->listWidget->currentItem();
    if(p_item)
        _folder = p_item->text();
    else
        _folder = "";

    if( _folder == "")
    {
        QMessageBox::warning(this, "Error!!","Select a folder to store the player");
        return false;
    }

    if( ui->_life->value() == 0 )
    {
        QMessageBox::warning(this, "Error!!", "The character will be difficult to survive if it only has 0 points of life ...");
        return false;
    }

    if( !ui->weaponList->currentItem() )
    {
      QMessageBox::warning( this, "Error!!","Select a weapon for the player" );
      return false;
    }

    return true;

}

void
QOmgDialogPlayer::putPlayerInQt( void )
{
    if(!_p_player)
        return;

    //! Name
    ui->_name->setText(_p_player->getName());

    //! Life
    ui->_life->setValue(_p_player->getTotalLife());

    //! Folder
    ui->listWidget->setCurrentItem( getListItem( _p_player->getFolderName(), ui->listWidget ));

    //! Weapon
	ui->weaponList->setSelectionMode(QAbstractItemView::MultiSelection);

    FillListWidget( OmgWeaponsContainer::Instance()->availableWeapons(), ui->weaponList );

	_color_button->changeColor( _p_player->getColor() );
}

QListWidgetItem*
QOmgDialogPlayer::findFolderItemByName(QString aName)
{
    QList<QListWidgetItem*> vItems = ui->listWidget->findItems(aName, Qt::MatchCaseSensitive );

    if(vItems.isEmpty())
        return NULL;

    return vItems.first();
}


void
QOmgDialogPlayer::storeAndFinish( OmgPlayer* apPlayer )
{
  OmgPlayerContainer::Instance()->addPlayer(apPlayer);
  QOmgWindowMngr::Instance()->GetMainWindow()->UpdateWidgets( apPlayer );
  OmgSaverMngr::Instance()->addEntityToSave( apPlayer );
  QOmgDialogCharacter::on__new_char_clicked();
  OgreManager::getInstance()->selectScene("EditScenary");
  FinishInputData();
}

OmgPlayer*
QOmgDialogPlayer::createPlayer( void )
{
  OmgPlayer* pPlayer = new OmgPlayer( ui->_name->text(), ui->listWidget->currentItem()->text() );

  pPlayer->setTextures( EditCharacterManager::getInstance()->getEditCharacter());
  pPlayer->setColor(_color_button->getSelectedColor());

  pPlayer->createCustomPixmap();

  pPlayer->setTotalLife( ui->_life->value() );

  QList<QListWidgetItem*> weaponsQList = ui->weaponList->selectedItems();
  std::vector<QString> vWeapons;
  for(QList<QListWidgetItem*>::Iterator it = weaponsQList.begin(); it != weaponsQList.end(); ++it )
	  vWeapons.push_back( QString(( *it)->text()) );
  pPlayer->setWeapons(vWeapons);

  return pPlayer;
}

