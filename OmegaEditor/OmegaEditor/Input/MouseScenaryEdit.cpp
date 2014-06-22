#include "MouseScenaryEdit.h"
#include "Display/OgreManager.h"
#include <QDebug>
#include <QTimeLine>
#include "EditionManagers/EditSceneManager.h"
#include "InputManager.h"
#include "KeyboardController.h"

MouseScenaryEdit::MouseScenaryEdit() : MouseController()
{
    Ogre::SceneManager * sceneManager = OgreManager::getInstance()->getSceneManager();

    _p_currentObject = sceneManager->getRootSceneNode()->createChildSceneNode("CurrentNode");
    _p_currentObject->setVisible(false);

    _p_raySceneQuery = sceneManager->createRayQuery(Ogre::Ray());
    _p_raySceneQuery->setQueryTypeMask(~Ogre::SceneManager::USER_TYPE_MASK_LIMIT);
    mCount = 1;

    _currentObjectName  = "";
    _controlKeyPressed  = false;
    _deleteMode         = false;
    _scaleMode          = false;
    _lastPnt            = Ogre::Vector3(0,0,0);
    _pointToLookAt      = Ogre::Vector3(0,0,0);

    initControlerCamera();
}

void
MouseScenaryEdit::changeCurrentObject(std::string nameObject)
{
    //The user is silly and wants to select another object whilst he is deleting things
    if(_deleteMode || _scaleMode )
        return;

    Ogre::SceneManager * sceneManager = OgreManager::getInstance()->getSceneManager();
    if(nameObject == "")
    {
        _p_currentObject->detachAllObjects();
        return;
    }

    if(sceneManager->getEntity(nameObject))
    {
        _p_currentObject->detachAllObjects();
		Ogre::Entity* pEntity = sceneManager->getEntity(nameObject);
		pEntity->setCastShadows(false);
        _p_currentObject->attachObject(sceneManager->getEntity(nameObject));
    }
    else if(sceneManager->getManualObject(nameObject))
    {
        _p_currentObject->detachAllObjects();
        _p_currentObject->attachObject(sceneManager->getEntity(nameObject));
    }

    _currentObjectName = nameObject;
}

void
MouseScenaryEdit::buttonPressed(Qt::MouseButton pressed, int x, int y, int width, int height)
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

void
MouseScenaryEdit::deleteMeshOnRay(int x, int y, int width, int height)
{
    Ogre::Camera * mCamera = OgreManager::getInstance()->getViewPort()->getCamera();
    Ogre::SceneManager * mSceneMgr = OgreManager::getInstance()->getSceneManager();
    if(_lastPressed == Qt::LeftButton)
    {
        Ogre::Ray mouseRay = mCamera->getCameraToViewportRay(x/float(width), y/float(height));
        _p_raySceneQuery->setRay(mouseRay);
        _p_raySceneQuery->setSortByDistance(true,2);
        Ogre::RaySceneQueryResult &result = _p_raySceneQuery->execute();
        Ogre::RaySceneQueryResult::iterator itr = result.begin( );
        if (itr != result.end())
        {
            if(itr->movable->getName() != "base_plane")
            {
                try{
                  if( "Enemy" ==  (QString().fromStdString(itr->movable->getName())).split('_')[0].toStdString())
                    EditSceneManager::getInstance()->deleteDoorFromScene( itr->movable->getName() );
				  else if( "Player" ==  (QString().fromStdString(itr->movable->getName())).split('_')[0].toStdString())
					  EditSceneManager::getInstance()->deleteDoorFromScene( itr->movable->getName(), true );
                  else
                    EditSceneManager::getInstance()->deleteCubeFromScene(itr->movable->getName());
                } catch(...)
                {
                    qDebug() << "Fuck!";
                }
            }
        }
    }
    _lastPressed = Qt::NoButton;
}

void
MouseScenaryEdit::scaleMeshOnRay(int x, int y, int width, int height)
{
  Ogre::Camera * mCamera = OgreManager::getInstance()->getViewPort()->getCamera();
  Ogre::SceneManager * mSceneMgr = OgreManager::getInstance()->getSceneManager();
  if(_lastPressed == Qt::LeftButton)
  {
    Ogre::Ray mouseRay = mCamera->getCameraToViewportRay(x/float(width), y/float(height));
    _p_raySceneQuery->setRay(mouseRay);
    _p_raySceneQuery->setSortByDistance(true,2);
    Ogre::RaySceneQueryResult &result = _p_raySceneQuery->execute();
    Ogre::RaySceneQueryResult::iterator itr = result.begin( );
    if (itr != result.end())
    {
      if(itr->movable->getName() != "base_plane")
      {
        try{
          Ogre::SceneNode *node = mSceneMgr->getSceneNode(itr->movable->getName());
          node->scale(2,2,2);
        } catch(...)
        {
          qDebug() << "Fuck!";
        }
      }
    }
  }
}

