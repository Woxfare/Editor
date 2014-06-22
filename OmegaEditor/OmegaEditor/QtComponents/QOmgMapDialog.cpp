#include "QOmgMapDialog.h"
#include "ui_QOmgMapDialog.h"
#include "QColorButton.h"
#include "Display/OgreManager.h"
#include "OmgEntities/OmgMapContainer.h"
#include "QOmgWindowMngr.h"
#include "Saver/OmgSaverMngr.h"
#include "EditionManagers/EditSceneManager.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QFile>
#include "Folders/OmgFoldersMngr.h"

QOmgMapDialog::QOmgMapDialog(QWidget *parent) : InputData(parent),
    ui(new Ui::QOmgMapDialog)
{
    ui->setupUi(this);
    fillInputData();
    setMapInQt( NULL );
    terrainTextureName = "";
    _map = NULL;
    ui->pbLoad->hide();
}

QOmgMapDialog::QOmgMapDialog(OmgMap* apMap, QWidget *parent) : InputData( parent ),
  ui(new Ui::QOmgMapDialog)
{
  ui->setupUi(this);
  fillInputData();
  setMapInQt( apMap );
  _map = apMap;
}

QOmgMapDialog::~QOmgMapDialog()
{
    delete ui;
}

void QOmgMapDialog::on_pbCreate_clicked()
{
    if(validate())
      storeAndFinish(createMap());
}

void QOmgMapDialog::on_pbremove_clicked()
{
  EditSceneManager::getInstance()->removeBasePlaneTexture();
}

bool
QOmgMapDialog::validate( void )
{
    return true;
}

void
QOmgMapDialog::on_basePlaneTexture_clicked()
{
  try
  {
    QString absFilename;
    absFilename = QFileDialog::getOpenFileName(this, "Open image file", "./mediaOgre/materials/textures");
    if(absFilename != "")
    {
      QFileInfo info(absFilename);
      terrainTextureName = (info.fileName().split(".")[0]) + ".png";

      if(!Ogre::TextureManager::getSingleton().resourceExists(terrainTextureName.toStdString()))
      {
        QPixmap image;
        image.load(absFilename);

        QFile file("./mediaOgre/materials/textures/" + terrainTextureName);
        file.open(QIODevice::WriteOnly);
        image.save(&file, "PNG");

        Ogre::TextureManager::getSingleton().load((terrainTextureName).toStdString(), Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
      }
    }
  } catch ( Ogre::Exception e ) {}

  EditSceneManager::getInstance()->changeBasePlaneTexture( terrainTextureName.toStdString() );
}

void
QOmgMapDialog::setMapInQt( OmgMap* apMap )
{
  if(! apMap )
  {
    ui->folderList->setCurrentItem(findFolderMapsByName("DefaultMaps"));
    return;
  }

  ui->_name->setText( apMap->getName() );
  ui->folderList->setCurrentItem(findFolderMapsByName(apMap->getFolderName()));

}

QListWidgetItem*
QOmgMapDialog::findFolderMapsByName(QString aName)
{
  QList<QListWidgetItem*> vObjects = ui->folderList->findItems(aName, Qt::MatchCaseSensitive );

  if(vObjects.isEmpty())
    return NULL;

  return vObjects.first();
}

void
QOmgMapDialog::fillInputData( void )
{
  QColorButton *colorButton = dynamic_cast<QColorButton*>( ui->widget );
  colorButton->setEditionMode(QColorButton::SCENARY);
  colorButton->changeColor(QColor(255,255,255));
  OgreManager::getInstance()->selectScene("EditScenary"); 

  std::vector<OmgFolder*> v_folders = OmgFoldersMngr::Instance()->getAvailableFolders(Omega::MapFolder);

  std::vector<OmgFolder*>::iterator it = v_folders.begin(), it_end = v_folders.end();

  for(; it != it_end; ++it)
  {
    OmgFolder* p_folder = (*it);

    ui->folderList->addItem(new QListWidgetItem(QIcon(":/Media/folder.png"), p_folder->getName()));
  }

  connect(ui->_remove_pb, SIGNAL( clicked()), this, SLOT( on_pbremove_clicked()) );
  connect( ui->pbCancel, SIGNAL( clicked()) , this, SLOT( FinishInputData() ) );
}

OmgMap*
QOmgMapDialog::createMap( void )
{
  OmgMap* newMap = new OmgMap( ui->_name->text(), ui->folderList->currentItem()->text());

  newMap->setTerrainTextureName( terrainTextureName );
  QColorButton *colorButton = dynamic_cast<QColorButton*>( ui->widget );
  newMap->setColor( colorButton->getSelectedColor() );
  newMap->setSceneObjectsToTheMap( EditSceneManager::getInstance()->getEditScenary() );
  newMap->setEnemyDoors( EditSceneManager::getInstance()->getEnemiesDoors());
  newMap->setPlayerDoor( EditSceneManager::getInstance()->getPlayerDoor() );
  return newMap;
}

void
QOmgMapDialog::storeAndFinish( OmgMap* apNewMap )
{
  OmgMapContainer::Instance()->addMap(apNewMap);
  QOmgWindowMngr::Instance()->GetMainWindow()->UpdateWidgets(apNewMap);
  OmgSaverMngr::Instance()->addEntityToSave(apNewMap);
  emit hideInputData();
  hide();
  deleteLater();
}

void
QOmgMapDialog::on_pbClear_clicked( void )
{
  EditSceneManager::getInstance()->clearScenary( );
}

void
QOmgMapDialog::on_pbLoad_clicked()
{
  EditSceneManager::getInstance()->setEditScenary( _map->getSceneObjectsInTheMap());

  if( _map )
  {
    EditSceneManager::getInstance()->setEditScenary( _map->getSceneObjectsInTheMap());
	EditSceneManager::getInstance()->changeBasePlaneTexture( _map->getTerrainTextureName().toStdString() );
    EditSceneManager::getInstance()->setEnemyDoors( _map->getEnemyDoors() );
	EditSceneManager::getInstance()->addDoorToScene( _map->getPlayerDoor(), true );
  }
}
