#include "QOmgItemDialog.h"
#include "ui_QOmgItemDialog.h"
#include "QOmgStyle.h"
#include <QList>
#include <QListWidgetItem>
#include "OmgEntities/OmgItem.h"
#include "Folders/OmgFolder.h"
#include "Folders/OmgFoldersMngr.h"
#include "OmgEntities/OmgItemContainer.h"
#include <QMessageBox>
#include "QColorButton.h"
#include "QOmgWindowMngr.h"
#include <QDebug>
#include "Utils/OgreManager.h"
#include "Saver/OmgSaverMngr.h"
#include "EditionManagers/EditSceneManager.h"
#include "EditionManagers/EditCubeManager.h"
#include "Utils/CubeUtils.h"
#include "OmgEntities/OmgWeaponsContainer.h"
#include "OmgEntities/OmgWeapon.h"


QOmgItemDialog::QOmgItemDialog(OmgItem* apItem, QWidget *parent  ) : InputData(parent), ui(new Ui::QOmgItemDialog), _item( apItem )
{
    ui->setupUi(this);
    putItemInQt();
    OgreManager::getInstance()->selectScene("EditScenary");
    EditCubeManager::getInstance()->clearEditCube();

    if(!apItem)
      return;

    int rgb[3] = { apItem->getColor().red(), apItem->getColor().green(), apItem->getColor().blue() };
    EditCubeManager::getInstance()->changeEditCubeColor( rgb );
    EditCubeManager::getInstance()->changeEditCubeTextures( apItem->getTextures() );
}

QOmgItemDialog::~QOmgItemDialog()
{
    delete ui;
}

void
QOmgItemDialog::on_cbItemType_currentIndexChanged(const QString &arg1)
{
    hideAndShowWidgets(arg1);
}

void
QOmgItemDialog::hideAndShowWidgets(QString aItemType)
{
  int index = 0;
    if(aItemType == "Ammo")
  {
      ui->weaponIcon->show();
      ui->weaponLabel->show();
      ui->weaponList->show();
      ui->bulletIcon->show();
      ui->bulletLabel->show();
      ui->bulletSpin->show();
      index = 2;
  } else {
      ui->weaponIcon->hide();
      ui->weaponLabel->hide();
      ui->weaponList->hide();
      ui->bulletIcon->hide();
      ui->bulletLabel->hide();
      ui->bulletSpin->hide();
  }

  if(aItemType == "Gold")
  {
      ui->pointsIcon->show();
      ui->pointsLabel->show();
      ui->pointsSpin->show();
      index = 0;
  } else {
      ui->pointsIcon->hide();
      ui->pointsLabel->hide();
      ui->pointsSpin->hide();
  }

  if(aItemType == "Health")
  {
      ui->healthIcon->show();
      ui->healthLabel->show();
      ui->healthSpin->show();
      index = 1;
  } else {
      ui->healthIcon->hide();
      ui->healthLabel->hide();
      ui->healthSpin->hide();
  }

  ui->cbItemType->setCurrentIndex(index);
}

void
QOmgItemDialog::putItemInQt()
{
    std::vector<OmgFolder*> v_folders = OmgFoldersMngr::Instance()->getAvailableFolders(Omega::ItemFolder);

    std::vector<OmgFolder*>::iterator it = v_folders.begin(), it_end = v_folders.end();

    for(; it != it_end; ++it)
    {
        OmgFolder* p_folder = (*it);

        ui->folderList->addItem(new QListWidgetItem(QIcon(":/OmegaEditor/Resources/Icons/folder.png"), p_folder->getName()));
    }

    FillListWidget( OmgWeaponsContainer::Instance()->availableWeapons(), ui->weaponList );

    _color_button = dynamic_cast<QColorButton*>( ui->widget );
	_color_button->setEditionMode(QColorButton::CUBE);

    if( !_item )
    {
        ui->_name->setText("ItemName");
        hideAndShowWidgets("Gold");
        ui->folderList->setCurrentItem( getListItem( "DefaultItems", ui->folderList ) );
        _color_button->changeColor( QColor( 255, 255, 255 ) );
		ui->_editItem->hide();
    } else {
        ui->_name->setText(_item->getName());

        hideAndShowWidgets( _item->itemTypeStr() );
        
        ui->folderList->setCurrentItem( getListItem( _item->getFolderName(), ui->folderList ));

        if( _item->getWeapon() != "" )
          ui->weaponList->setCurrentItem( getListItem( _item->getWeapon(), ui->weaponList ));

        if(_item->itemType() == Omega::Ammo )
          ui->bulletSpin->setValue( _item->getQuantity() );
        else if(_item->itemType() == Omega::Health )
          ui->healthSpin->setValue( _item->getQuantity() );
        else
          ui->pointsSpin->setValue( _item->getQuantity() );

        _color_button->changeColor( _item->getColor() );

		int rgb[3] = { _item->getColor().red(), _item->getColor().green(), _item->getColor().blue() };
		EditCubeManager::getInstance()->changeEditCubeColor( rgb );
		EditCubeManager::getInstance()->changeEditCubeTextures( _item->getTextures() );

		ui->_newItem->hide();
    }
}

void
QOmgItemDialog::on__newItem_clicked()
{
    if(!validate())
      return;
    
    storeAndFinnish(createItem());
}