void
MouseScenaryEdit::moved(int x, int y, int width, int height)
{
  if(_lastPressed == Qt::LeftButton)
  {
    _continuePress = false;
  }
  else if(_lastPressed == Qt::RightButton)
  {      
    rotateCam(x-_lastX, y-_lastY,OgreManager::getInstance()->getSceneManager()->getCamera("EditScenaryCamera"));
    _continuePress = false;
  }
  else if(_lastPressed == Qt::MidButton)
  {
    translateCamera(x,y, float( width ), float( height));
    _continuePress = false;
  }
  else if(_lastPressed == Qt::NoButton)
  {
    moveObject(x,y,float(width), float(height));
  }
}

void
MouseScenaryEdit::buttonReleased( int x, int y, int width, int height)
{
    if(_lastPressed == Qt::LeftButton)
    {
      if( InputManager::getInstance()->getKeyBoardController()->isKeyPressed(Qt::Key_D))
      {
            deleteMeshOnRay( x, y, width, height);
            return;
      }
      if( _scaleMode )
      {
        scaleMeshOnRay( x, y, width, height);
        return;
      }

      if(_continuePress)
      {
        if( _p_currentObject->numAttachedObjects() != 0 )
        {
          Ogre::Ray mouseRay = _editScenaryCamera->getCameraToViewportRay(x/float(width), y/float(height));
          addObjectToScene(mouseRay, x, y);
        }
      }
    }
    else if(_lastPressed == Qt::RightButton)
    {
        finnishRotation();
    }
    _lastPressed = Qt::NoButton;
    _continuePress = false;
}

void
MouseScenaryEdit::wheelMoved(int delta)
{
  Ogre::Vector3 direction = _editScenaryCamera->getDirection(),
                 position = _editScenaryCamera->getPosition();

    float increment = (delta/120)*1.5;


    Ogre::Vector3 newPosition = Ogre::Vector3( position.x - direction.x*increment,
                                               position.y - direction.y*increment,
                                               position.z - direction.z*increment );

    Ogre::Ray cameraRay( newPosition, direction );

    _p_raySceneQuery->setRay(cameraRay);
    _p_raySceneQuery->setSortByDistance(true,3);

    Ogre::RaySceneQueryResult &result = _p_raySceneQuery->execute();
    Ogre::RaySceneQueryResult::iterator itr = result.begin( );

    if(itr == result.end())
      return; // The camera is pointing no place

    float distance = itr->distance;

    if( distance < 5. )
      return;

    _radius += increment;
    _editScenaryCamera->setPosition( newPosition );
}

void
MouseScenaryEdit::doubleClickEvent(int x, int y, int width, int height, QWidget* /*widget*/)
{
    try
    {
        if(_lastPressed == Qt::RightButton)
        {
            Ogre::Ray mouseRay = _editScenaryCamera->getCameraToViewportRay(x/float(width), y/float(height));
            changeLookAt(mouseRay, x,y);
        }
    }
    catch(Ogre::Exception e)
    {
        qDebug() << e.getFullDescription().c_str();
    }

    _lastPressed = Qt::NoButton;
    _continuePress = false;
}

std::string
MouseScenaryEdit::currentObjectName( void )
{
    return _currentObjectName;
}

void
MouseScenaryEdit::controlKeyPressed(bool pressed)
{
    _controlKeyPressed = pressed;
}

void
MouseScenaryEdit::deleteMode(bool pressed)
{
    _deleteMode = pressed;
}

void
MouseScenaryEdit::rotateCam(Ogre::Real dx, Ogre::Real dy, Ogre::Camera *cam)
{
    Ogre::Radian yawValue = (Ogre::Radian)ROTATION_SPEED*dx,
                 pitchValue = (Ogre::Radian)ROTATION_SPEED*dy;
    cam->setOrientation(Ogre::Quaternion::IDENTITY);
    cam->setPosition(getNewCameraRotationPos( yawValue + _yawValue, pitchValue + _pitchValue ));
    cam->lookAt(_lastPnt);

    _lastYawValue = yawValue;
    _lastPitchValue = pitchValue;
}

