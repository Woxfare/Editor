#include "OmgMap.h"

#include <QXmlStreamWriter>
#include "OmgSceneObjContainer.h"
#include "Utils\OgreManager.h"

#include <qDebug>

OmgMap::OmgMap(QString aName, QString aFolderName ) : OmgEntity(aName, aFolderName )
{
    setFolderName(aFolderName);
    setType(Omega::Map);
}

void
OmgMap::setTerrainTextureName( QString terrainTextureName )
{
  _terrainTextureName = terrainTextureName;
}

QString
OmgMap::getTerrainTextureName( void )
{
  return _terrainTextureName;
}

void
OmgMap::setSceneObjectsToTheMap( std::vector< std::pair< std::string, std::vector< Ogre::Vector3 > > > sceneObjectsToSet )
{
  _sceneObjects = sceneObjectsToSet;
}

std::vector< std::pair< std::string, std::vector< Ogre::Vector3 > > >
OmgMap::getSceneObjectsInTheMap( void )
{ 
  return _sceneObjects;
}

Ogre::MeshPtr
OmgMap::getMeshScenary( void )
{
  return _scenaryMesh;
}

void
OmgMap::setMeshScenary( Ogre::MeshPtr meshScenary )
{
  _scenaryMesh = meshScenary;
}

std::vector< std::pair < std::string, std::vector< Ogre::Vector3 > > >
OmgMap::getDynamicObjects( void )
{
  return _dynamicSceneObjects;
}

void
OmgMap::setDynamicObjects( std::vector< std::pair < std::string, std::vector< Ogre::Vector3 > > >  dynamicObjects )
{
  _dynamicSceneObjects = dynamicObjects;
}

void
OmgMap::writeInfo( QXmlStreamWriter *a_xml_stream )
{
  a_xml_stream->writeStartElement("map");
  a_xml_stream->writeAttribute("name", getName() );
  a_xml_stream->writeAttribute("folder", getFolderName() );

  writeColor(a_xml_stream);

  a_xml_stream->writeStartElement("terrain");
  a_xml_stream->writeAttribute( "texture", _terrainTextureName );
  a_xml_stream->writeEndElement(); // terrain

  a_xml_stream->writeStartElement("materials");
  for(int i =0; i<_materialsToExport.size(); i++)
  {
	  a_xml_stream->writeStartElement("material");
	  a_xml_stream->writeAttribute( "name", _materialsToExport[i].c_str());
    QString tex(_materialsToExport[i].c_str());
    int lastIndex = tex.lastIndexOf('_');

    QString b = tex.mid(lastIndex+1, tex.length());
    tex = tex.left(lastIndex);

    lastIndex = tex.lastIndexOf('_');
    QString g = tex.mid(lastIndex+1, tex.length());
    tex = tex.left(lastIndex);

    lastIndex = tex.lastIndexOf('_');
    QString r = tex.mid(lastIndex+1, tex.length());
    tex = tex.left(lastIndex);

    a_xml_stream->writeAttribute( "texture", tex);
    a_xml_stream->writeAttribute( "r", r);
    a_xml_stream->writeAttribute( "g", g);
    a_xml_stream->writeAttribute( "b", b);
    
	  a_xml_stream->writeEndElement();
  }
  a_xml_stream->writeEndElement();

  a_xml_stream->writeStartElement("objects");
  std::vector< std::pair < std::string, std::vector< Ogre::Vector3 > > >::iterator it     = _sceneObjects.begin(),
                                                                                   it_end = _sceneObjects.end();
  for(; it != it_end; ++it )
  {
    std::pair < std::string, std::vector< Ogre::Vector3 > > auxPair = (*it);

    a_xml_stream->writeStartElement("cube");

    a_xml_stream->writeAttribute( "name" , QString().fromStdString( auxPair.first ) );
    a_xml_stream->writeAttribute( "number" , QString("%1").arg( auxPair.second.size() ) );

    std::vector< Ogre::Vector3 >::iterator it_positions = auxPair.second.begin(), it_positions_end = auxPair.second.end();
    for(; it_positions != it_positions_end ; ++it_positions)
    {
      Ogre::Vector3 position = (*it_positions);
      a_xml_stream->writeStartElement("pos");
      a_xml_stream->writeAttribute( "x" , QString("%1").arg(position.x) );
      a_xml_stream->writeAttribute( "y" , QString("%1").arg(position.y) );
      a_xml_stream->writeAttribute( "z" , QString("%1").arg(position.z) );
      a_xml_stream->writeEndElement(); // element
    }

    a_xml_stream->writeEndElement(); // current cube
  }

  a_xml_stream->writeEndElement(); // objects

  a_xml_stream->writeStartElement("doors");
  std::vector< Ogre::Vector3 >::iterator itDoors = _doors.begin(), itDoors_end = _doors.end();
  for(; itDoors != itDoors_end; ++itDoors )
  {
    Ogre::Vector3 doorPos = (*itDoors);

    a_xml_stream->writeStartElement("pos");

    a_xml_stream->writeAttribute( "x" , QString("%1").arg( doorPos.x ) );
    a_xml_stream->writeAttribute( "y" , QString("%1").arg( doorPos.y ) );
    a_xml_stream->writeAttribute( "z" , QString("%1").arg( doorPos.z ) );
    
    a_xml_stream->writeEndElement(); // pos
  }

  a_xml_stream->writeEndElement(); // doors

  a_xml_stream->writeStartElement("player");
  a_xml_stream->writeAttribute( "x" , QString("%1").arg( playerPos.x ) );
  a_xml_stream->writeAttribute( "y" , QString("%1").arg( playerPos.y ) );
  a_xml_stream->writeAttribute( "z" , QString("%1").arg( playerPos.z ) );
  a_xml_stream->writeEndElement(); // player


  a_xml_stream->writeEndElement(); // map
}

