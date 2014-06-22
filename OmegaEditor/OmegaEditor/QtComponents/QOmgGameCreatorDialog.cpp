#include "QOmgGameCreatorDialog.h"
#include "ui_QOmgGameCreatorDialog.h"
#include "Omega.h"
#include "OmgEntities/OmgItemContainer.h"
#include "OmgEntities/OmgPlayerContainer.h"
#include "OmgEntities/OmgEnemyContainer.h"
#include "OmgEntities/OmgPlayer.h"
#include "Folders/OmgFoldersMngr.h"
#include "Folders/OmgFolder.h"
#include "OmgEntities/OmgMapContainer.h"
#include "OmgEntities/OmgMap.h"
#include <QListWidget>
#include "OmgEntities/OmgGame.h"
#include "qmessagebox.h"
#include <QString>
#include "OmgEntities/OmgGameContainer.h"
#include "QOmgWindowMngr.h"
#include "Saver/OmgSaverMngr.h"

QOmgGameCreatorDialog::QOmgGameCreatorDialog( QWidget *parent ) : InputData(parent),
  ui(new Ui::QOmgGameCreatorDialog)
{
  ui->setupUi(this);
  fillInputData();
}

QOmgGameCreatorDialog::QOmgGameCreatorDialog( OmgGame* apGameToEdit, QWidget *parent ) : InputData(parent),
  ui(new Ui::QOmgGameCreatorDialog)
{
  ui->setupUi(this);
  fillInputData();
  setGameInQt( apGameToEdit );
}

QOmgGameCreatorDialog::~QOmgGameCreatorDialog()
{
  delete ui;
}

void
QOmgGameCreatorDialog::fillInputData( void )
{
  ui->itemsList->setSelectionMode(QAbstractItemView::MultiSelection);
  ui->enemiesList->setSelectionMode(QAbstractItemView::MultiSelection);

  FillListWidget( OmgItemContainer::Instance()->availableItems(), ui->itemsList );
  FillListWidget( OmgEnemyContainer::Instance()->availableEnemies(), ui->enemiesList );
  FillListWidget( OmgMapContainer::Instance()->availableMaps(), ui->mapList );
  FillListWidget( OmgPlayerContainer::Instance()->availablePlayers(), ui->playersList );

  Omega::FolderVector vFolders = OmgFoldersMngr::Instance()->getAvailableFolders( Omega::GameFolder );

  Omega::FolderVector::iterator itFolders = vFolders.begin(), it_endFolders = vFolders.end();

  for(; itFolders != it_endFolders; ++itFolders)
  {
    OmgFolder* pFolder = (*itFolders);

    ui->listWidget->addItem(new QListWidgetItem(QIcon(":/Media/folder.png"), pFolder->getName()));
  }

  ui->listWidget->setCurrentItem(getListItem( "DefaultGames", ui->listWidget ) );
}

void
QOmgGameCreatorDialog::setGameInQt( OmgGame* apGame )
{
  ui->name->setText( apGame->getName() );
  ui->nRounds->setValue( apGame->getNumberOfRounds() );
  ui->maxEnemies->setValue( apGame->getMaxEnemies() );
  ui->minEnemies->setValue( apGame->getMinEnemies() );
  ui->enemyIncrement->setValue( apGame->getEnemyIncrement());
  ui->maxBosses->setValue( apGame->getIntervalBosses());
  ui->bossesInterval->setValue( apGame->getIntervalBosses());
  ui->listWidget->setCurrentItem( getListItem( apGame->getFolderName(), ui->listWidget ) );

  Omega::EntityVector vEnemies = apGame->getAvailableEnemies();
  Omega::EntityVector vItems = apGame->getAvailableItems();

  int nEnemies = vEnemies.size(), nItems = vItems.size();
  for( int i = 0; i < nEnemies ; ++i )
    ui->enemiesList->setItemSelected(getListItem( vEnemies[i]->getName(), ui->enemiesList ), true );
  for( int i = 0; i < nItems ; ++i )
    ui->itemsList->setItemSelected(getListItem( vItems[i]->getName(), ui->itemsList ), true );

  ui->playersList->setCurrentItem( getListItem( apGame->getPlayer()->getName(), ui->playersList ) );
  ui->mapList->setCurrentItem( getListItem( apGame->getMap()->getName() , ui->mapList ) );
}