Ogre::Vector3
MouseScenaryEdit::getNewCameraRotationPos(Ogre::Radian newYaw, Ogre::Radian newPitch)
{
    Ogre::Vector3 newPosition(_lastPnt.x + _radius*Ogre::Math::Cos(newYaw)*Ogre::Math::Cos(newPitch),
                              _lastPnt.y + _radius*Ogre::Math::Sin(newPitch),
                              _lastPnt.z + _radius*Ogre::Math::Sin(newYaw)*Ogre::Math::Cos(newPitch));

    if((newPitch).valueDegrees() < -89)
    {
        newPosition = Ogre::Vector3(_lastPnt.x + _radius*Ogre::Math::Cos(newYaw)*Ogre::Math::Cos(-89),
                                    _lastPnt.y + _radius*Ogre::Math::Sin(-89),
                                    _lastPnt.z + _radius*Ogre::Math::Sin(newYaw)*Ogre::Math::Cos(-89));
    } else if ( (newPitch).valueDegrees() > 89 )
    {
        newPosition = Ogre::Vector3(_lastPnt.x + _radius*Ogre::Math::Cos(newYaw)*Ogre::Math::Cos(Ogre::Degree(89)),
                                    _lastPnt.y + _radius*Ogre::Math::Sin(Ogre::Degree(89)),
                                    _lastPnt.z + _radius*Ogre::Math::Sin(newYaw)*Ogre::Math::Cos(Ogre::Degree(89)));
    }

    return newPosition;
}

void
MouseScenaryEdit::initControlerCamera( void )
{
    _editScenaryCamera = OgreManager::getInstance()->getSceneManager()->getCamera("EditScenaryCamera");
    _radius = 60;
    _editScenaryCamera->setPosition(0.0,0.0,0.0);
    _editScenaryCamera->setOrientation(Ogre::Quaternion::IDENTITY);
    _yawValue = Ogre::Degree(0);
    _lastYawValue = _yawValue;
    _editScenaryCamera->yaw(_yawValue );
    _pitchValue = Ogre::Degree(45);
    _editScenaryCamera->pitch( _pitchValue );
    _lastPitchValue = _pitchValue;
    _editScenaryCamera->moveRelative(Ogre::Vector3(0.0,0.0,_radius));
    _editScenaryCamera->lookAt(0,0,0);
}

void
MouseScenaryEdit::addObjectToScene(Ogre::Ray mouseRay, int x, int y)
{
  try
  {
    _p_raySceneQuery->setRay(mouseRay);
    _p_raySceneQuery->setSortByDistance(true,3);
    Ogre::RaySceneQueryResult &result = _p_raySceneQuery->execute();
    Ogre::RaySceneQueryResult::iterator itr = result.begin( );
    if (itr != result.end())
    {
        bool bottom = false;
        if( _pitchValue.valueDegrees() < 0)
        {
            bottom = true;
            if((itr->movable->getName() == "Ogre/MO1" ))
            {
                itr++;
            }
            if( itr != result.end() && _p_currentObject->getAttachedObject(0)->getName() == itr->movable->getName() )
                itr++;
        }
        else
        {
            if( _p_currentObject->getAttachedObject(0)->getName() == itr->movable->getName() )
                itr++;
        }

        if(itr != result.end())
        {
          // Gets the name of the current attached object
          QString name = QString().fromStdString(_p_currentObject->getAttachedObject(0)->getName()).split('_')[0];

          // Calculates the position to draw the new object
          Ogre::Vector3 positionToDraw = mouseRay.getPoint(itr->distance);
          positionToDraw.x = Ogre::Math::Floor(positionToDraw.x+0.5);
          positionToDraw.y = Ogre::Math::Ceil(positionToDraw.y);
          if(bottom)
              positionToDraw.y-=1;
          positionToDraw.z = Ogre::Math::Floor(positionToDraw.z+0.5);

          // The Edit Scene Manager will perform all the need it actions

          if(name == "Enemy")
            EditSceneManager::getInstance()->addDoorToScene( positionToDraw );
		  else if( name == "Player" )
			EditSceneManager::getInstance()->addDoorToScene( positionToDraw , true );
          else
            EditSceneManager::getInstance()->addCubeToScene( name.toStdString(), positionToDraw );

        }
    }
  } catch(Ogre::Exception e) {
      qDebug() << e.getFullDescription().c_str();
  }
}

void
MouseScenaryEdit::changeLookAt(Ogre::Ray mouseRay, int x, int y)
{
    try {
        Ogre::SceneManager * mSceneMgr = OgreManager::getInstance()->getSceneManager();
        _p_raySceneQuery->setRay(mouseRay);
        _p_raySceneQuery->setSortByDistance(true,3);
        Ogre::RaySceneQueryResult &result = _p_raySceneQuery->execute();
        Ogre::RaySceneQueryResult::iterator itr = result.begin( );
        if (itr != result.end())
        {
            if( _p_currentObject->numAttachedObjects() != 0 )
                if( _p_currentObject->getAttachedObject(0)->getName() == itr->movable->getName() )
                    itr++;

            if(itr != result.end())
            {
                Ogre::Vector3 pointToLook = mouseRay.getPoint(itr->distance);
                _editScenaryCamera->lookAt(pointToLook);
                _lastPnt = pointToLook;
                rotateCam(0, 0, _editScenaryCamera);
            }
        }
    }catch(Ogre::Exception e){
        qDebug() << e.getFullDescription().c_str();
    }
}

