#include "EditCubeManager.h"
#include <QFileDialog>
#include <string>
#include "Utils/OgreManager.h"
#include <QString>
#include "Utils/CubeUtils.h"

EditCubeManager * EditCubeManager::_p_instance = NULL;

EditCubeManager::EditCubeManager()
{
  createEditCube();
  _lastTexture = "";
}

EditCubeManager::~EditCubeManager() {}

EditCubeManager*
EditCubeManager::getInstance()
{
  if(!_p_instance)
    _p_instance = new EditCubeManager();
  return _p_instance;
}

void
EditCubeManager::createEditCube( void )
{
  Ogre::SceneManager* pSceneManager = OgreManager::getInstance()->getSceneManager();
  Ogre::Light* mainLight = pSceneManager->createLight("EditCubeLight");
  mainLight->setType(Ogre::Light::LT_POINT);
  mainLight->setPosition(Ogre::Vector3(0, 100, 0));
  mainLight->setDiffuseColour(Ogre::ColourValue(0,0,0,0));

  // The degrees of yaw and pitch are stetted in the controllers
  Ogre::Camera * camera = pSceneManager->createCamera( "EditCubeCamera" );
  camera->setNearClipDistance( 1.0 );

  pSceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);
  Ogre::SceneNode * editCube = pSceneManager->getRootSceneNode()->createChildSceneNode("EditCubeNode");

  CubeUtils::createCubeByFaces("EditCube", 1<<1);
  editCube->scale(Ogre::Vector3(1,1,1));
}

void
EditCubeManager::clearEditCube( void )
{
  CubeUtils::clearTexturesOfCube( "EditCube" );
}

std::map<std::string, std::string>
EditCubeManager::getEditCube( void )  
{
  return CubeUtils::getTexturesFromCube( "EditCube" );
}

void
EditCubeManager::changeEditCubeColor( int rgb[3] )
{
  CubeUtils::setColorToCube( "EditCube", rgb );
}

void
EditCubeManager::changeEditCubeTextures( std::map<std::string, std::string> textures )
{
  CubeUtils::setTexturesToCube( "EditCube", textures );
}

void
EditCubeManager::setAllTexturesEqual( void )
{
  if( _lastTexture == "" )
    return;

  std::map<std::string, std::string > textures = CubeUtils::getTexturesFromCube("EditCube");
  std::map<std::string, std::string >::iterator it =  textures.begin(), it_end = textures.end();

  for(; it!=it_end; ++it )
    (*it).second = _lastTexture;
  
  CubeUtils::setTexturesToCube( "EditCube", textures );
}

void
EditCubeManager::setLastTexture( std::string texture )
{
  _lastTexture = texture;
}

