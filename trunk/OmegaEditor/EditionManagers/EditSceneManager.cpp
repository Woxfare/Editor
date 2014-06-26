#include "EditSceneManager.h"
#include <QFileDialog>
#include <string>
#include "Utils/OgreManager.h"
#include <QString>
#include <qDebug>
#include "OmgEntities/OmgSceneObjContainer.h"
#include "Utils/CubeUtils.h"

EditSceneManager * EditSceneManager::_p_instance = NULL;

EditSceneManager::EditSceneManager()
{
  createEditScenary();
  _doors_indexes = 0;
  playerDoorInit = false;
}

EditSceneManager::~EditSceneManager() {}

EditSceneManager* 
EditSceneManager::getInstance()
{
    if(!_p_instance)
        _p_instance = new EditSceneManager();
    return _p_instance;
}

void
EditSceneManager::createEditScenary()
{
  try{
    Ogre::SceneManager* pSceneManager = OgreManager::getInstance()->getSceneManager();

    Ogre::Light* mainLight = pSceneManager->createLight("EditScenaryLight");
    mainLight->setType(Ogre::Light::LT_POINT);
    mainLight->setPosition(Ogre::Vector3(150,150,150));
    mainLight->setDiffuseColour(Ogre::ColourValue(1, 1, 1));
    mainLight->setSpecularColour(Ogre::ColourValue(0.4, 0.4, 0.4));

	Ogre::Light* mainLight2 = pSceneManager->createLight("EditScenaryLight2");
	mainLight2->setType(Ogre::Light::LT_POINT);
	mainLight2->setPosition(Ogre::Vector3(-150,0,-150));
	mainLight2->setDiffuseColour(Ogre::ColourValue::White);
	mainLight2->setSpecularColour(Ogre::ColourValue(0.4, 0.4, 0.4));

    pSceneManager->setAmbientLight(Ogre::ColourValue(1, 1, 1));

    // The degrees of yaw and pitch are set in the controllers
    Ogre::Camera * camera = pSceneManager->createCamera( "EditScenaryCamera" );
    camera->setNearClipDistance( 1.0f );
    camera->setFarClipDistance( 2.0f);

    Ogre::Viewport* pViewport = OgreManager::getInstance()->getWindow()->addViewport( camera );
    OgreManager::getInstance()->setViewport( pViewport );
    pViewport->setBackgroundColour( Ogre::ColourValue( 0,0,0 ) );

    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	pSceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
    Ogre::SceneNode * editScenary = pSceneManager->getRootSceneNode()->createChildSceneNode("EditScenaryNode");
	pSceneManager->setSkyBox(true, "Examples/SpaceSkyBox", 10);
    createBasePlane(60.0, 60.0, -0.5);

	float red[3] = { 1.0f, 0.3f, 0.3f };

	CubeUtils::createDoorEntity("Enemy_Door", red, 1, 2, 1 );
    pSceneManager->getSceneNode("EditScenaryNode")->createChildSceneNode("Enemy_Door_Root");
    Ogre::Entity * doorEntity = pSceneManager->createEntity( "Enemy_Door", "Enemy_DoorMesh");
    Ogre::SceneNode * doorNode = pSceneManager->getSceneNode( "Enemy_Door_Root" )->createChildSceneNode("Enemy_Door");

	float green[3] = { 0.3f, 1.0f, 0.3f };
	CubeUtils::createDoorEntity("Player_Door", green, 1, 2, 1 );
	pSceneManager->getSceneNode("EditScenaryNode")->createChildSceneNode("Player_Door_Root");
	Ogre::Entity * playerEntity = pSceneManager->createEntity( "Player_Door", "Player_DoorMesh");
	Ogre::SceneNode *playerrNode = pSceneManager->getSceneNode( "Player_Door_Root" )->createChildSceneNode("Player_Door");

  }
  catch( Ogre::InternalErrorException e )
  {

  }
}

