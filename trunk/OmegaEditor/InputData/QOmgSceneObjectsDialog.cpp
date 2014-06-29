#include "QOmgSceneObjectsDialog.h"
#include "ui_QOmgSceneObjectsDialog.h"
#include "OmgEntities/OmgSceneObj.h"
#include "OmgEntities/OmgSceneObjContainer.h"
#include "QOmgStyle.h"
#include <QList>
#include <QListWidgetItem>
#include "Folders/OmgFolder.h"
#include "Folders/OmgFoldersMngr.h"
#include <QMessageBox>
#include "QOmgWindowMngr.h"
#include "QColorButton.h"
#include "Utils/OgreManager.h"
#include "Saver/OmgSaverMngr.h"
#include <QDebug>
#include "EditionManagers/EditSceneManager.h"
#include "EditionManagers/EditCubeManager.h"
#include "Utils/CubeUtils.h"

QOmgSceneObjectsDialog::QOmgSceneObjectsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QOmgSceneObjectsDialog)
{
  ui->setupUi(this);
  _sceneObj = NULL;
  putSceneObjectInQt();
  ui->_editItem->hide();   
  editingTextures = false;
  OgreManager::getInstance()->selectScene("EditScenary");
  EditCubeManager::getInstance()->clearEditCube();
}

QOmgSceneObjectsDialog::~QOmgSceneObjectsDialog()
{
    delete ui;
}

QOmgSceneObjectsDialog::QOmgSceneObjectsDialog(OmgSceneObj* aObject, QWidget *parent) :
    QDialog(parent), ui(new Ui::QOmgSceneObjectsDialog)
{
    ui->setupUi(this);
    ui->_newItem->hide();
    _sceneObj = aObject;
    putSceneObjectInQt();
    editingTextures = false;
    OgreManager::getInstance()->selectScene("EditScenary");
    if( !_sceneObj)
      return;

    int rgb[3] = { _sceneObj->getColor().red(), _sceneObj->getColor().green(), _sceneObj->getColor().blue() };
    EditCubeManager::getInstance()->changeEditCubeColor( rgb );
    EditCubeManager::getInstance()->changeEditCubeTextures( _sceneObj->getTextures() );
}

void
QOmgSceneObjectsDialog::putSceneObjectInQt()
{
  setStyleSheet(QOmgStyle::CurrentStyleSheet());
  Omega::FolderVector v_folders = OmgFoldersMngr::Instance()->getAvailableFolders( Omega::SceneObjFolder );

  std::vector<OmgFolder*>::iterator it = v_folders.begin(), it_end = v_folders.end();

  for(; it != it_end; ++it)
  {
      OmgFolder* p_folder = (*it);

      ui->folderList->addItem(new QListWidgetItem(QIcon(":/OmegaEditor/Resources/Icons/folder.png"), p_folder->getName()));
  }

  QColorButton *colorButton = dynamic_cast<QColorButton*>( ui->widget );
  colorButton->setEditionMode(QColorButton::CUBE);

  if( _sceneObj )
  {
      ui->_name->setText( _sceneObj->getName() );
      ui->folderList->setCurrentItem(findFolderObjectsByName(_sceneObj->getFolderName()));
      colorButton->changeColor( _sceneObj->getColor() );

      if( _sceneObj->getObjectType() == Omega::Dynamic )
          ui->cbType->setCurrentIndex(1);
  } else {
      ui->_name->setText( "ObjectName" );
      ui->folderList->setCurrentItem(findFolderObjectsByName("DefaultSceneObj"));
      colorButton->changeColor( QColor(255,255,255) );
  }
}

QListWidgetItem*
QOmgSceneObjectsDialog::findFolderObjectsByName(QString aName)
{
    QList<QListWidgetItem*> vObjects = ui->folderList->findItems(aName, Qt::MatchCaseSensitive );

    if(vObjects.isEmpty())
        return NULL;

    return vObjects.first();
}

bool
QOmgSceneObjectsDialog::validate( void )
{
    // Fill the player data
    QString name = ui->_name->text();

    if( name == "" )
    {
        QMessageBox::warning(this,
                             "Error!!",
                             "Select a name for the Object");
        return false;
    }

    if( name == "ObjectName" )
    {
        QMessageBox::warning(this,
                             "Error!!",
                             "Please select another name for the object instead ObjectName");
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
                             "Select a folder to store the Object");
        return false;
    }
    return true;
}

void QOmgSceneObjectsDialog::on__newItem_clicked()
{
    if(!validate())
        return;
    if(OmgSceneObjContainer::Instance()->getSceneObj(ui->_name->text()))
    {
        QMessageBox::warning(this,
                          "Error!!",
                          "The name for the object already exist, select another one");
        return;
    }

    storeAndFinnish(createSceneObject());
}

