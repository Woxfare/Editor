#include "MouseCharacterEdit.h"
#include <QDebug>
#include <QFileDialog>
#include "InputData\QOmgWindowMngr.h"
#include "editionmanagers\editcharactermanager.h"

MouseCharacterEdit::MouseCharacterEdit() : MouseController()
{
    _p_raySceneQuery = OgreManager::getInstance()->getSceneManager()
            ->createRayQuery(Ogre::Ray());
    initControlerCamera();
}

void
MouseCharacterEdit::buttonPressed(Qt::MouseButton pressed, int x, int y, int width, int height)
{
    _lastPressed = pressed;
    _lastX = x;
    _lastY = y;
    _continuePress = true;

    if(_lastPressed == Qt::LeftButton)
    {
        //qDebug() << "MOUSE LEFT_B PRESSED";
    }
    else if(_lastPressed == Qt::RightButton)
    {
        //qDebug() << "MOUSE RIGTH_B PRESSED";
    }
}

void MouseCharacterEdit::moved(int x, int y, int width, int height)
{
    if(_lastPressed == Qt::LeftButton)
    {
        //qDebug() << "MOUSE LEFT_B MOVED";
        _continuePress = false;
    }
    else if(_lastPressed == Qt::RightButton)
    {
        rotateCam(_lastX-x,_lastY-y,OgreManager::getInstance()->getSceneManager()->getCamera("EditCharacterCamera"));
        _continuePress = false;
    }
    else if(_lastPressed == Qt::MidButton)
    {
        //qDebug() << "MOUSE MID_B MOVED";
        _continuePress = false;
    }
    else if(_lastPressed == Qt::NoButton)
    {
        //qDebug() << "TRANKING";
    }
}

void MouseCharacterEdit::buttonReleased( int x, int y, int width, int height)
{
    if(_lastPressed == Qt::LeftButton)
    {
        //qDebug() << "MOUSE LEFT_B RELEASSED";
        if(_continuePress)
        {
        }
    }
    else if(_lastPressed == Qt::RightButton)
    {
        qDebug() << "MOUSE RIGHT_B RELEASSED";
        _yawValue += _lastYawValue;
        _pitchValue += _lastPitchValue;
    }
    _lastPressed = Qt::NoButton;
    _continuePress = false;
}

void MouseCharacterEdit::wheelMoved(int delta)
{

}

std::string MouseCharacterEdit::selectCharacterFace(Ogre::Vector3 colisionPoint)
{
	std::string faceName = "";

	return faceName;
}

void MouseCharacterEdit::doubleClickEvent(int x, int y, int width, int height, QWidget * widget)
{
  Ogre::ManualObject * selectedFace = NULL;
  try{
    Ogre::Ray mouseRay = _editCharacterCamera->getCameraToViewportRay(x/float(width), y/float(height));
    _p_raySceneQuery->setRay(mouseRay);
	  _p_raySceneQuery->setSortByDistance(true,3);
    Ogre::RaySceneQueryResult &result = _p_raySceneQuery->execute();
    Ogre::RaySceneQueryResult::iterator itr = result.begin();

    for(; itr != result.end() && !selectedFace ; ++itr)
    {
      try{
        if(itr->movable)
        {
          QString nameFace = QString(itr->movable->getName().c_str());

          if( nameFace != "base_plane")
            selectedFace = OgreManager::getInstance()->getSceneManager()->getManualObject( itr->movable->getName() );
        }
      } catch( Ogre::Exception e){

      }
    }
   } catch( Ogre::Exception e){


  }

   if(selectedFace != NULL)
   {
     switch( _lastPressed )
     {
     case Qt::RightButton:
       selectedFace->getSection(0)->getMaterial()->getTechnique(0)->getPass(0)->removeAllTextureUnitStates();
       break;
     case Qt::LeftButton:
       changeTextureOfFace(selectedFace, widget );
       break;
     }
  }
}

