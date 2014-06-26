#include "QOmgDialogEnemy.h"
#include "OmgEntities/OmgEnemyContainer.h"
#include "QColorButton.h"
#include "QOmgWindowMngr.h"
#include <QMessageBox>
#include <QList>
#include <QListWidgetItem>
#include "Saver/OmgSaverMngr.h"
#include "Utils/OgreManager.h"
#include "EditionManagers/EditCharacterManager.h"
#include "OmgEntities/OmgWeapon.h"
#include "OmgEntities/OmgWeaponsContainer.h"

QOmgDialogEnemy::QOmgDialogEnemy(QWidget *ap_parent ) :
                                 QOmgDialogCharacter( ap_parent,false)
{
    ChangeWidgetsForEnemy();
    _p_enemy = new OmgEnemy("EnemyName", "DefaultEnemies");
    PutEnemyInQt();
    EditCharacterManager::getInstance()->clearCharacter();
}

QOmgDialogEnemy::QOmgDialogEnemy( QWidget* ap_parent, OmgEnemy* ap_enemy ) :
                                  QOmgDialogCharacter (ap_parent, true)
{
    ChangeWidgetsForEnemy();
    _p_enemy = ap_enemy;
    PutEnemyInQt();
    ui->_name->setEnabled(false);
    EditCharacterManager::getInstance()->setEditCharacter( ap_enemy->getTextures() );
    int rgb[3] = {
      ap_enemy->getColor().red(),
      ap_enemy->getColor().green(),
      ap_enemy->getColor().blue()
    };
    EditCharacterManager::getInstance()->changeCharacterColor( rgb );
}

void
QOmgDialogEnemy::on__new_char_clicked( void )
{
  if(OmgEnemyContainer::Instance()->getEnemy(_p_enemy->getName()))
  {
    QMessageBox::warning(this, "Error!!", "The enemy already exist, select another name");
    return;
  }

  if( Validate() )
      storeAndFinish(createEnemy());
}

void
QOmgDialogEnemy::on__edit_char_clicked()
{
    if(Validate())
    {
      OmgEnemyContainer::Instance()->deleteEnemy( _p_enemy->getName());
      storeAndFinish(createEnemy());
    }
}

bool
QOmgDialogEnemy::Validate( void )
{
    // Fill the player data
    QString name = ui->_name->text();

    if( name == "" )
    {
        QMessageBox::warning(this,
                             "Error!!",
                             "Select a name for the Enemy");
        return false;
    }

    QListWidgetItem * p_item = ui->listWidget->currentItem();
    if(p_item)
        _folder = p_item->text();
    else
        _folder = "";

    if( _folder == "")
    {
        QMessageBox::warning(this,
                             "Error!!",
                             "Select a folder to store the enemy");
        return false;
    }

    if( ui->_life->value() == 0 )
    {
        QMessageBox::warning(this,
                             "Error!!",
                             "The Enemy needs life");
        return false;
    }

    if( ui->itemList->currentItem() == 0 )
    {
        QMessageBox::warning(this,
                             "Error!!",
                             "The Enemy will give 0 points to the player, please give it points");
        return false;
    }

    return true;

}

void
QOmgDialogEnemy::PutEnemyInQt()
{
    if(!_p_enemy)
        return;

    //Enemy Name
    ui->_name->setText(_p_enemy->getName());

    //Life
    ui->_life->setValue(_p_enemy->getTotalLife());

    ui->listWidget->setCurrentItem(findFolderItemByName(_p_enemy->getFolderName()));

    //! Weapon
    if( _p_enemy->getWeapon() )
      ui->weaponList->setCurrentItem( getListItem( _p_enemy->getWeapon()->getName(), ui->weaponList ));

	//! Item
	ui->itemList->setCurrentItem( getListItem( _p_enemy->getItemName(), ui->itemList ));

	_color_button->changeColor( _p_enemy->getColor() );

	switch( _p_enemy->enemyType() )
	{
	case Omega::Runner:
		{
			ui->weaponIcon->hide();
			ui->weaponLabel->hide();
			ui->weaponList->hide();
			ui->_type_enemy->setCurrentIndex( 0 );
		}
		break;
	case Omega::BigBoss:
		ui->_type_enemy->setCurrentIndex( 1 );
		break;
	case Omega::Gunner:
		ui->_type_enemy->setCurrentIndex( 2 );
		break;
	case Omega::JuniorBoss:
		{
			ui->_type_enemy->setCurrentIndex( 3 );
			ui->weaponIcon->hide();
			ui->weaponLabel->hide();
			ui->weaponList->hide();
		}
		break;
	}
}

QListWidgetItem*
QOmgDialogEnemy::findFolderItemByName(QString aName)
{
    QList<QListWidgetItem*> vItems = ui->listWidget->findItems(aName, Qt::MatchCaseSensitive );

    if(vItems.isEmpty())
        return NULL;

    return vItems.first();
}

void
QOmgDialogEnemy::storeAndFinish( OmgEnemy* apEnemy )
{
  OmgEnemyContainer::Instance()->addEnemy(apEnemy);
  QOmgWindowMngr::Instance()->GetMainWindow()->UpdateWidgets( apEnemy );
  OmgSaverMngr::Instance()->addEntityToSave( apEnemy );
  QOmgDialogCharacter::on__new_char_clicked();
  OgreManager::getInstance()->selectScene("EditScenary");
  FinishInputData();
}

OmgEnemy*
QOmgDialogEnemy::createEnemy( void )
{
  OmgEnemy* pEnemy = new OmgEnemy( ui->_name->text(), ui->listWidget->currentItem()->text() );

  pEnemy->setTextures( EditCharacterManager::getInstance()->getEditCharacter());

  pEnemy->setColor(_color_button->getSelectedColor());

  pEnemy->setTotalLife( ui->_life->value() );

  pEnemy->setItemName( ui->itemList->currentItem()->text() );

  pEnemy->createCustomPixmap();

  QString debug = ui->_type_enemy->currentText();
  if( ui->_type_enemy->currentText() == "Big Boss")
	  pEnemy->setEnemyType( Omega::BigBoss );
  if( ui->_type_enemy->currentText() == "Junior Boss")
	  pEnemy->setEnemyType( Omega::JuniorBoss );
  if( ui->_type_enemy->currentText() == "Gunner")
	  pEnemy->setEnemyType( Omega::Gunner );
  if( ui->_type_enemy->currentText() == "Runner")
	  pEnemy->setEnemyType( Omega::Runner );

  if( ui->_type_enemy->currentText() == "Big Boss" || ui->_type_enemy->currentText() == "Gunner" ) // They have weapons
	  pEnemy->setWeapon( OmgWeaponsContainer::Instance()->getWeapon( ui->weaponList->currentItem()->text() ) );

  return pEnemy;
}