void
QOmgSceneObjectsDialog::on__editItem_clicked()
{
    if(!validate())
        return;

    // Solo se elimina el objeto y se vuelve a crear cuando se le cambia el nombre o la mesh
    QColorButton *colorButton = dynamic_cast<QColorButton*>( ui->widget );
    QColor color = colorButton->getSelectedColor();


    bool nameChanged(_sceneObj->getName() != ui->_name->text());
    if(nameChanged)
        qDebug() << "Name Changed";

    qDebug() << "Previous Color:" << _sceneObj->getColor().red() << _sceneObj->getColor().green() << _sceneObj->getColor().blue();
    qDebug() << "Current Color:"<< color.red() << color.green() << color.blue();
    bool colorChanged( color.red() != _sceneObj->getColor().red() ||
                       color.green() != _sceneObj->getColor().green() ||
                       color.blue() != _sceneObj->getColor().blue() );
    if(colorChanged)
        qDebug() << "Color Changed";

    if(editingTextures)
        qDebug() << "Textures Changed";

    if( nameChanged || editingTextures || colorChanged )
    {
        qDebug() << "Deleting old scene obj: " <<_sceneObj->getName() <<  ".mesh";
        try{
            QString oldName = _sceneObj->getName();
            OmgSceneObjContainer::Instance()->DeleteObject(oldName);

            EditSceneManager * editSceneMngr = EditSceneManager::getInstance();

            //Guardamos la información de posicion de todos los nodos que tenian ese Item
            editSceneMngr->changeNodesInfo(oldName.toStdString(), ui->_name->text().toStdString());
            //Eliminamos todos los sitios donde esta el Item
            editSceneMngr->deleteEntityGroup(oldName.toStdString());
            //Elimnamos la Entidad0 i la mesh
            CubeUtils::deleteCubeMesh(oldName.toStdString());
            OgreManager::getInstance()->deleteMaterialGroup(oldName.toStdString());
            //Creamos la nueva mesh y la nueva Entidad0
            storeAndFinnish(createSceneObject());
            //Creamos todas las entidades segun los nodes guardados i restauramos su info
            editSceneMngr->createEntityGroup( ui->_name->text().toStdString());

        } catch( Ogre::Exception e) {
            qDebug() << e.getFullDescription().c_str();
        }

        return;
    }

    qDebug() << "Modified";
    _sceneObj->setFolderName(ui->folderList->currentItem()->text());
    if(ui->cbType->currentText().contains("Static"))
        _sceneObj->setObjectType(Omega::Static);
    else
        _sceneObj->setObjectType(Omega::Dynamic);

    QOmgWindowMngr::Instance()->GetMainWindow()->UpdateWidgets(_sceneObj);
    emit HideInputData();
    hide();
    deleteLater();
}

void QOmgSceneObjectsDialog::on__cancel_clicked()
{
    if(editingTextures)
        OgreManager::getInstance()->selectScene("EditScenary");
    emit HideInputData();
    hide();
    deleteLater();
}

OmgSceneObj*
QOmgSceneObjectsDialog::createSceneObject( void )
{
    QColorButton *colorButton = dynamic_cast<QColorButton*>( ui->widget );
    QColor color = colorButton->getSelectedColor();
    int rgb[3] = {color.red(), color.green(), color.blue()};
    OmgSceneObj * newObject = new OmgSceneObj( ui->_name->text(), ui->folderList->currentItem()->text(), EditCubeManager::getInstance()->getEditCube(), rgb);

    if(ui->cbType->currentText().contains("Dynamic",Qt::CaseSensitive))
    {
        newObject->setObjectType( Omega::Dynamic );
    } else {
        newObject->setObjectType( Omega::Static );
    }

    return newObject;
}

void
QOmgSceneObjectsDialog::storeAndFinnish(OmgSceneObj *aObject)
{
    OmgSceneObjContainer::Instance()->AddObject(aObject);
    QOmgWindowMngr::Instance()->GetMainWindow()->UpdateWidgets(aObject);
    OmgSaverMngr::Instance()->addEntityToSave(aObject);
    if(editingTextures)
        OgreManager::getInstance()->selectScene("EditScenary");
    emit HideInputData();
    hide();
    deleteLater();
}

void QOmgSceneObjectsDialog::on__pbTextures_clicked()
{
    if(!editingTextures)
    {
        OgreManager::getInstance()->selectScene("EditCube");
        editingTextures = true;
    }
}

void QOmgSceneObjectsDialog::on_deleteTextures_clicked()
{
   EditCubeManager::getInstance()->clearEditCube();

    //Set the previous color
    QColorButton *colorButton = dynamic_cast<QColorButton*>( ui->widget );
    QColor color = colorButton->getSelectedColor();
    int rgb[3] = {color.red(), color.green(), color.blue()};
    EditCubeManager::getInstance()->changeEditCubeColor(rgb);
}

void QOmgSceneObjectsDialog::on_texturesEqual_clicked()
{
    EditCubeManager::getInstance()->setAllTexturesEqual();
    //Set the previous color
    QColorButton *colorButton = dynamic_cast<QColorButton*>( ui->widget );
    QColor color = colorButton->getSelectedColor();
    int rgb[3] = {color.red(), color.green(), color.blue()};
    EditCubeManager::getInstance()->changeEditCubeColor(rgb);
}
