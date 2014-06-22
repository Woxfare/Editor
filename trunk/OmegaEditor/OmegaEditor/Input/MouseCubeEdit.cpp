#include "MouseCubeEdit.h"
#include <QDebug>
#include <QFileDialog>
#include "EditionManagers\EditCubeManager.h"

MouseCubeEdit::MouseCubeEdit() : MouseController()
{
    _p_raySceneQuery = OgreManager::getInstance()->getSceneManager()
            ->createRayQuery(Ogre::Ray());
    _p_raySceneQuery->setQueryTypeMask(Ogre::SceneManager::USER_TYPE_MASK_LIMIT);

    initControlerCamera();
}

void MouseCubeEdit::buttonPressed(Qt::MouseButton pressed, int x, int y, int width, int height)
{
    _lastPressed = pressed;
    _lastX = x;
    _lastY = y;
    _continuePress = true;

    if(_lastPressed == Qt::LeftButton)
    {
        qDebug() << "MOUSE LEFT_B PRESSED";
    }
    else if(_lastPressed == Qt::RightButton)
    {
        qDebug() << "MOUSE RIGTH_B PRESSED";
    }
}

void MouseCubeEdit::moved(int x, int y, int width, int height)
{
    if(_lastPressed == Qt::LeftButton)
    {
        qDebug() << "MOUSE LEFT_B MOVED";
        _continuePress = false;
    }
    else if(_lastPressed == Qt::RightButton)
    {
        rotateCam(_lastX-x,_lastY-y,OgreManager::getInstance()->getSceneManager()->getCamera("EditCubeCamera"));
        _continuePress = false;
    }
    else if(_lastPressed == Qt::MidButton)
    {
        qDebug() << "MOUSE MID_B MOVED";
        _continuePress = false;
    }
    else if(_lastPressed == Qt::NoButton)
    {
        //qDebug() << "TRANKING";
    }
}

void MouseCubeEdit::buttonReleased( int x, int y, int width, int height)
{
    if(_lastPressed == Qt::LeftButton)
    {
        qDebug() << "MOUSE LEFT_B RELEASSED";
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

void MouseCubeEdit::wheelMoved(int delta)
{

}

void MouseCubeEdit::doubleClickEvent(int x, int y, int width, int height, QWidget * widget)
{
    // Primero obtenemos la cara que ha seleccionado el usuario
    Ogre::ManualObject * selectedFace = NULL;
    try{
        Ogre::Ray mouseRay = _editCubeCamera->getCameraToViewportRay(x/float(width), y/float(height));
        _p_raySceneQuery->setRay(mouseRay);
        _p_raySceneQuery->setSortByDistance(true,1);
		_p_raySceneQuery->setQueryTypeMask(1<<1);
        Ogre::RaySceneQueryResult &result = _p_raySceneQuery->execute();
        Ogre::RaySceneQueryResult::iterator itr = result.begin();
        if (itr != result.end())
        {
            if(itr->movable)
            {
                qDebug() << itr->movable->getName().c_str();
                selectedFace = OgreManager::getInstance()->getSceneManager()->getManualObject(itr->movable->getName());
            }
        }

    } catch( Ogre::Exception e)
    {

    }

    //! Ahora decidimos dependiendo de el botton que debemos hacer o poner textura o eliminarla
    if(selectedFace != NULL)
	{
		switch( _lastPressed )
		{
			case Qt::RightButton:
				qDebug() << "Eliminando textura....";
				selectedFace->getSection(0)->getMaterial()->getTechnique(0)->getPass(0)->removeAllTextureUnitStates();
				break;
			case Qt::LeftButton:
				qDebug() << "Poniendo textura....";
				changeTextureOfFace(selectedFace, widget );
			break;
		}
	}
}

void
MouseCubeEdit::initControlerCamera( void )
{
    _editCubeCamera= OgreManager::getInstance()->getSceneManager()->getCamera("EditCubeCamera");
    Ogre::Real radius = 4;
    _editCubeCamera->setPosition(0.0,0.0,0.0);
    _editCubeCamera->setOrientation(Ogre::Quaternion::IDENTITY);
    _yawValue = Ogre::Degree(20);
    _lastYawValue = _yawValue;
    _editCubeCamera->yaw(_yawValue );
    _pitchValue = Ogre::Degree(40);
    _editCubeCamera->pitch( _pitchValue );
    _lastPitchValue = _pitchValue;
    _editCubeCamera->moveRelative(Ogre::Vector3(0.0,0.0,radius));
    _editCubeCamera->lookAt(0,0,0);
}

void
MouseCubeEdit::changeTextureOfFace(Ogre::ManualObject *selectedFace, QWidget * widget )
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
            image = image.scaled( QSize( 128, 128 ), Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
            QFile file("./mediaOgre/materials/textures/" + name);
            file.open(QIODevice::WriteOnly);
            image.save(&file, "PNG");
            file.close();

            Ogre::TextureManager::getSingleton().load((name).toStdString(), Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
        }
        selectedFace->getSection(0)->getMaterial()->getTechnique(0)->getPass(0)->removeAllTextureUnitStates();
        selectedFace->getSection(0)->getMaterial()->getTechnique(0)->getPass(0)->createTextureUnitState(name.toStdString());
        EditCubeManager::getInstance()->setLastTexture( name.toStdString() );

    } catch( Ogre::Exception e )
    {
        qDebug() << "Recovered";

        //! Cuando llega aqui es porque ha habido un error al cargar el archivo, pero ahora el archivo esta en mediaOgre copiado y correcto para poder mapearlo en
        //! la box, asi que volvemos a intentar poner la imagen.
        selectedFace->getSection(0)->getMaterial()->getTechnique(0)->getPass(0)->removeAllTextureUnitStates();
        selectedFace->getSection(0)->getMaterial()->getTechnique(0)->getPass(0)->createTextureUnitState(name.toStdString());
    }
}
