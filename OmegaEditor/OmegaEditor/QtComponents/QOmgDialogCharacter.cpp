#include "QOmgDialogCharacter.h"
#include "Folders/OmgFoldersMngr.h"
#include "Display/OgreManager.h"
#include <qDebug>
#include "EditionManagers/EditCharacterManager.h"
#include "OmgEntities/OmgWeaponsContainer.h"
#include "OmgEntities/OmgWeapon.h"
#include "OmgEntities/OmgItemContainer.h"


QOmgDialogCharacter::QOmgDialogCharacter(QWidget *parent, bool a_edit) :
    ui(new Ui::QOmgDialogCharacter),
    InputData( parent )
{
    ui->setupUi(this);

    _editing = a_edit;

    if(!_editing)
        ui->_edit_char->hide();
    else
        ui->_new_char->hide();

    _color_button = dynamic_cast<QColorButton*>( ui->widget );
    _color_button->setEditionMode(QColorButton::CHARACTER);
}

QOmgDialogCharacter::~QOmgDialogCharacter()
{
    delete ui;
}

void
QOmgDialogCharacter::ChangeWidgetsForEnemy()
{
  ui->_label2_enemy->show();
  ui->_type_enemy->show();
  ui->itemList->show();
  ui->itemLabel->show();
  ui->itemIcon->show();

  ui->_pb_textures->setIcon( QIcon(":/Media/enemy.png") );
  ui->_edit_char->setText("Edit Enemy");
  ui->_new_char->setText("New Enemy");

  std::vector<OmgFolder*> v_folders = OmgFoldersMngr::Instance()->getAvailableFolders(Omega::EnemyFolder);

  std::vector<OmgFolder*>::iterator it = v_folders.begin(), it_end = v_folders.end();

  for(; it != it_end; ++it)
  {
      OmgFolder* p_folder = (*it);

      ui->listWidget->addItem(new QListWidgetItem(QIcon(":/Media/folder.png"), p_folder->getName()));
  }

  FillListWidget( OmgWeaponsContainer::Instance()->availableWeapons(), ui->weaponList );
  FillListWidget( OmgItemContainer::Instance()->availableItems(), ui->itemList );
  adjustSize();
}

void
QOmgDialogCharacter::ChangeWidgetsForPlayer()
{
    ui->_label2_enemy->hide();
    ui->_type_enemy->hide();
	ui->itemList->hide();
	ui->itemLabel->hide();
	ui->itemIcon->hide();
    ui->_edit_char->setText("Edit Player");
    ui->_new_char->setText("New Player");

    std::vector<OmgFolder*> v_folders = OmgFoldersMngr::Instance()->getAvailableFolders(Omega::PlayerFolder);

    std::vector<OmgFolder*>::iterator it = v_folders.begin(), it_end = v_folders.end();

    for(; it != it_end; ++it)
    {
        OmgFolder* p_folder = (*it);

        ui->listWidget->addItem(new QListWidgetItem(QIcon(":/Media/folder.png"), p_folder->getName()));
    }

    Omega::EntityVector vWeapons = OmgWeaponsContainer::Instance()->availableWeapons();
    Omega::EntityIterator itWeapons = vWeapons.begin(), itEndWeapons = vWeapons.end();
    for(; itWeapons != itEndWeapons ; ++itWeapons )
    {
      OmgWeapon* weapon = dynamic_cast<OmgWeapon*>(*itWeapons);
      if( weapon )
        ui->weaponList->addItem(new QListWidgetItem(QIcon(":/Media/gun.png"), weapon->getName()));
    }

    adjustSize();
}

void QOmgDialogCharacter::on__new_char_clicked()
{
   qDebug() << "ALL OK";
   OgreManager::getInstance()->selectScene("EditScenary");
}

void QOmgDialogCharacter::on__edit_char_clicked()
{
    qDebug() << "ALL OK";
    OgreManager::getInstance()->selectScene("EditScenary");
}

void QOmgDialogCharacter::on_pushButton_clicked()
{
  FinishInputData();
}

void
QOmgDialogCharacter::on__pb_textures_clicked()
{
    OgreManager::getInstance()->selectScene("EditCharacter");
}

void QOmgDialogCharacter::on__type_enemy_currentIndexChanged(const QString &arg1)
{
    if(arg1 == "Runner" || arg1 == "Junior Boss" )
    {
        ui->weaponIcon->hide();
        ui->weaponLabel->hide();
        ui->weaponList->hide();
    } else {
        ui->weaponIcon->show();
        ui->weaponLabel->show();
        ui->weaponList->show();
    }
}

void QOmgDialogCharacter::on_deleteTextures_clicked()
{
  EditCharacterManager::getInstance()->clearCharacter();
}