void
OmgMap::CalculateScenary( void )
{
  _dynamicSceneObjects.clear();
  std::vector< std::pair < std::string, std::vector< Ogre::Vector3 > > > scenaryComplete;
  std::vector< Ogre::Vector3 > positionList;
  std::vector< std::pair< std::string, std::vector< Ogre::Vector3 > > >::iterator it = _sceneObjects.begin(), it_end = _sceneObjects.end();

  for(; it != it_end; ++it )
  {
    std::pair< std::string, std::vector< Ogre::Vector3 > > currentPair = *it;

    // Iterate over the vector of each cube and add the reference to the position
    std::string cubeName = currentPair.first;
    std::vector< Ogre::Vector3 > vectorOfPositions = currentPair.second;

    if( OmgSceneObjContainer::Instance()->getSceneObj( QString().fromStdString(cubeName ))->getObjectType() == Omega::Dynamic )
      _dynamicSceneObjects.push_back( std::make_pair( cubeName, vectorOfPositions ) );
    else
    {
      int nCubes = vectorOfPositions.size();
      for( int i = 0; i < nCubes ; ++i )
        positionList.push_back(vectorOfPositions[i]);

      scenaryComplete.push_back( std::make_pair( cubeName, vectorOfPositions ) );
    }
  }

  std::vector< std::pair < std::string, std::vector< Ogre::Vector3 > > >::iterator scenaryCompleteIt;
  std::vector< Ogre::Vector3 >::iterator positionListIt, cubeListIt;

  scenaryCompleteIt = scenaryComplete.begin();

  std::string materialBaseName;
  std::map<std::string, bool> facesToDraw;

  //Por cada cubo
  //Creamos el objeto que contendra el escenario
  Ogre::SceneManager* pSceneManager = OgreManager::getInstance()->getSceneManager();

  Ogre::ManualObject * scenary;

  try{
    pSceneManager->destroyManualObject( getName().toStdString() );
    scenary = pSceneManager->createManualObject( getName().toStdString() );
  } catch ( Ogre::Exception e )
  {

  }

  for(; scenaryCompleteIt != scenaryComplete.end(); scenaryCompleteIt++)
  {
    materialBaseName = scenaryCompleteIt->first + "Mat";
    //Seteamos la lista de posiciones a recorrer:
    //cubeListIt = iterador del vector de posiciones de cada tipo
    cubeListIt = scenaryCompleteIt->second.begin();


    for(;cubeListIt != scenaryCompleteIt->second.end(); cubeListIt++)
    {
      //Para cada cubo de la lista y para cada otro cubo
      facesToDraw["Top"] = true;
      facesToDraw["Bottom"] = true;
      facesToDraw["Left"] = true;
      facesToDraw["Right"] = true;
      facesToDraw["Front"] = true;
      facesToDraw["Back"] = true;

      for(positionListIt = positionList.begin(); positionListIt != positionList.end(); positionListIt++)
      {
        //Comprobar si existe cubo arriba, abajo, derecha, izquierda, delante o detras y solo pintar las caras que tocan
        //Top
        if((cubeListIt->x == positionListIt->x) && (cubeListIt->y + 1 == positionListIt->y) && (cubeListIt->z == positionListIt->z) )
        {
          facesToDraw["Top"] = false;
        }
        //Bottom
        else if((cubeListIt->x == positionListIt->x) && (cubeListIt->y - 1 == positionListIt->y) && (cubeListIt->z == positionListIt->z) )
        {
          facesToDraw["Bottom"] = false;
        }
        //Left
        else if((cubeListIt->x - 1 == positionListIt->x) && (cubeListIt->y == positionListIt->y) && (cubeListIt->z == positionListIt->z) )
        {
          facesToDraw["Left"] = false;
        }
        //Right
        else if((cubeListIt->x + 1 == positionListIt->x) && (cubeListIt->y == positionListIt->y) && (cubeListIt->z == positionListIt->z) )
        {
          facesToDraw["Right"] = false;
        }
        //Front
        else if((cubeListIt->x == positionListIt->x) && (cubeListIt->y == positionListIt->y) && (cubeListIt->z + 1 == positionListIt->z) )
        {
          facesToDraw["Front"] = false;
        }
        //Back
        else if((cubeListIt->x == positionListIt->x) && (cubeListIt->y == positionListIt->y) && (cubeListIt->z - 1 == positionListIt->z) )
        {
          facesToDraw["Back"] = false;
        }
      }
      //En este punto sabe que caras tiene que dibujar del cubo concreto.
      addFacesToScenaryOptimized(scenary, *cubeListIt, materialBaseName, facesToDraw);
    }
  }

  _scenaryMesh = scenary->convertToMesh("scenary_to_export.mesh");
}