void
EditSceneManager::createBasePlane(float width, float depth, float y)
{
	Ogre::SceneManager* pSceneManager = OgreManager::getInstance()->getSceneManager();
	Ogre::ManualObject * basePlane = pSceneManager->createManualObject("base_plane");

	Ogre::MaterialPtr materialPtr = Ogre::MaterialManager::getSingleton().create("base_plane",Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	materialPtr->setAmbient(Ogre::ColourValue(0,0,0));
	materialPtr->setSpecular(Ogre::ColourValue(0.5,0.5,0.5));
	materialPtr->setDiffuse(Ogre::ColourValue(1,1,1));
	
	basePlane->begin("base_plane", Ogre::RenderOperation::OT_TRIANGLE_LIST);
    basePlane->normal(0,1,0);
    basePlane->position(width/2.0f, y, depth/2.0f);
    basePlane->textureCoord(1, 1);
    basePlane->position( width/2.0f, y, -depth/2.0f);
    basePlane->textureCoord(1, 0);
    basePlane->position( -width/2.0f, y, -depth/2.0f);
    basePlane->textureCoord(0, 0);
    basePlane->position(-width/2.0f, y, depth/2.0f);
    basePlane->textureCoord(0, 1);
    basePlane->quad(0,1,2,3);
    basePlane->end();

	basePlane->convertToMesh("base_plane");

	Ogre::SceneNode *basePlaneNode = pSceneManager->getSceneNode("EditScenaryNode")->createChildSceneNode( "base_plane" );
	Ogre::Entity * Plane = pSceneManager->createEntity("base_plane");
	basePlaneNode->attachObject( Plane );
}

void
EditSceneManager::changeBasePlaneTexture( std::string textureName )
{
	if( textureName == "" )
		return;

    try{
        Ogre::MaterialPtr materialPtr = Ogre::MaterialManager::getSingleton().getByName( "base_plane", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
        materialPtr->getTechnique(0)->getPass(0)->removeAllTextureUnitStates();
        materialPtr->getTechnique(0)->getPass(0)->createTextureUnitState( textureName );
    } catch( ... ) {
    }
}

void
EditSceneManager::changeBasePlaneColor(int rgb[3])
{
    try
    {
        Ogre::MaterialPtr materialPtr = Ogre::MaterialManager::getSingleton().getByName("base_plane", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
		materialPtr->setAmbient(Ogre::ColourValue(rgb[0]/256.0f,rgb[1]/256.0f,rgb[2]/256.0f));
        materialPtr->setDiffuse(Ogre::ColourValue(rgb[0]/256.0f,rgb[1]/256.0f,rgb[2]/256.0f));
    } catch(...)
    {

    }
}

void
EditSceneManager::addCubeToScene(std::string cubeName, Ogre::Vector3 position )
{
  Ogre::SceneManager* pSceneManager = OgreManager::getInstance()->getSceneManager();
  // Search if the cubeName is already in the _cubes map
  std::map<std::string, std::vector<std::string> >::iterator it = _cubes.find( cubeName );
  std::vector<std::string> auxVec;
  int cubeIndex = 1;
  
  if( _cubes.end() != it) // It's on the map
  {
    auxVec    = _cubes[cubeName]; // Get the vector of cubes 
    cubeIndex = _indexes[cubeName]; // Get the next index
  }

  // Get the name of the new node
  QString nodeName = QString().fromStdString(cubeName) + QString("_%1").arg(cubeIndex);

  // Add 1 to the index for the next cube and store the new index in the index map
  ++cubeIndex;
  _indexes[cubeName] = cubeIndex;

  // Store in the map of positions the position of the new node
  _positions[nodeName.toStdString()] = position;

  // Store in the cubes map the new vector of cubes
  auxVec.push_back( nodeName.toStdString() );
  _cubes[cubeName] = auxVec;

  QString meshName = QString().fromStdString(cubeName) + QString(".mesh");
  // Create the entity and the node for the new cube
  Ogre::Entity *cube = pSceneManager->createEntity( nodeName.toStdString(), meshName.toStdString() );
  Ogre::SceneNode *cubeNode = pSceneManager->getSceneNode("EditScenaryNode")->createChildSceneNode( nodeName.toStdString(), position );
  cubeNode->attachObject( cube );
  cube->setCastShadows(false);

}

void
EditSceneManager::addDoorToScene( Ogre::Vector3 position, bool isPlayerDoor )
{
	Ogre::SceneManager* pSceneManager = OgreManager::getInstance()->getSceneManager();
	if( isPlayerDoor )
	{
	  if( playerDoorInit )
		  return;

	  // Get the name of the new node
	  QString nodeName = QString().fromStdString("Player_Door") + QString("_1");
	  // Create the entity and the node for the new cube
	  Ogre::Entity *cube = pSceneManager->createEntity( nodeName.toStdString(), "Player_DoorMesh" );
	  Ogre::SceneNode *cubeNode = pSceneManager->getSceneNode("EditScenaryNode")->createChildSceneNode( nodeName.toStdString(), position );

	  cubeNode->attachObject( cube );
	  cube->setCastShadows(false);
	  playerDoorInit = true;
	  playerDoorPos = position;
	  return;
	}

	// Get the name of the new node
	QString nodeName = QString().fromStdString("Enemy_Door") + QString("_%1").arg(_doors_indexes);

	// Add 1 to the index for the next cube and store the new index in the index map
	++_doors_indexes;

	// Store in the map of positions the position of the new node
	_doors_positions[nodeName.toStdString()] = position;

	// Create the entity and the node for the new cube
	Ogre::Entity *cube = pSceneManager->createEntity( nodeName.toStdString(), "Enemy_DoorMesh" );
	Ogre::SceneNode *cubeNode = pSceneManager->getSceneNode("EditScenaryNode")->createChildSceneNode( nodeName.toStdString(), position );

	cubeNode->attachObject( cube );
	cube->setCastShadows(false);
}

void
EditSceneManager::deleteCubeFromScene( std::string cubeName )
{
  Ogre::SceneManager* pSceneManager = OgreManager::getInstance()->getSceneManager();
  // Get the name of the cube with out the _x
  std::string name = QString(cubeName.c_str()).split('_')[0].toStdString();

  std::vector<std::string> auxVec = _cubes[name];
  std::vector<std::string>::iterator it;
  for(it = auxVec.begin(); it != auxVec.end(); ++it)
  {
      if(cubeName == (*it))
      {
        auxVec.erase(it);
        _positions.erase(cubeName);
        _cubes[name] = auxVec;
        try{
          Ogre::SceneNode * node = pSceneManager->getSceneNode(cubeName);
          node->detachAllObjects();
          pSceneManager->destroySceneNode(node);
          pSceneManager->destroyEntity( cubeName );
        } catch( ... )
        {

        }
        return;
      }
  }
  
}

void
EditSceneManager::deleteDoorFromScene( std::string doorName, bool isPlayerDoor )
{
	Ogre::SceneManager* pSceneManager = OgreManager::getInstance()->getSceneManager();
	if( isPlayerDoor )
	{
		if( !playerDoorInit )
			return;
		try{
			Ogre::SceneNode * node = pSceneManager->getSceneNode(doorName);
			node->detachAllObjects();
			pSceneManager->destroySceneNode( node);
			pSceneManager->destroyEntity( doorName );
		} catch( ... )
		{

		}
		playerDoorInit = false;
		return;
	}

  if( _doors_positions.find( doorName ) != _doors_positions.end())
  {
    _doors_positions.erase( doorName );
    try{
      Ogre::SceneNode * node = pSceneManager->getSceneNode(doorName);
      node->detachAllObjects();
      pSceneManager->destroySceneNode( node);
      pSceneManager->destroyEntity( doorName );
    } catch( ... )
    {

    }
  }
}

int
EditSceneManager::getNumberOfCubesInTheScene( void )
{
  return _positions.size();
}

void
EditSceneManager::clearScenary( void )
{
  Ogre::SceneManager* pSceneManager = OgreManager::getInstance()->getSceneManager();

  Ogre::SceneNode *scenaryNode = pSceneManager->getSceneNode("EditScenaryNode");
  scenaryNode->detachAllObjects();

  // Iterates through the map of scene cubes and delete the meshes
  std::map<std::string, std::vector<std::string> >::iterator it = _cubes.begin();

  while( it != _cubes.end() )
  {
    std::vector<std::string> auxVec = it->second;
    int nCubes = auxVec.size();
    for( int i = 0; i < nCubes ; ++i )
    {
      std::string nameObject = auxVec[i];
      deleteCubeFromScene( nameObject );
    }
    ++it;
  }

  // Clear the map containers
  _positions.clear();
  _cubes.clear();
  _indexes.clear();

  removeBasePlaneTexture();

  for( int i = 0; i < _doors_indexes; ++i )
  {
    try{
      std::string nameObject = "Enemy_Door" + QString("_%1").arg(i).toStdString();
      deleteDoorFromScene( nameObject );
    } catch( Ogre::Exception e )
    {

    }
  }

  _doors_positions.clear();
  _doors_indexes = 0;

  if( playerDoorInit )
  {
	  try{
		  std::string nameObject = "Player_Door" + QString("_1").toStdString();
		  deleteDoorFromScene( nameObject,true );
	  } catch( Ogre::Exception e )
	  {

	  }
	  playerDoorInit = false;
  }

  
}

void
EditSceneManager::removeBasePlaneTexture( void )
{
  try{
    Ogre::MaterialPtr materialPtr = Ogre::MaterialManager::getSingleton().getByName( "base_plane", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    materialPtr->getTechnique(0)->getPass(0)->removeAllTextureUnitStates();
  } catch( ... ) {

  }
}

std::vector< std::pair < std::string, std::vector< Ogre::Vector3 > > >
EditSceneManager::getEditScenary( void )
{
  std::vector< std::pair < std::string, std::vector< Ogre::Vector3 > > > sceneToReturn;
  std::map<std::string, std::vector<std::string> >::iterator it = _cubes.begin(),
                                                             it_end = _cubes.end();
  for(; it != it_end; ++it )
  {
    // Iterate over the vector of each cube and add the reference to the position
    std::string cubeName = it->first;
    std::vector<std::string> auxVec = it->second;
    
    std::vector<Ogre::Vector3> vectorOfPositions;
    int nCubes = auxVec.size();

    for( int i = 0; i < nCubes ; ++i )
    {
      Ogre::Vector3 position = _positions[auxVec[i]];
      vectorOfPositions.push_back(position);
    }
    sceneToReturn.push_back( std::make_pair( cubeName, vectorOfPositions ) );
  }

  return sceneToReturn;
}

void
EditSceneManager::setEditScenary( std::vector< std::pair < std::string, std::vector< Ogre::Vector3 > > > sceneToSet )
{
  // Clear the edit scenery before adding a new one
  clearScenary();

  // Add to the scene the new cubes!!
  std::vector< std::pair < std::string, std::vector< Ogre::Vector3 > > >::iterator it = sceneToSet.begin(),
                                                                                   it_end = sceneToSet.end();

  for(; it != it_end; ++it )
  {
    std::pair < std::string, std::vector< Ogre::Vector3 > > auxPair = (*it);

    std::string cubeName = auxPair.first;

    std::vector< Ogre::Vector3 >::iterator it_positions = auxPair.second.begin(), it_positions_end = auxPair.second.end();
    for(; it_positions != it_positions_end ; ++it_positions)
      addCubeToScene(cubeName, (*it_positions));
  }
}

void
EditSceneManager::setEnemyDoors( std::vector< Ogre::Vector3 > doors )
{
  // Add to the scene the new cubes!!
  std::vector< Ogre::Vector3 >::iterator it = doors.begin(),it_end = doors.end();

  for(; it != it_end; ++it )
    addDoorToScene( *it );
}

void
EditSceneManager::changeNodesInfo( std::string oldBaseName, std::string newBaseName )
{
  Ogre::SceneManager* pSceneManager = OgreManager::getInstance()->getSceneManager();
  // Get the vector of the _mapSceneCubes
  std::vector<std::string> vectorOfCubes = _cubes[oldBaseName], newVector;
  int nCubes = vectorOfCubes.size();

  if( vectorOfCubes.empty())
    return;

  for( int i = 0; i < nCubes; ++i )
  {
    try
    {
      Ogre::SceneNode * oldNode = pSceneManager->getSceneNode(vectorOfCubes[i]);
      Ogre::Vector3 pos(oldNode->getPosition());
      oldNode->detachAllObjects();
      pSceneManager->destroySceneNode(oldNode);

      QString newName = QString().fromStdString(newBaseName) + QString("_%1").arg(i+1);
      //pSceneManager->getSceneNode("EditScenaryNode")->createChildSceneNode( newName.toStdString(), pos);
      newVector.push_back(newName.toStdString());

      // Changing the object in the map of positions
      _positions.erase(vectorOfCubes[i]); 
      _positions[newName.toStdString()] = pos;

    } catch (Ogre::Exception e) {

    }
  }

  // Deleting the old entry to the map
  _cubes.erase(oldBaseName);

  // Adding the new entry to the map
  _cubes[newBaseName] = newVector;
}

void
EditSceneManager::deleteEntityGroup(std::string baseName)
{
  Ogre::SceneManager* pSceneManager = OgreManager::getInstance()->getSceneManager();
  std::vector<std::string> vectorOfCubes = _cubes[baseName];
  int nCubes = vectorOfCubes.size();
  for( int i = 0; i < nCubes; ++i )
  {
    try
    {
      pSceneManager->destroyEntity(vectorOfCubes[i]);
    }
    catch (Ogre::Exception e)
    {

    }
  }
}

void
EditSceneManager::createEntityGroup(std::string baseName)
{
  Ogre::SceneManager* pSceneManager = OgreManager::getInstance()->getSceneManager();

  // Get the mesh name
  QString meshName = QString().fromStdString(baseName) + QString(".mesh");

  std::vector<std::string> vectorOfCubes = _cubes[baseName];
  int nCubes = vectorOfCubes.size();
  for( int i = 0; i < nCubes; ++i)
  {
    try
    {
      Ogre::Vector3 position = _positions[vectorOfCubes[i]];
      Ogre::Entity *cube = pSceneManager->createEntity( vectorOfCubes[i], meshName.toStdString() );
      Ogre::SceneNode *cubeNode = pSceneManager->getSceneNode("EditScenaryNode")->createChildSceneNode( vectorOfCubes[i], position );
      cubeNode->attachObject( cube );
      cube->setCastShadows(false);
    }
    catch (Ogre::Exception e)
    {

    }
  }
}

void
EditSceneManager::initializeEnemyDoorsMesh(Ogre::Vector3 position, float sizex, float sizey, float sizez)
{
	float maxX = position.x + sizex/2;
	float minX = position.x - sizex/2;
	float maxY = position.y + 3*sizey/4;
	float minY = position.y - sizey/4;
	float maxZ = position.z + sizez/2;
	float minZ = position.z - sizez/2;

	Ogre::SceneManager* pSceneManager = OgreManager::getInstance()->getSceneManager();
	
	Ogre::ManualObject * enemyDoor = pSceneManager->createManualObject("enemy_door");

	Ogre::MaterialPtr mat = Ogre::MaterialManager::getSingleton().create("enemyDoorMat", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    mat->setAmbient(Ogre::ColourValue(0.3f,0.3f,0.3f,0.4f));
	mat->getTechnique(0)->getPass(0)->setDiffuse(Ogre::ColourValue(0.3f,0.3f,0.3f,0.4f));
	mat->getTechnique(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
	mat->getTechnique(0)->setDepthWriteEnabled(false);

	//Bottom
	enemyDoor->begin("enemyDoorMat", Ogre::RenderOperation::OT_TRIANGLE_LIST);
	enemyDoor->normal(0,1,0);
	enemyDoor->position(maxX, minY, maxZ);
	enemyDoor->textureCoord(1, 0);
	enemyDoor->position( maxX, minY, minZ);
	enemyDoor->textureCoord(1, 1);
	enemyDoor->position( minX, minY, minZ);
	enemyDoor->textureCoord(0, 1);
	enemyDoor->position(minX, minY, maxZ);
	enemyDoor->textureCoord(0, 0);
	enemyDoor->quad(3,2,1,0);
	enemyDoor->end();
    
	// Top
	enemyDoor->begin("enemyDoorMat", Ogre::RenderOperation::OT_TRIANGLE_LIST);
	enemyDoor->normal(0,1,0);
	enemyDoor->position(maxX, maxY, maxZ);
	enemyDoor->textureCoord(1, 1);
	enemyDoor->position( maxX, maxY, minZ);
	enemyDoor->textureCoord(1, 0);
	enemyDoor->position( minX, maxY, minZ);
	enemyDoor->textureCoord(0, 0);
	enemyDoor->position(minX, maxY, maxZ);
	enemyDoor->textureCoord(0, 1);
	enemyDoor->quad(0,1,2,3);
	enemyDoor->end();

    // Left
	enemyDoor->begin("enemyDoorMat", Ogre::RenderOperation::OT_TRIANGLE_LIST);
	enemyDoor->normal(1,0,0);
	enemyDoor->position(minX, minY, maxZ);
	enemyDoor->textureCoord(1, 1);
	enemyDoor->position( minX, maxY, maxZ);
	enemyDoor->textureCoord(1, 0);
	enemyDoor->position( minX, maxY, minZ);
	enemyDoor->textureCoord(0, 0);
	enemyDoor->position(minX, minY, minZ);
	enemyDoor->textureCoord(0, 1);
	enemyDoor->quad(0,1,2,3);
	enemyDoor->end();

    // Right
	enemyDoor->begin("enemyDoorMat", Ogre::RenderOperation::OT_TRIANGLE_LIST);
	enemyDoor->normal(1,0,0);
	enemyDoor->position(maxX, minY, maxZ);
	enemyDoor->textureCoord(0, 1);
	enemyDoor->position( maxX, maxY, maxZ);
	enemyDoor->textureCoord(0, 0);
	enemyDoor->position( maxX, maxY, minZ);
	enemyDoor->textureCoord(1, 0);
	enemyDoor->position(maxX, minY, minZ);
	enemyDoor->textureCoord(1, 1);
	enemyDoor->quad(3,2,1,0);
	enemyDoor->end();

	//Front
	enemyDoor->begin("enemyDoorMat", Ogre::RenderOperation::OT_TRIANGLE_LIST);
	enemyDoor->normal(0,0,1);
	enemyDoor->position( minX, minY, maxZ);
	enemyDoor->textureCoord(0, 1);
	enemyDoor->position( minX, maxY, maxZ);
	enemyDoor->textureCoord(0, 0);
	enemyDoor->position( maxX, maxY, maxZ);
	enemyDoor->textureCoord(1, 0);
	enemyDoor->position( maxX, minY, maxZ);
	enemyDoor->textureCoord(1, 1);
	enemyDoor->quad(3,2,1,0);
	enemyDoor->end();

	//Back
	enemyDoor->begin("enemyDoorMat", Ogre::RenderOperation::OT_TRIANGLE_LIST);
	enemyDoor->normal(0,0,1);
	enemyDoor->position(minX, minY, minZ);
	enemyDoor->textureCoord(1, 1);
	enemyDoor->position(minX, maxY, minZ);
	enemyDoor->textureCoord(1, 0);
	enemyDoor->position( maxX, maxY, minZ);
	enemyDoor->textureCoord(0, 0);
	enemyDoor->position(maxX, minY, minZ);
	enemyDoor->textureCoord(0, 1);
	enemyDoor->quad(0,1,2,3);
	enemyDoor->end();

	enemyDoor->convertToMesh("Enemy_Door");
	enemyDoor->setCastShadows(false);
}

std::vector< Ogre::Vector3 >
EditSceneManager::getEnemiesDoors( void )
{
  std::map<std::string, Ogre::Vector3>::iterator it = _doors_positions.begin(), itEnd = _doors_positions.end();

  std::vector< Ogre::Vector3 > vPositions;

  for(;it!=itEnd;++it)
    vPositions.push_back( it->second );

  return vPositions;
}

Ogre::Vector3
EditSceneManager::getPlayerDoor( void )
{
	return playerDoorPos;
}