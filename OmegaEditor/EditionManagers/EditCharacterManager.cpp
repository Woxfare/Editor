#include "EditCharacterManager.h"
#include <QFileDialog>
#include <string>
#include "Utils/OgreManager.h"
#include <QString>
#include "Utils/CubeUtils.h"
#include "InputData/QOmgWindowMngr.h"

EditCharacterManager * EditCharacterManager::_p_instance = NULL;

EditCharacterManager::EditCharacterManager()
{
	createEditCharacter();
}

EditCharacterManager::~EditCharacterManager() {}

EditCharacterManager*
EditCharacterManager::getInstance()
{
	if(!_p_instance)
		_p_instance = new EditCharacterManager();
	return _p_instance;
}

void
EditCharacterManager::createEditCharacter( void )
{
	OgreManager* ogreMngr = OgreManager::getInstance();
	Ogre::SceneManager* pSceneManager = ogreMngr->getSceneManager();

	Ogre::Light* mainLight = pSceneManager->createLight("EditCharacterLight");
	mainLight->setType(Ogre::Light::LT_POINT);
	mainLight->setPosition(Ogre::Vector3(0, 100, 0));
	mainLight->setDiffuseColour(Ogre::ColourValue(0,0,0,0));

	Ogre::Camera * camera = pSceneManager->createCamera( "EditCharacterCamera" );
	camera->setNearClipDistance( 1.0 );

	Ogre::SceneNode * editChar = pSceneManager->getRootSceneNode()->createChildSceneNode("EditCharacterNode");

	//Head
	editChar->createChildSceneNode("CharacterHeadNode");
	CubeUtils::createCubeByFaces("CharacterHead", 1<<2, 0.0f, 2.4f, 0.0f, 4.f, 2.9f, 2.45f);

	//ArmL
	Ogre::SceneNode * node = editChar->createChildSceneNode("CharacterArmLNode");
	CubeUtils::createCubeByFaces("CharacterArmL", 1<<2, 1.65f, -0.35f, 0.f, .7f, 2.1f, .7f);

	//ArmR
	node = editChar->createChildSceneNode("CharacterArmRNode");
	CubeUtils::createCubeByFaces("CharacterArmR", 1<<2, -1.65f, -0.35f, 0.f, .7f, 2.1f, .7f);

	//Body
	editChar->createChildSceneNode("CharacterBodyNode");
	CubeUtils::createCubeByFaces("CharacterBody", 1<<2, 0.0f, -0.55f, 0.0f, 2.35f, 2.6f, 1.4f);

	//LegL
	node = editChar->createChildSceneNode("CharacterLegLNode");
	CubeUtils::createCubeByFaces("CharacterLegL", 1<<2, 0.5f, -2.7f, 0.0f, .95f, 1.6f, .9f);

	//LegR
	node = editChar->createChildSceneNode("CharacterLegRNode");
	CubeUtils::createCubeByFaces("CharacterLegR", 1<<2, -0.5f, -2.7f, 0.0f, .95f, 1.6f, .9f);
}

void
EditCharacterManager::clearCharacter( void )
{
  OgreManager* ogreMngr = OgreManager::getInstance();
  CubeUtils::clearTexturesOfCube( "CharacterHead" );
  CubeUtils::clearTexturesOfCube( "CharacterBody" );
  CubeUtils::clearTexturesOfCube( "CharacterArmL" );
  CubeUtils::clearTexturesOfCube( "CharacterArmR" );
  CubeUtils::clearTexturesOfCube( "CharacterLegL" );
  CubeUtils::clearTexturesOfCube( "CharacterLegR" );

  // Clear as well the widget
  QOmgWindowMngr::Instance()->GetMainWindow()->getCharacterPartSelector()->changeTextureOfPart( head, "");
  QOmgWindowMngr::Instance()->GetMainWindow()->getCharacterPartSelector()->changeTextureOfPart( body, "");
  QOmgWindowMngr::Instance()->GetMainWindow()->getCharacterPartSelector()->changeTextureOfPart( armLeft, "");
  QOmgWindowMngr::Instance()->GetMainWindow()->getCharacterPartSelector()->changeTextureOfPart( armRight, "");
  QOmgWindowMngr::Instance()->GetMainWindow()->getCharacterPartSelector()->changeTextureOfPart( legLeft, "");
  QOmgWindowMngr::Instance()->GetMainWindow()->getCharacterPartSelector()->changeTextureOfPart( legRight, "");
}