void
MouseCharacterEdit::changeTextureOfFace(Ogre::ManualObject *selectedFace, QWidget * widget )
{
    //QFileDialog::
    //devuelve ./ruta/del/arxivo/mierdas/imagen.png
    /*
     * if !Ogre::ResourceManager::resourceExists("imagen.png"); entonces
     *      Copiar el arxivo a mediaOgre/material/texture/imagen.png
     * **Si la imagen no se carga: Ogre::ResourceManager::load("mediaOgre/material/texture/imagen.png", ??);
     */
    QString absFilename = QFileDialog::getOpenFileName(widget, "Open image file", "./mediaOgre/materials/textures");
    qDebug() << absFilename;

    if(absFilename == "")
        return;

    QFileInfo info(absFilename);

    QString name = (info.fileName().split(".")[0]) + ".png";

    try{
        if(!Ogre::TextureManager::getSingleton().resourceExists(name.toStdString()))
        {
            QPixmap image;
            image.load(absFilename);

            QFile file("./mediaOgre/materials/textures/" + name);
            file.open(QIODevice::WriteOnly);
            image.save(&file, "PNG");

            Ogre::TextureManager::getSingleton().load((name).toStdString(), Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
        }
        selectedFace->getSection(0)->getMaterial()->getTechnique(0)->getPass(0)->removeAllTextureUnitStates();
        selectedFace->getSection(0)->getMaterial()->getTechnique(0)->getPass(0)->createTextureUnitState(name.toStdString());
		if(QString( selectedFace->getName().c_str() ).contains("Front"))
		{
			if(QString( selectedFace->getName().c_str() ).contains("Head"))
				QOmgWindowMngr::Instance()->GetMainWindow()->getCharacterPartSelector()->changeTextureOfPart(head, name);
			else if(QString( selectedFace->getName().c_str() ).contains("Body"))
				QOmgWindowMngr::Instance()->GetMainWindow()->getCharacterPartSelector()->changeTextureOfPart(body, name);
			else if(QString( selectedFace->getName().c_str() ).contains("ArmL"))
				QOmgWindowMngr::Instance()->GetMainWindow()->getCharacterPartSelector()->changeTextureOfPart(armLeft, name);
			else if(QString( selectedFace->getName().c_str() ).contains("ArmR"))
				QOmgWindowMngr::Instance()->GetMainWindow()->getCharacterPartSelector()->changeTextureOfPart(armRight, name);
			else if(QString( selectedFace->getName().c_str() ).contains("LegL"))
				QOmgWindowMngr::Instance()->GetMainWindow()->getCharacterPartSelector()->changeTextureOfPart(legLeft, name);
			else if(QString( selectedFace->getName().c_str() ).contains("LegR"))
				QOmgWindowMngr::Instance()->GetMainWindow()->getCharacterPartSelector()->changeTextureOfPart(legRight, name);
		}

    } catch( Ogre::Exception e )
    {
        qDebug() << "Recovered";

        //! Cuando llega aqui es porque ha habido un error al cargar el archivo, pero ahora el archivo esta en mediaOgre copiado y correcto para poder mapearlo en
        //! la box, asi que volvemos a intentar poner la imagen.
        selectedFace->getSection(0)->getMaterial()->getTechnique(0)->getPass(0)->removeAllTextureUnitStates();
        selectedFace->getSection(0)->getMaterial()->getTechnique(0)->getPass(0)->createTextureUnitState(name.toStdString());
    }
}

void
MouseCharacterEdit::initControlerCamera( void )
{
    _editCharacterCamera = OgreManager::getInstance()->getSceneManager()->getCamera("EditCharacterCamera");
    Ogre::Real radius = 20;
    _editCharacterCamera->setPosition(0.0,0.0,0.0);
    _editCharacterCamera->setOrientation(Ogre::Quaternion::IDENTITY);
    _yawValue = Ogre::Degree(40);
    _lastYawValue = _yawValue;
    _editCharacterCamera->yaw(_yawValue );
    _pitchValue = Ogre::Degree(30);
    _editCharacterCamera->pitch( _pitchValue );
    _lastPitchValue = _pitchValue;
    _editCharacterCamera->moveRelative(Ogre::Vector3(0.0,0.0,radius));
    _editCharacterCamera->lookAt(0,0,0);
}