void
QOmgItemDialog::on__editItem_clicked()
{
    if(validate())
    {
        QString oldName = _item->getName();
        OmgItemContainer::Instance()->deleteItem(oldName);

        EditSceneManager * editSceneMngr = EditSceneManager::getInstance();

        //Guardamos la información de posicion de todos los nodos que tenian ese Item
        editSceneMngr->changeNodesInfo(oldName.toStdString(), ui->_name->text().toStdString());
        //Eliminamos todos los sitios donde esta el Item
        editSceneMngr->deleteEntityGroup(oldName.toStdString());
        //Elimnamos la Entidad0 i la mesh
        CubeUtils::deleteCubeMesh(oldName.toStdString());
        OgreManager::getInstance()->deleteMaterialGroup(oldName.toStdString());
        //Creamos la nueva mesh y la nueva Entidad0
        storeAndFinnish(createItem());
        //Creamos todas las entidades segun los nodes guardados i restauramos su info
        editSceneMngr->createEntityGroup( ui->_name->text().toStdString());
    }
}

void
QOmgItemDialog::on__cancel_clicked()
{
  FinishInputData();
}

bool
QOmgItemDialog::validate( void )
{
    // Fill the player data
    QString name = ui->_name->text();

    if( name == "" )
    {
        QMessageBox::warning(this,
                             "Error!!",
                             "Select a name for the Item");
        return false;
    }

    if( name == "ItemName" )
    {
        QMessageBox::warning(this,
                             "Error!!",
                             "Select another name instead ItemName");
        return false;
    }

    QListWidgetItem * p_item = ui->folderList->currentItem();
    if(p_item)
        _folder = p_item->text();
    else
        _folder = "";

    if( _folder == "")
    {
        QMessageBox::warning(this,
                             "Error!!",
                             "Select a folder to store the Item");
        return false;
    }

    if( getItemTypeFromQt() == Omega::Ammo )
    {
      if( !ui->weaponList->currentItem() )
      {
            QMessageBox::warning(this, "Error!!", "Select a weapon for the Item");
            return false;
      }

      if( ui->bulletSpin->value() == 0)
      {
        QMessageBox::warning(this,"Error!!", "Select a quantity of bullets for the Item");
        return false;
      }
    }

    if( getItemTypeFromQt() == Omega::Health )
    {
        if(ui->healthSpin->value() == 0)
        {
            QMessageBox::warning(this,
                                 "Error!!",
                                 "Select a quantity of life for the Item");
            return false;
        }
    }

    if( getItemTypeFromQt() == Omega::Gold )
    {
        if(ui->pointsSpin->value() == 0)
        {
            QMessageBox::warning(this,
                                 "Error!!",
                                 "Select a quantity of extra gold for the Item");
            return false;
        }
    }

    return true;
}

Omega::ItemType
QOmgItemDialog::getItemTypeFromQt( void )
{
    if( ui->cbItemType->currentText() == "Ammo" )
        return Omega::Ammo;
    if( ui->cbItemType->currentText() == "Gold")
        return Omega::Gold;
    return Omega::Health;
}

void
QOmgItemDialog::on__pb_textures_clicked()
{
	OgreManager::getInstance()->selectScene("EditCube");
}

OmgItem*
QOmgItemDialog::createItem( )
{
  QColorButton *colorButton = dynamic_cast<QColorButton*>( ui->widget );
  QColor color = colorButton->getSelectedColor();
  int rgb[3] = {color.red(), color.green(), color.blue()};
  OmgItem *newItem = new OmgItem( ui->_name->text(),ui->folderList->currentItem()->text(), EditCubeManager::getInstance()->getEditCube(), rgb);
  newItem->setItemType(getItemTypeFromQt());
  newItem->setFolderName(ui->folderList->currentItem()->text());
  if( newItem->itemType() == Omega::Ammo )
    newItem->setWeapon( ui->weaponList->currentItem()->text() );
  
  if( newItem->itemType() == Omega::Ammo )
    newItem->setQuantity( ui->bulletSpin->value() );
  else if( newItem->itemType() == Omega::Health )
     newItem->setQuantity( ui->healthSpin->value() );
  else
    newItem->setQuantity( ui->pointsSpin->value() );

  newItem->createCustomPixmap();
  return newItem;
}

void
QOmgItemDialog::storeAndFinnish(OmgItem *aObject)
{
    OmgItemContainer::Instance()->addItem(aObject);
    QOmgWindowMngr::Instance()->GetMainWindow()->UpdateWidgets(aObject);
    OmgSaverMngr::Instance()->addEntityToSave(aObject);
    FinishInputData();
}

void QOmgItemDialog::on_deleteTextures_clicked()
{
    EditCubeManager::getInstance()->clearEditCube();

    //Set the previous color
    QColorButton *colorButton = dynamic_cast<QColorButton*>( ui->widget );
    QColor color = colorButton->getSelectedColor();
    int rgb[3] = {color.red(), color.green(), color.blue()};
    EditCubeManager::getInstance()->changeEditCubeColor(rgb);
}

void QOmgItemDialog::on_texturesEqual_clicked()
{
    EditCubeManager::getInstance()->setAllTexturesEqual();
    //Set the previous color
    QColorButton *colorButton = dynamic_cast<QColorButton*>( ui->widget );
    QColor color = colorButton->getSelectedColor();
    int rgb[3] = {color.red(), color.green(), color.blue()};
    EditCubeManager::getInstance()->changeEditCubeColor(rgb);
}