std::map<std::string, std::string>
EditCharacterManager::getCharacterPart( characterParts aPartToGet )
{
	switch( aPartToGet )
	{
	case head:
		return CubeUtils::getTexturesFromCube("CharacterHead");
		break;
	case body:
		return CubeUtils::getTexturesFromCube("CharacterBody");
		break;
	case armLeft:
		return CubeUtils::getTexturesFromCube("CharacterArmL");
		break;
	case armRight:
		return CubeUtils::getTexturesFromCube("CharacterArmR");
		break;
	case legLeft:
		return CubeUtils::getTexturesFromCube("CharacterLegL");
		break;
	case legRight:
		return CubeUtils::getTexturesFromCube("CharacterLegR");
		break;
	}

  return std::map<std::string, std::string>();
}

void
EditCharacterManager::setCharacterPart( characterParts aPart, std::map<std::string, std::string> textures )
{
  switch( aPart )
  {
  case head:
    CubeUtils::setTexturesToCube("CharacterHead", textures);
    break;
  case body:
    CubeUtils::setTexturesToCube("CharacterBody", textures);
    break;
  case armLeft:
    CubeUtils::setTexturesToCube("CharacterArmL", textures);
    break;
  case armRight:
    CubeUtils::setTexturesToCube("CharacterArmR", textures);
    break;
  case legLeft:
    CubeUtils::setTexturesToCube("CharacterLegL", textures);
    break;
  case legRight:
    CubeUtils::setTexturesToCube("CharacterLegR", textures);
    break;
  }

  QOmgWindowMngr::Instance()->GetMainWindow()->getCharacterPartSelector()->changeTextureOfPart( aPart, QString().fromStdString( textures["Front"] ));
}

std::map<std::string, std::map<std::string, std::string>>
EditCharacterManager::getEditCharacter()
{
	std::map<std::string,std::map<std::string, std::string>> textures;

	textures["Head"] = getCharacterPart( head );
	textures["Body"] = getCharacterPart( body );
	textures["ArmL"] = getCharacterPart( armLeft );
	textures["ArmR"] = getCharacterPart( armRight );
	textures["LegL"] = getCharacterPart( legLeft );
	textures["LegR"] = getCharacterPart( legRight );

	return textures;
}

void
EditCharacterManager::changeCharacterColor( int rgb[3] )
{
  CubeUtils::setColorToCube( "CharacterHead", rgb );
  CubeUtils::setColorToCube( "CharacterBody", rgb );
  CubeUtils::setColorToCube( "CharacterArmL", rgb );
  CubeUtils::setColorToCube( "CharacterArmR", rgb );
  CubeUtils::setColorToCube( "CharacterLegL", rgb );
  CubeUtils::setColorToCube( "CharacterLegR", rgb );
}

void
EditCharacterManager::setEditCharacter( std::map<std::string, std::map<std::string, std::string>> textures )
{
  setCharacterPart(head, textures["Head"]);
  setCharacterPart(body, textures["Body"]);
  setCharacterPart(armLeft, textures["ArmL"]);
  setCharacterPart(armRight, textures["ArmR"]);
  setCharacterPart(legLeft, textures["LegL"]);
  setCharacterPart(legRight, textures["LegR"]);
}

void
EditCharacterManager::setPartsToShow( std::vector< characterParts > partsToShow )
{
  Ogre::SceneManager* pSceneManager = OgreManager::getInstance()->getSceneManager();

  pSceneManager->getSceneNode("CharacterHeadNode")->detachAllObjects();
  pSceneManager->getSceneNode("CharacterBodyNode")->detachAllObjects();
  pSceneManager->getSceneNode("CharacterLegLNode")->detachAllObjects();
  pSceneManager->getSceneNode("CharacterLegRNode")->detachAllObjects();
  pSceneManager->getSceneNode("CharacterArmLNode")->detachAllObjects();
  pSceneManager->getSceneNode("CharacterArmRNode")->detachAllObjects();

  std::vector< characterParts >::iterator itb =  partsToShow.begin(), ite = partsToShow.end();

  for( ; itb != ite ; ++itb)
  {
    characterParts part = *itb;

    switch( part )
    {
    case head:
      CubeUtils::attachCubeFaces("CharacterHead");
      break;
    case body:
      CubeUtils::attachCubeFaces("CharacterBody");
      break;
    case armLeft:
      CubeUtils::attachCubeFaces("CharacterArmL");
      break;
    case armRight:
      CubeUtils::attachCubeFaces("CharacterArmR");
      break;
    case legLeft:
      CubeUtils::attachCubeFaces("CharacterLegL");
      break;
    case legRight:
      CubeUtils::attachCubeFaces("CharacterLegR");
      break;
    }
  }
}