void
QOmgGameCreatorDialog::on_pbCancel_clicked()
{
  FinishInputData();
}

void QOmgGameCreatorDialog::on_pbSave_clicked()
{
  if(validate())
    storeAndFinnish( createGame() );
}

void QOmgGameCreatorDialog::on_pbPlay_clicked()
{
  if(validate())
    createGame()->SaveGameInFile();
}

OmgGame*
QOmgGameCreatorDialog::createGame( void )
{
  OmgGame* newGame = new OmgGame( ui->name->text(), ui->listWidget->currentItem()->text() );

  newGame->setPlayer( OmgPlayerContainer::Instance()->getPlayer( ui->playersList->currentItem()->text() ) );
  newGame->setMap( OmgMapContainer::Instance()->getMap(ui->mapList->currentItem()->text()));

  QList<QListWidgetItem*> listEnemies = ui->enemiesList->selectedItems();
  Omega::EntityVector vEnemies;
  for(QList<QListWidgetItem*>::Iterator it = listEnemies.begin(); it != listEnemies.end(); ++it )
    vEnemies.push_back(OmgEnemyContainer::Instance()->getEnemy((*it)->text()));
  newGame->setAvailableEnemies(vEnemies);

  QList<QListWidgetItem*> listItems = ui->itemsList->selectedItems();
  Omega::EntityVector vItems;
  for(QList<QListWidgetItem*>::Iterator it = listItems.begin(); it != listItems.end(); ++it )
    vItems.push_back(OmgItemContainer::Instance()->getItem((*it)->text()));
  newGame->setAvailableItems(vItems);

  newGame->setIntervalBosses( ui->bossesInterval->value());
  newGame->setNumberOfRounds(ui->nRounds->value());
  newGame->setMaxEnemies(ui->maxEnemies->value());
  newGame->setMinEnemies(ui->minEnemies->value());
  newGame->setEnemyIncrement( ui->enemyIncrement->value());
  newGame->setNumberOfBosses( ui->maxBosses->value());

  return newGame;
}

bool
QOmgGameCreatorDialog::validate( void )
{
  QString name = ui->name->text();

  if( name == "" )
  {
    QMessageBox::warning(this,
      "Error!!",
      "Select a name for the game");
    return false;
  }

  if( !ui->playersList->currentItem())
  {
    QMessageBox::warning( this,
                          "Error!!",
                          "Select a player for the game");
    return false;
  }

  if( !ui->mapList->currentItem() )
  {
    QMessageBox::warning( this,
                          "Error!!",
                          "Select a map for the game");
    return false;
  }

  if( ui->enemiesList->selectedItems().size() == 0 )
  {
    QMessageBox::warning( this,
                          "Error!!",
                          "Select at least one enemy to play the game");
    return false;
  }

  if( ui->itemsList->selectedItems().size() == 0 )
  {
    QMessageBox::warning( this,
      "Error!!",
      "Select at least one item to play the game");
    return false;
  }

  if( !ui->listWidget->currentItem())
  {
    QMessageBox::warning( this,
      "Error!!",
      "Select at least one item to play the game");
    return false;
  }
  return true;
}

void
QOmgGameCreatorDialog::storeAndFinnish( OmgGame* newGame )
{
  OmgGameContainer::Instance()->addGame( newGame );
  QOmgWindowMngr::Instance()->GetMainWindow()->UpdateWidgets( newGame );
  OmgSaverMngr::Instance()->addEntityToSave(newGame);
  FinishInputData();
}