std::vector<std::string>
	OmgMap::getMaterialsToExport()
{
	return _materialsToExport;
}

std::string
OmgMap::optimizeMaterial(std::string materialName)
{	 
	 Ogre::MaterialPtr mat = Ogre::MaterialManager::getSingleton().getByName(materialName);
	 if(!mat.isNull())
	 {
		 if(mat->getTechnique(0)->getPass(0)->getNumTextureUnitStates()!= 0)
		 {
			 Ogre::ColourValue colourAmb = mat->getTechnique(0)->getPass(0)->getAmbient();
			 Ogre::ColourValue colourDiff = mat->getTechnique(0)->getPass(0)->getDiffuse();

			 std::string texName = mat->getTechnique(0)->getPass(0)->getTextureUnitState(0)->getTextureName();
			 std::stringstream ss;
			 ss << texName << "_" << floor(colourAmb.r*255) << "_" << floor(colourAmb.g*255) << "_" << floor(colourAmb.b*255);
			 std::string newMatName = ss.str();

			 std::vector<std::string>::iterator it = std::find(_materialsToExport.begin(), _materialsToExport.end(), newMatName);
			 if(it == _materialsToExport.end())
			 {
				 Ogre::MaterialPtr newMat = Ogre::MaterialManager::getSingleton().create(newMatName, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
				 if(!newMat->getTechnique(0))
					 newMat->createTechnique();
				 if(!newMat->getTechnique(0)->getPass(0))
					 newMat->getTechnique(0)->createPass();	 

				 newMat->getTechnique(0)->getPass(0)->removeAllTextureUnitStates();
				 
				 newMat->getTechnique(0)->getPass(0)->setAmbient(colourAmb);
				 newMat->getTechnique(0)->getPass(0)->setDiffuse(colourDiff);

				 if(texName != "")
					newMat->getTechnique(0)->getPass(0)->createTextureUnitState(texName);

				 _materialsToExport.push_back(newMatName);
				 return newMatName;
			 }
			 else
			 {
				 return newMatName;
			 }
			 
		 }
	 }
	//Devuelve el nombre del material que tiene que poner.
	return "";
}

void
OmgMap::addFacesToScenaryOptimized(Ogre::ManualObject * scenary, Ogre::Vector3 position, std::string materialBaseName, std::map<std::string, bool> facesToDraw)
{
  float maxX = position.x + 0.5f;
  float minX = position.x - 0.5f;
  float maxY = position.y + 0.5f;
  float minY = position.y - 0.5f;
  float maxZ = position.z + 0.5f;
  float minZ = position.z - 0.5f;

  std::string matName;
  if(facesToDraw["Bottom"])
  {
	matName = optimizeMaterial(materialBaseName + "Bottom");
    scenary->begin(matName, Ogre::RenderOperation::OT_TRIANGLE_LIST);
    scenary->normal(0,1,0);
    scenary->position(maxX, minY, maxZ);
    scenary->textureCoord(1, 0);
    scenary->position( maxX, minY, minZ);
    scenary->textureCoord(1, 1);
    scenary->position( minX, minY, minZ);
    scenary->textureCoord(0, 1);
    scenary->position(minX, minY, maxZ);
    scenary->textureCoord(0, 0);
    scenary->quad(3,2,1,0);
    scenary->end();
  }
  // Top
  if(facesToDraw["Top"])
  {
	matName = optimizeMaterial(materialBaseName + "Top");
    scenary->begin(matName, Ogre::RenderOperation::OT_TRIANGLE_LIST);
    scenary->normal(0,1,0);
    scenary->position(maxX, maxY, maxZ);
    scenary->textureCoord(1, 1);
    scenary->position( maxX, maxY, minZ);
    scenary->textureCoord(1, 0);
    scenary->position( minX, maxY, minZ);
    scenary->textureCoord(0, 0);
    scenary->position(minX, maxY, maxZ);
    scenary->textureCoord(0, 1);
    scenary->quad(0,1,2,3);
    scenary->end();
  }
  // Left
  if(facesToDraw["Left"])
  {
	matName = optimizeMaterial(materialBaseName + "Left");
    scenary->begin(matName, Ogre::RenderOperation::OT_TRIANGLE_LIST);
    scenary->normal(1,0,0);
    scenary->position(minX, minY, maxZ);
    scenary->textureCoord(1, 1);
    scenary->position( minX, maxY, maxZ);
    scenary->textureCoord(1, 0);
    scenary->position( minX, maxY, minZ);
    scenary->textureCoord(0, 0);
    scenary->position(minX, minY, minZ);
    scenary->textureCoord(0, 1);
    scenary->quad(0,1,2,3);
    scenary->end();
  }
  // Right
  if(facesToDraw["Right"])
  {
    matName = optimizeMaterial(materialBaseName + "Right");
    scenary->begin(matName, Ogre::RenderOperation::OT_TRIANGLE_LIST);
    scenary->normal(1,0,0);
    scenary->position(maxX, minY, maxZ);
    scenary->textureCoord(0, 1);
    scenary->position( maxX, maxY, maxZ);
    scenary->textureCoord(0, 0);
    scenary->position( maxX, maxY, minZ);
    scenary->textureCoord(1, 0);
    scenary->position(maxX, minY, minZ);
    scenary->textureCoord(1, 1);
    scenary->quad(3,2,1,0);
    scenary->end();
  }
  //Front
  if(facesToDraw["Front"])
  {
	matName = optimizeMaterial(materialBaseName + "Front");
    scenary->begin(matName, Ogre::RenderOperation::OT_TRIANGLE_LIST);
    scenary->normal(0,0,1);
    scenary->position( minX, minY, maxZ);
    scenary->textureCoord(0, 1);
    scenary->position( minX, maxY, maxZ);
    scenary->textureCoord(0, 0);
    scenary->position( maxX, maxY, maxZ);
    scenary->textureCoord(1, 0);
    scenary->position( maxX, minY, maxZ);
    scenary->textureCoord(1, 1);
    scenary->quad(3,2,1,0);
    scenary->end();
  }
  //Back
  if(facesToDraw["Back"])
  {
	matName = optimizeMaterial(materialBaseName + "Back");
    scenary->begin(matName, Ogre::RenderOperation::OT_TRIANGLE_LIST);
    scenary->normal(0,0,1);
    scenary->position(minX, minY, minZ);
    scenary->textureCoord(1, 1);
    scenary->position(minX, maxY, minZ);
    scenary->textureCoord(1, 0);
    scenary->position( maxX, maxY, minZ);
    scenary->textureCoord(0, 0);
    scenary->position(maxX, minY, minZ);
    scenary->textureCoord(0, 1);
    scenary->quad(0,1,2,3);
    scenary->end();
  }
}

void
OmgMap::setEnemyDoors( std::vector< Ogre::Vector3> aDoors )
{
  _doors = aDoors;
}


std::vector< Ogre::Vector3>
OmgMap::getEnemyDoors(  )
{
 return _doors;
}

Ogre::Vector3
OmgMap::getPlayerDoor()
{
	return playerPos;
}

void
OmgMap::setPlayerDoor( Ogre::Vector3 pos )
{
	playerPos = pos;
}