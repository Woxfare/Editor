#include "CubeUtils.h"

#include <QDebug>
#include "Display\OgreManager.h"

void
CubeUtils::setTexturesToCube( Ogre::String baseName, std::map<std::string, std::string>  textures )
{
  try {
    std::map<std::string, std::string>::iterator it = textures.begin(), it_end = textures.end();

    for( ; it!=it_end; ++it )
    {
      if( (std::string)(*it).second == "" )
        continue;

      std::string completeNameFace = baseName + "Mat" + (std::string)(*it).first; // Generate all the name of the material

      Ogre::MaterialPtr materialPtr = Ogre::MaterialManager::getSingleton().getByName(completeNameFace, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
      materialPtr->getTechnique(0)->getPass(0)->removeAllTextureUnitStates();
      materialPtr->getTechnique(0)->getPass(0)->createTextureUnitState( (std::string)(*it).second );
    }
  } catch(Ogre::Exception e) {

  }

}

void
CubeUtils::setColorToCube( Ogre::String baseName, int rgb[3] )
{
  try{
    float red, green, blue;
    red = rgb[0]/255.0f;
    green = rgb[1]/255.0f;
    blue = rgb[2]/255.0f;

    std::string faceName = baseName + "MatTop";
    Ogre::MaterialPtr mat = Ogre::MaterialManager::getSingleton().getByName( faceName, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    mat->setAmbient(Ogre::ColourValue(red,green,blue));
	mat->setDiffuse(Ogre::ColourValue(red, green, blue));

    faceName = baseName + "MatBottom";
    mat = Ogre::MaterialManager::getSingleton().getByName( faceName, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    mat->setAmbient(Ogre::ColourValue(red,green,blue));
	mat->setDiffuse(Ogre::ColourValue(red, green, blue));

    faceName = baseName + "MatLeft";
    mat = Ogre::MaterialManager::getSingleton().getByName( faceName, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    mat->setAmbient(Ogre::ColourValue(red,green,blue));
	mat->setDiffuse(Ogre::ColourValue(red, green, blue));

    faceName = baseName + "MatRight";
    mat = Ogre::MaterialManager::getSingleton().getByName( faceName, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    mat->setAmbient(Ogre::ColourValue(red,green,blue));
	mat->setDiffuse(Ogre::ColourValue(red, green, blue));

    faceName = baseName + "MatFront";
    mat = Ogre::MaterialManager::getSingleton().getByName( faceName, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    mat->setAmbient(Ogre::ColourValue(red,green,blue));
	mat->setDiffuse(Ogre::ColourValue(red, green, blue));

    faceName = baseName + "MatBack";
    mat = Ogre::MaterialManager::getSingleton().getByName( faceName, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    mat->setAmbient(Ogre::ColourValue(red,green,blue));
	mat->setDiffuse(Ogre::ColourValue(red, green, blue));

  } catch(Ogre::Exception e)
  {
  
  }
}

void
CubeUtils::clearTexturesOfCube( Ogre::String baseName )
{
  try{
    Ogre::MaterialManager * materialManager = Ogre::MaterialManager::getSingletonPtr();

    Ogre::MaterialPtr mat = materialManager->getByName(baseName + "MatTop");
    if(mat->getTechnique(0)->getPass(0)->getNumTextureUnitStates())
      mat->getTechnique(0)->getPass(0)->removeAllTextureUnitStates();

    mat = materialManager->getByName(baseName + "MatBottom");
    if(mat->getTechnique(0)->getPass(0)->getNumTextureUnitStates())
      mat->getTechnique(0)->getPass(0)->removeAllTextureUnitStates();

    mat = materialManager->getByName(baseName + "MatLeft");
    if(mat->getTechnique(0)->getPass(0)->getNumTextureUnitStates())
      mat->getTechnique(0)->getPass(0)->removeAllTextureUnitStates();

    mat = materialManager->getByName(baseName + "MatRight");
    if(mat->getTechnique(0)->getPass(0)->getNumTextureUnitStates())
      mat->getTechnique(0)->getPass(0)->removeAllTextureUnitStates();

    mat = materialManager->getByName(baseName + "MatFront");
    if(mat->getTechnique(0)->getPass(0)->getNumTextureUnitStates())
      mat->getTechnique(0)->getPass(0)->removeAllTextureUnitStates();

    mat = materialManager->getByName(baseName + "MatBack");
    if(mat->getTechnique(0)->getPass(0)->getNumTextureUnitStates())
      mat->getTechnique(0)->getPass(0)->removeAllTextureUnitStates();

  } catch(Ogre::Exception e) 
  {
    qDebug() << QString().fromStdString( baseName ) << "Textures not deleted";
  }
}

std::map<std::string, std::string>
CubeUtils::getTexturesFromCube(Ogre::String baseName)
{
  std::map<std::string, std::string> textures;

  try {
    Ogre::MaterialManager * materialManager = Ogre::MaterialManager::getSingletonPtr();

    Ogre::MaterialPtr mat = materialManager->getByName(baseName + "MatTop");
    if(mat->getTechnique(0)->getPass(0)->getNumTextureUnitStates())
      textures["Top"] = mat->getTechnique(0)->getPass(0)->getTextureUnitState(0)->getTextureName();
    else
      textures["Top"] = "";

    mat = materialManager->getByName(baseName + "MatBottom");
    if(mat->getTechnique(0)->getPass(0)->getNumTextureUnitStates())
      textures["Bottom"] = mat->getTechnique(0)->getPass(0)->getTextureUnitState(0)->getTextureName();
    else
      textures["Bottom"] = "";

    mat = materialManager->getByName(baseName + "MatLeft");
    if(mat->getTechnique(0)->getPass(0)->getNumTextureUnitStates())
      textures["Left"] = mat->getTechnique(0)->getPass(0)->getTextureUnitState(0)->getTextureName();
    else
      textures["Left"] = "";

    mat = materialManager->getByName(baseName + "MatRight");
    if(mat->getTechnique(0)->getPass(0)->getNumTextureUnitStates())
      textures["Right"] = mat->getTechnique(0)->getPass(0)->getTextureUnitState(0)->getTextureName();
    else
      textures["Right"] = "";

    mat = materialManager->getByName(baseName + "MatFront");
    if(mat->getTechnique(0)->getPass(0)->getNumTextureUnitStates())
      textures["Front"] = mat->getTechnique(0)->getPass(0)->getTextureUnitState(0)->getTextureName();
    else
      textures["Front"] = "";

    mat = materialManager->getByName(baseName + "MatBack");
    if(mat->getTechnique(0)->getPass(0)->getNumTextureUnitStates())
      textures["Back"] = mat->getTechnique(0)->getPass(0)->getTextureUnitState(0)->getTextureName();
    else
      textures["Back"] = "";
   } catch(Ogre::Exception e){

   }

  return textures;
}

void
CubeUtils::createCubeByFaces(Ogre::String name, Ogre::uint32 mask , float x, float y, float z, float xSize, float ySize, float zSize )
{
  float ambientColor[3] = {1,1,1};
  createCubeByFaces(name, ambientColor, mask, x, y, z, xSize, ySize, zSize );
}

void
CubeUtils::createCubeByFaces(Ogre::String name, float ambientColor[3],  Ogre::uint32 mask, float x, float y, float z, float xSize, float ySize, float zSize )
{
  Ogre::String nameFace;
  Ogre::String nameMat;
  Ogre::ManualObject* manual;
  Ogre::SceneManager* pSceneManager = OgreManager::getInstance()->getSceneManager();

  float maxX = x + xSize/2;
  float minX = x - xSize/2;
  float maxY = y + ySize/2;
  float minY = y - ySize/2;
  float maxZ = z + zSize/2;
  float minZ = z - zSize/2;

  // Bottom
  nameFace = name + "Bottom";
  manual =  pSceneManager->createManualObject(nameFace);

  nameMat = name + "MatBottom";
  Ogre::MaterialPtr bot = Ogre::MaterialManager::getSingleton().create(nameMat, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
  bot->setAmbient(Ogre::ColourValue(ambientColor[0], ambientColor[1], ambientColor[2]));

  manual->begin(nameMat, Ogre::RenderOperation::OT_TRIANGLE_LIST);
  manual->normal(0,1,0);
  manual->position(maxX, minY, maxZ);
  manual->textureCoord(1, 0);
  manual->position( maxX, minY, minZ);
  manual->textureCoord(1, 1);
  manual->position( minX, minY, minZ);
  manual->textureCoord(0, 1);
  manual->position(minX, minY, maxZ);
  manual->textureCoord(0, 0);
  manual->quad(3,2,1,0);
  manual->end();

  manual->setQueryFlags(mask);
  pSceneManager->getSceneNode(name + "Node")->attachObject(manual);

  // Top
  nameFace = name + "Top";
  manual =  pSceneManager->createManualObject(nameFace);

  nameMat = name + "MatTop";
  Ogre::MaterialPtr top = Ogre::MaterialManager::getSingleton().create(nameMat, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
  top->setAmbient(Ogre::ColourValue(ambientColor[0], ambientColor[1], ambientColor[2]));

  manual->begin(nameMat, Ogre::RenderOperation::OT_TRIANGLE_LIST);
  manual->normal(0,1,0);
  manual->position(maxX, maxY, maxZ);
  manual->textureCoord(1, 1);
  manual->position( maxX, maxY, minZ);
  manual->textureCoord(1, 0);
  manual->position( minX, maxY, minZ);
  manual->textureCoord(0, 0);
  manual->position(minX, maxY, maxZ);
  manual->textureCoord(0, 1);
  manual->quad(0,1,2,3);
  manual->end();

  manual->setQueryFlags(mask);
  pSceneManager->getSceneNode(name + "Node")->attachObject(manual);

  nameFace = name + "Left";
  manual =  pSceneManager->createManualObject(nameFace);

  nameMat = name + "MatLeft";
  Ogre::MaterialPtr left = Ogre::MaterialManager::getSingleton().create(nameMat, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
  left->setAmbient(Ogre::ColourValue(ambientColor[0], ambientColor[1], ambientColor[2]));

  // Left
  manual->begin(nameMat, Ogre::RenderOperation::OT_TRIANGLE_LIST);
  manual->normal(1,0,0);
  manual->position(minX, minY, maxZ);
  manual->textureCoord(1, 1);
  manual->position( minX, maxY, maxZ);
  manual->textureCoord(1, 0);
  manual->position( minX, maxY, minZ);
  manual->textureCoord(0, 0);
  manual->position(minX, minY, minZ);
  manual->textureCoord(0, 1);
  manual->quad(0,1,2,3);
  manual->end();

  manual->setQueryFlags(mask);
  pSceneManager->getSceneNode(name + "Node")->attachObject(manual);

  nameFace = name + "Right";
  manual =  pSceneManager->createManualObject(nameFace);

  nameMat = name + "MatRight";
  Ogre::MaterialPtr right = Ogre::MaterialManager::getSingleton().create(nameMat, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
  right->setAmbient(Ogre::ColourValue(ambientColor[0], ambientColor[1], ambientColor[2]));

  // Right
  manual->begin(nameMat, Ogre::RenderOperation::OT_TRIANGLE_LIST);
  manual->normal(1,0,0);
  manual->position(maxX, minY, maxZ);
  manual->textureCoord(0, 1);
  manual->position( maxX, maxY, maxZ);
  manual->textureCoord(0, 0);
  manual->position( maxX, maxY, minZ);
  manual->textureCoord(1, 0);
  manual->position(maxX, minY, minZ);
  manual->textureCoord(1, 1);
  manual->quad(3,2,1,0);
  manual->end();

  manual->setQueryFlags(mask);
  pSceneManager->getSceneNode(name + "Node")->attachObject(manual);

  // Front
  nameFace = name + "Front";
  manual =  pSceneManager->createManualObject(nameFace);

  nameMat = name + "MatFront";
  Ogre::MaterialPtr front = Ogre::MaterialManager::getSingleton().create(nameMat, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
  front->setAmbient(Ogre::ColourValue(ambientColor[0], ambientColor[1], ambientColor[2]));

  manual->begin(nameMat, Ogre::RenderOperation::OT_TRIANGLE_LIST);
  manual->normal(0,0,1);
  manual->position( minX, minY, maxZ);
  manual->textureCoord(0, 1);
  manual->position( minX, maxY, maxZ);
  manual->textureCoord(0, 0);
  manual->position( maxX, maxY, maxZ);
  manual->textureCoord(1, 0);
  manual->position( maxX, minY, maxZ);
  manual->textureCoord(1, 1);
  manual->quad(3,2,1,0);
  manual->end();

  manual->setQueryFlags(mask);
  pSceneManager->getSceneNode(name + "Node")->attachObject(manual);

  // Back
  nameFace = name + "Back";
  manual =  pSceneManager->createManualObject(nameFace);

  nameMat = name + "MatBack";
  Ogre::MaterialPtr back = Ogre::MaterialManager::getSingleton().create(nameMat, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
  back->setAmbient(Ogre::ColourValue(ambientColor[0], ambientColor[1], ambientColor[2]));

  manual->begin(nameMat, Ogre::RenderOperation::OT_TRIANGLE_LIST);
  manual->normal(0,0,1);
  manual->position(minX, minY, minZ);
  manual->textureCoord(1, 1);
  manual->position(minX, maxY, minZ);
  manual->textureCoord(1, 0);
  manual->position( maxX, maxY, minZ);
  manual->textureCoord(0, 0);
  manual->position(maxX, minY, minZ);
  manual->textureCoord(0, 1);
  manual->quad(0,1,2,3);
  manual->end();

  manual->setQueryFlags(mask);
  pSceneManager->getSceneNode(name + "Node")->attachObject(manual);
}

void
CubeUtils::createCubeMesh(std::string name, std::map<std::string, std::string> textures, int rgb[3])
{
  Ogre::SceneManager* pSceneManager = OgreManager::getInstance()->getSceneManager();
  Ogre::ManualObject* manual;
  try
  {
    manual = pSceneManager->createManualObject(name);
  } catch(Ogre::Exception e)
  {
    pSceneManager->destroyManualObject(name);
    manual = pSceneManager->createManualObject(name);
  }

  Ogre::ColourValue baseColour(rgb[0]/255.0f,rgb[1]/255.0f,rgb[2]/255.0f);

  //Setting up material of every face.
  Ogre::MaterialPtr top = Ogre::MaterialManager::getSingleton().create(name+"MatTop", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
  top->setAmbient(Ogre::ColourValue(0,0,0));
  top->setSpecular(Ogre::ColourValue(0.5,0.5,0.5));
  top->getTechnique(0)->getPass(0)->setDiffuse(baseColour);
  if(textures["Top"]!="")
    top->getTechnique(0)->getPass(0)->createTextureUnitState(textures["Top"]);

  Ogre::MaterialPtr bot = Ogre::MaterialManager::getSingleton().create(name+"MatBottom", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
  bot->setAmbient(Ogre::ColourValue(0,0,0));
  bot->setSpecular(Ogre::ColourValue(0.5,0.5,0.5));
  bot->getTechnique(0)->getPass(0)->setDiffuse(baseColour);
  if(textures["Bottom"]!="")
    bot->getTechnique(0)->getPass(0)->createTextureUnitState(textures["Bottom"]);

  Ogre::MaterialPtr left = Ogre::MaterialManager::getSingleton().create(name+"MatLeft", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
  left->setAmbient(Ogre::ColourValue(0,0,0));
  left->setSpecular(Ogre::ColourValue(0.5,0.5,0.5));
  left->getTechnique(0)->getPass(0)->setDiffuse(baseColour);
  if(textures["Left"]!="")
    left->getTechnique(0)->getPass(0)->createTextureUnitState(textures["Left"]);

  Ogre::MaterialPtr right = Ogre::MaterialManager::getSingleton().create(name+"MatRight", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
  right->setAmbient(Ogre::ColourValue(0,0,0));
  right->setSpecular(Ogre::ColourValue(0.5,0.5,0.5));
  right->getTechnique(0)->getPass(0)->setDiffuse(baseColour);
  if(textures["Right"]!="")
    right->getTechnique(0)->getPass(0)->createTextureUnitState(textures["Right"]);

  Ogre::MaterialPtr front = Ogre::MaterialManager::getSingleton().create(name+"MatFront", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
  front->setAmbient(Ogre::ColourValue(0,0,0));
  front->setSpecular(Ogre::ColourValue(0.5,0.5,0.5));
  front->getTechnique(0)->getPass(0)->setDiffuse(baseColour);
  if(textures["Front"]!="")
    front->getTechnique(0)->getPass(0)->createTextureUnitState(textures["Front"]);

  Ogre::MaterialPtr back = Ogre::MaterialManager::getSingleton().create(name+"MatBack", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
  back->setAmbient(Ogre::ColourValue(0,0,0));
  back->setSpecular(Ogre::ColourValue(0.5,0.5,0.5));
  back->getTechnique(0)->getPass(0)->setDiffuse(baseColour);
  if(textures["Back"]!="")
    back->getTechnique(0)->getPass(0)->createTextureUnitState(textures["Back"]);

  manual->setDynamic(true);

  manual->begin(name + "MatBottom", Ogre::RenderOperation::OT_TRIANGLE_LIST);
  manual->normal(0,1,0);
  manual->position(0.5, -0.5, 0.5);
  manual->textureCoord(1, 0);
  manual->position( 0.5, -0.5, -0.5);
  manual->textureCoord(1, 1);
  manual->position( -0.5, -0.5, -0.5);
  manual->textureCoord(0, 1);
  manual->position(-0.5, -0.5, 0.5);
  manual->textureCoord(0, 0);
  manual->quad(3,2,1,0);
  manual->end();

  // Top
  manual->begin(name + "MatTop", Ogre::RenderOperation::OT_TRIANGLE_LIST);
  manual->normal(0,1,0);
  manual->position(0.5, 0.5, 0.5);
  manual->textureCoord(1, 1);
  manual->position( 0.5, 0.5, -0.5);
  manual->textureCoord(1, 0);
  manual->position( -0.5, 0.5, -0.5);
  manual->textureCoord(0, 0);
  manual->position(-0.5, 0.5, 0.5);
  manual->textureCoord(0, 1);
  manual->quad(0,1,2,3);
  manual->end();

  // Left
  manual->begin(name + "MatLeft", Ogre::RenderOperation::OT_TRIANGLE_LIST);
  manual->normal(1,0,0);
  manual->position(-0.5, -0.5, 0.5);
  manual->textureCoord(1, 1);
  manual->position( -0.5, 0.5, 0.5);
  manual->textureCoord(1, 0);
  manual->position( -0.5, 0.5, -0.5);
  manual->textureCoord(0, 0);
  manual->position(-0.5, -0.5, -0.5);
  manual->textureCoord(0, 1);
  manual->quad(0,1,2,3);
  manual->end();

  // Right
  manual->begin(name + "MatRight", Ogre::RenderOperation::OT_TRIANGLE_LIST);
  manual->normal(1,0,0);
  manual->position(0.5, -0.5, 0.5);
  manual->textureCoord(0, 1);
  manual->position( 0.5, 0.5, 0.5);
  manual->textureCoord(0, 0);
  manual->position( 0.5, 0.5, -0.5);
  manual->textureCoord(1, 0);
  manual->position(0.5, -0.5, -0.5);
  manual->textureCoord(1, 1);
  manual->quad(3,2,1,0);
  manual->end();

  // Front
  manual->begin(name + "MatFront", Ogre::RenderOperation::OT_TRIANGLE_LIST);
  manual->normal(0,0,1);
  manual->position(-0.5, -0.5, 0.5);
  manual->textureCoord(0, 1);
  manual->position( -0.5, 0.5, 0.5);
  manual->textureCoord(0, 0);
  manual->position( 0.5, 0.5, 0.5);
  manual->textureCoord(1, 0);
  manual->position(0.5, -0.5, 0.5);
  manual->textureCoord(1, 1);
  manual->quad(3,2,1,0);
  manual->end();

  // Back
  manual->begin(name + "MatBack", Ogre::RenderOperation::OT_TRIANGLE_LIST);
  manual->normal(0,0,1);
  manual->position(-0.5, -0.5, -0.5);
  manual->textureCoord(1, 1);
  manual->position( -0.5, 0.5, -0.5);
  manual->textureCoord(1, 0);
  manual->position( 0.5, 0.5, -0.5);
  manual->textureCoord(0, 0);
  manual->position(0.5, -0.5, -0.5);
  manual->textureCoord(0, 1);
  manual->quad(0,1,2,3);
  manual->end();

  manual->convertToMesh(name +".mesh");
  pSceneManager->destroyManualObject(name);
}


void
CubeUtils::deleteCubeMesh(std::string name)
{
  Ogre::SceneManager* pSceneManager = OgreManager::getInstance()->getSceneManager();
  Ogre::Root *pOgreRoot = OgreManager::getInstance()->getRoot();
  QString entityName = QString().fromStdString(name) + QString("_%1").arg(0);
  QString entityMesh =  entityName + QString(".mesh");
  pSceneManager->destroyEntity( entityName.toStdString() ); 
  pOgreRoot->getMeshManager()->remove(entityMesh.toStdString() );
}

void
CubeUtils::attachCubeFaces( std::string name )
{
  Ogre::SceneManager* pSceneManager = OgreManager::getInstance()->getSceneManager();
  pSceneManager->getSceneNode(name + "Node")->attachObject( pSceneManager->getManualObject(name + "Top"));
  pSceneManager->getSceneNode(name + "Node")->attachObject( pSceneManager->getManualObject(name + "Bottom"));
  pSceneManager->getSceneNode(name + "Node")->attachObject( pSceneManager->getManualObject(name + "Left"));
  pSceneManager->getSceneNode(name + "Node")->attachObject( pSceneManager->getManualObject(name + "Right"));
  pSceneManager->getSceneNode(name + "Node")->attachObject( pSceneManager->getManualObject(name + "Front"));
  pSceneManager->getSceneNode(name + "Node")->attachObject( pSceneManager->getManualObject(name + "Back"));
}

void
CubeUtils::createDoorEntity( Ogre::String name, float ambientColor[3], float sizex, float sizey, float sizez )
{
	float maxX = sizex/2;
	float minX = - sizex/2;
	float maxY = 3*sizey/4;
	float minY = - sizey/4;
	float maxZ = sizez/2;
	float minZ = - sizez/2;

	Ogre::SceneManager* pSceneManager = OgreManager::getInstance()->getSceneManager();
	Ogre::String manualObjectName = name + "MO";
	Ogre::String materialName = name + "Mat";
	Ogre::ManualObject * pDoor = pSceneManager->createManualObject( manualObjectName );

	Ogre::MaterialPtr mat = Ogre::MaterialManager::getSingleton().create( materialName, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	mat->setAmbient(Ogre::ColourValue( ambientColor[0], ambientColor[1], ambientColor[2], 0.4f) );
	mat->getTechnique(0)->getPass(0)->setDiffuse(Ogre::ColourValue( ambientColor[0], ambientColor[1], ambientColor[2], 0.4f) );
	mat->getTechnique(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
	mat->getTechnique(0)->setDepthWriteEnabled(false);

	//Bottom
	pDoor->begin(materialName, Ogre::RenderOperation::OT_TRIANGLE_LIST);
	pDoor->normal(0,1,0);
	pDoor->position(maxX, minY, maxZ);
	pDoor->textureCoord(1, 0);
	pDoor->position( maxX, minY, minZ);
	pDoor->textureCoord(1, 1);
	pDoor->position( minX, minY, minZ);
	pDoor->textureCoord(0, 1);
	pDoor->position(minX, minY, maxZ);
	pDoor->textureCoord(0, 0);
	pDoor->quad(3,2,1,0);
	pDoor->end();

	// Top
	pDoor->begin(materialName, Ogre::RenderOperation::OT_TRIANGLE_LIST);
	pDoor->normal(0,1,0);
	pDoor->position(maxX, maxY, maxZ);
	pDoor->textureCoord(1, 1);
	pDoor->position( maxX, maxY, minZ);
	pDoor->textureCoord(1, 0);
	pDoor->position( minX, maxY, minZ);
	pDoor->textureCoord(0, 0);
	pDoor->position(minX, maxY, maxZ);
	pDoor->textureCoord(0, 1);
	pDoor->quad(0,1,2,3);
	pDoor->end();

	// Left
	pDoor->begin(materialName, Ogre::RenderOperation::OT_TRIANGLE_LIST);
	pDoor->normal(1,0,0);
	pDoor->position(minX, minY, maxZ);
	pDoor->textureCoord(1, 1);
	pDoor->position( minX, maxY, maxZ);
	pDoor->textureCoord(1, 0);
	pDoor->position( minX, maxY, minZ);
	pDoor->textureCoord(0, 0);
	pDoor->position(minX, minY, minZ);
	pDoor->textureCoord(0, 1);
	pDoor->quad(0,1,2,3);
	pDoor->end();

	// Right
	pDoor->begin(materialName, Ogre::RenderOperation::OT_TRIANGLE_LIST);
	pDoor->normal(1,0,0);
	pDoor->position(maxX, minY, maxZ);
	pDoor->textureCoord(0, 1);
	pDoor->position( maxX, maxY, maxZ);
	pDoor->textureCoord(0, 0);
	pDoor->position( maxX, maxY, minZ);
	pDoor->textureCoord(1, 0);
	pDoor->position(maxX, minY, minZ);
	pDoor->textureCoord(1, 1);
	pDoor->quad(3,2,1,0);
	pDoor->end();

	//Front
	pDoor->begin(materialName, Ogre::RenderOperation::OT_TRIANGLE_LIST);
	pDoor->normal(0,0,1);
	pDoor->position( minX, minY, maxZ);
	pDoor->textureCoord(0, 1);
	pDoor->position( minX, maxY, maxZ);
	pDoor->textureCoord(0, 0);
	pDoor->position( maxX, maxY, maxZ);
	pDoor->textureCoord(1, 0);
	pDoor->position( maxX, minY, maxZ);
	pDoor->textureCoord(1, 1);
	pDoor->quad(3,2,1,0);
	pDoor->end();

	//Back
	pDoor->begin(materialName, Ogre::RenderOperation::OT_TRIANGLE_LIST);
	pDoor->normal(0,0,1);
	pDoor->position(minX, minY, minZ);
	pDoor->textureCoord(1, 1);
	pDoor->position(minX, maxY, minZ);
	pDoor->textureCoord(1, 0);
	pDoor->position( maxX, maxY, minZ);
	pDoor->textureCoord(0, 0);
	pDoor->position(maxX, minY, minZ);
	pDoor->textureCoord(0, 1);
	pDoor->quad(0,1,2,3);
	pDoor->end();

	pDoor->convertToMesh( name + "Mesh" );
	pDoor->setCastShadows(false);
}