void
MouseScenaryEdit::finnishRotation( void )
{
    _yawValue += _lastYawValue;
    _pitchValue += _lastPitchValue;
    if( _pitchValue.valueDegrees() < -89)
        _pitchValue = -89;
    if( _pitchValue.valueDegrees() > 89)
        _pitchValue = 89;
}

void
MouseScenaryEdit::translateCamera( int x, int y,float width, float height)
{
  Ogre::Ray mouseRay = _editScenaryCamera->getCameraToViewportRay(x/width, y/height);
  _p_raySceneQuery->setRay(mouseRay);
  Ogre::Vector3 destination = mouseRay.getPoint(1);

  Ogre::Ray mouseRayOrigin = _editScenaryCamera->getCameraToViewportRay(_lastX/width, _lastY/height);
  _p_raySceneQuery->setRay(mouseRayOrigin);
  Ogre::Vector3 origin = mouseRayOrigin.getPoint(1);

  Ogre::Vector3 direction = -(destination - origin)*MOUSE_SENSIBILITY;
  _lastPnt += direction;
  Ogre::Vector3 cameraPosition = _editScenaryCamera->getPosition();
  _editScenaryCamera->setPosition( cameraPosition.x + direction.x,
    cameraPosition.y + direction.y,
    cameraPosition.z + direction.z );
  _lastX = x;
  _lastY = y;
}

void
MouseScenaryEdit::moveObject(int x, int y, float width, float height)
{
   try{
        if( _p_currentObject->numAttachedObjects() != 0 )
        {
           Ogre::Ray mouseRay = _editScenaryCamera->getCameraToViewportRay(x/width, y/height);
           _p_raySceneQuery->setRay(mouseRay);
           _p_raySceneQuery->setSortByDistance(true,3);
           Ogre::RaySceneQueryResult &result = _p_raySceneQuery->execute();
           Ogre::RaySceneQueryResult::iterator itr = result.begin();
           if (itr != result.end())
           {
               bool bottom = false;
               if( _pitchValue.valueDegrees() < 0)
               {
                   bottom = true;
				   std::string movableName = itr->movable->getName();
                   if((itr->movable->getName() == "Ogre/MO1" ))
                       itr++;
                   if( itr != result.end() && _p_currentObject->getAttachedObject(0)->getName() == itr->movable->getName()  )
                       itr++;
               }
               else
               {
                   if( _p_currentObject->getAttachedObject(0)->getName() == itr->movable->getName() )
                       itr++;
               }
               if(itr != result.end())
               {
                   Ogre::Vector3 positionToDraw = mouseRay.getPoint(itr->distance);
                   qDebug() << "RayPoint" << positionToDraw.x << positionToDraw.y << positionToDraw.z;
                   positionToDraw.x = Ogre::Math::Floor(positionToDraw.x+0.5);
                   positionToDraw.y = Ogre::Math::Ceil(positionToDraw.y);
                   if(bottom)
                       positionToDraw.y-=1;
                   positionToDraw.z = Ogre::Math::Floor(positionToDraw.z+0.5);
                   qDebug() << "DrawPoint" << positionToDraw.x << positionToDraw.y << positionToDraw.z;

                   _p_currentObject->setPosition(positionToDraw);
               }
           }
       }
    } catch(Ogre::Exception e) {
        qDebug() << e.getFullDescription().c_str();
    }
}

void
MouseScenaryEdit::scaleMode( bool pressed )
{
  _scaleMode = pressed;
}

void
MouseScenaryEdit::arrowKeyPressed( Qt::Key key )
{
  Ogre::Radian yawValue, pitchValue;
  switch( key )
  {
  case Qt::Key_Up:
    yawValue = (Ogre::Radian) 0;
    pitchValue = (Ogre::Radian)(Ogre::Math::PI/4);
    break;
  case Qt::Key_Down:
    yawValue = (Ogre::Radian) 0;
    pitchValue = (Ogre::Radian)(-Ogre::Math::PI/4);
    break;
  case Qt::Key_Right:
    yawValue = (Ogre::Radian)(Ogre::Math::PI/4);
    pitchValue = (Ogre::Radian) 0;
    break;
  case Qt::Key_Left:
    yawValue = (Ogre::Radian)(-Ogre::Math::PI/4);
    pitchValue = (Ogre::Radian) 0;
    break;
  }

  _editScenaryCamera->setOrientation(Ogre::Quaternion::IDENTITY);
  _editScenaryCamera->setPosition(getNewCameraRotationPos( yawValue + _yawValue, pitchValue + _pitchValue ));
  _editScenaryCamera->lookAt(_lastPnt);

  _lastYawValue = yawValue;
  _lastPitchValue = pitchValue;
}