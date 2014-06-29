#include "OmgGame.h"

#include <Qfile>
#include <QTextstream>
#include <QPixmap>
#include <QDir>
#include <QXmlStreamWriter>

#include "OmgEntities/OmgEnemy.h"
#include "OmgEntities/OmgItem.h"
#include "OmgEntities/OmgSceneObjContainer.h"
#include "OmgEntities/OmgWeapon.h"
#include "OmgWeaponsContainer.h"

OmgGame::OmgGame(QString aName, QString aFolderName ) : OmgEntity(aName, aFolderName )
{
    setType(Omega::Game);
}


Omega::EntityVector
OmgGame::getAvailableEnemies( void )
{
    return _vEnemies;
}

Omega::EntityVector
OmgGame::getAvailableItems( void )
{
    return _vItems;
}

void
OmgGame::setAvailableEnemies( Omega::EntityVector vEnemies )
{
  _vEnemies = vEnemies;
}

void
OmgGame::setAvailableItems( Omega::EntityVector vItems )
{
  _vItems = vItems;
}

float
OmgGame::getEnemyIncrement( void )
{
    return _enemyIncrement;
}

int
OmgGame::getIntervalBosses( void )
{
    return _intervalBosses;
}

OmgMap*
OmgGame::getMap( void )
{
    return _scenary;
}

int
OmgGame::getMaxEnemies( void )
{
    return _maxEnemies;
}

int
OmgGame::getMinEnemies( void )
{
    return _minEnemies;
}

void OmgGame::setNumberOfRounds( int nRounds )
{
    _nRounds = nRounds;
}

int OmgGame::getNumberOfRounds(void)
{
    return _nRounds;
}

void OmgGame::setMinEnemies( int minEnemies )
{
    _minEnemies = minEnemies;
}


void OmgGame::setMaxEnemies( int maxEnemies )
{
    _maxEnemies = maxEnemies;
}


void OmgGame::setEnemyIncrement( float increment )
{
    _enemyIncrement = increment;
}

void OmgGame::setNumberOfBosses( int nBosses )
{
    _nBosses = nBosses;
}

int
OmgGame::getNumberOfBosses(void)
{
    return _nBosses;
}

void
OmgGame::setIntervalBosses( int interval )
{
    _intervalBosses = interval;
}

OmgPlayer*
OmgGame::getPlayer( void )
{
    return _player;
}

void
OmgGame::setPlayer( OmgPlayer* apPlayer )
{
  _player = apPlayer;
}

void
OmgGame::setMap( OmgMap* apMap )
{
  _scenary = apMap;
}

void
OmgGame::SaveGameInFile( void )
{ 
  // Directorio donde se guardarán las imagenes y las meshes y el fichero de información
  if( QDir(getName()).exists() )
    QDir().rmdir(getName());
  
  // Creamos el directorio
  QDir().mkdir(getName());
  QString path = QDir().absolutePath() + "/" + getName() + "/" ;

  // Generate textures to save only one time
  std::set< std::string > textures = getPixmapSet();

  // Save the mesh of the scenary
  Ogre::MeshSerializer ser;
  std::string nameMeshScenary = path.toStdString() + _scenary->getName().toStdString() + ".mesh";
  if(_scenary->getMeshScenary().isNull())
    _scenary->CalculateScenary(); // It calculates the mesh and the dynamic objects
  
  if(!_scenary->getMeshScenary().isNull()) // it it continues being null... no save the mesh
    ser.exportMesh(_scenary->getMeshScenary().getPointer(), nameMeshScenary );

  //Generate Materials of the scenary and save the image.
  std::vector<std::string> matNames = _scenary->getMaterialsToExport();
  if(matNames.size() != 0)
  {
	  Ogre::MaterialSerializer mes;
	  for(int i =0; i < matNames.size(); i++)
	  {
		  Ogre::MaterialPtr mat = Ogre::MaterialManager::getSingleton().getByName(matNames[i]);
		  mes.exportMaterial(mat, path.toStdString() + matNames[i] + ".material");
	  }
  }

  std::string nameAux;
  for(int i = 0; i<matNames.size(); i++)
  {
	  std::istringstream splitAux(matNames[i]);
	  std::vector<std::string> stringList;

	  while (std::getline(splitAux, nameAux, '_')) {
		stringList.push_back(nameAux);
	  }

	  std::stringstream ss;
	  for(int j = 0; j < stringList.size()-3; j++)
	  {
		  ss << stringList[j];
		  if(j < stringList.size()-4)
			ss << "_";
	  }

	  nameAux = ss.str();

	  if(textures.count( nameAux ) == 0)
	  {
		  textures.insert(nameAux);
	  }
  }

  savePixmaps( textures, path );
  saveConfigurationFile( path + getName() + ".xml", textures );
}

std::set< std::string >
OmgGame::getPixmapSet( )
{
  std::set< std::string > setPixmaps;

  std::string characterParts[] = {"Head", "Body", "ArmL", "ArmR", "LegL", "LegR" };

  // Get the textures of the players
  std::map<std::string, std::map<std::string, std::string>> playerTextures = _player->getTextures();

  for(int i = 0; i < 6; ++i )
  {
    std::map<std::string, std::string> internalMap = playerTextures[characterParts[i]];
    std::map< std::string, std::string>::iterator it = internalMap.begin(), itEnd = internalMap.end();

    for(; it!=itEnd; ++it)
    {
      std::string texture = (*it).second;

      if( texture == "" )
        continue;

      if( setPixmaps.count( texture ) == 0 )
        setPixmaps.insert( texture );
    }
  }

  Omega::EntityVector vEnemies = getAvailableEnemies();
  int nEnemies = vEnemies.size();

  for( int i = 0; i < nEnemies ; ++i )
  {
    OmgEnemy *enemy = dynamic_cast<OmgEnemy*>(vEnemies[i]);
    std::map<std::string, std::map<std::string, std::string>> currentTextures = enemy->getTextures();

    for(int j = 0; j < 6; ++j )
    {
      std::map<std::string, std::string> internalMap = currentTextures[characterParts[i]];
      std::map< std::string, std::string>::iterator it = internalMap.begin(), itEnd = internalMap.end();

      for(; it!=itEnd; ++it)
      {
        std::string texture = (*it).second;

        if( texture == "" )
          continue;

        if( setPixmaps.count( texture ) == 0 )
          setPixmaps.insert( texture );
      }
    }
  }

  Omega::EntityVector vItems = getAvailableItems();
  Omega::EntityIterator ititems = vItems.begin(), ititemsend = vItems.end();

  for( ; ititems != ititemsend ; ++ititems )
  {
    OmgItem *item = dynamic_cast< OmgItem* >( *ititems );
    std::map<std::string, std::string> currentVector = item->getTextures();
    std::map<std::string, std::string> ::iterator itb = currentVector.begin(), ite = currentVector.end();

    for(; itb!=ite; ++itb )
    {
      std::string texture = (*itb).second;

      if( texture == "")
        continue;

      if( setPixmaps.count( texture ) == 0 )
        setPixmaps.insert( texture );
    }
  }

  return setPixmaps;
}

std::set< QString >
OmgGame::getWeaponsSet()
{
	std::set< QString > setWeapons;
  std::vector<QString> playerWeapons = _player->getWeapons();
  for( int i = 0; i < playerWeapons.size(); ++i )
    setWeapons.insert( playerWeapons[i]);

	

	Omega::EntityVector vEnemies = getAvailableEnemies();
	int nEnemies = vEnemies.size();

	for( int i = 0; i < nEnemies ; ++i )
	{
		OmgEnemy *enemy = dynamic_cast<OmgEnemy*>(vEnemies[i]);
		if(!enemy)
			continue;
    if(!enemy->getWeapon())
      continue;
		setWeapons.insert( enemy->getWeapon()->getName() );
	}

	Omega::EntityVector vItems = getAvailableItems();
	Omega::EntityIterator ititems = vItems.begin(), ititemsend = vItems.end();

	for( ; ititems != ititemsend ; ++ititems )
	{
		OmgItem *item = dynamic_cast< OmgItem* >( *ititems );
		if( !item )
			continue;

		if( item->itemType() == Omega::Ammo )
			setWeapons.insert( item->getWeapon() );

	}

	return setWeapons;
}

void
OmgGame::savePixmaps( std::set< std::string > pixmapSet, QString path )
{
  // Generate from the pixmap set a vector of name and the pixmap
  std::set< std::string >::iterator it_pix = pixmapSet.begin(), it_pix_end = pixmapSet.end();
  std::vector< std::pair< QString, QPixmap > > vPixmaps;
  for( ; it_pix != it_pix_end ; ++it_pix )
  {
    std::string currentName = *it_pix;
    QString pixmapName = "./Resources/materials/textures/" + QString().fromStdString( currentName );

    QPixmap pix( pixmapName );

    if( pix.isNull() )
      continue;

    std::pair< QString, QPixmap > pair = std::make_pair( pixmapName, pix );

    vPixmaps.push_back( pair );
  }

  int nPixmaps = vPixmaps.size();

  for( int i = 0; i < nPixmaps ; ++i )
  {
    std::pair< QString, QPixmap > currentPair = vPixmaps[i];
    QFileInfo info(currentPair.first);
    QString name = path + (info.fileName().split(".")[0]) + ".png";
    QFile file(name);
    file.open(QIODevice::WriteOnly);
    currentPair.second.save(&file, "PNG");
    file.close();
  }
}

void
OmgGame::writeInfo( QXmlStreamWriter *a_xml_stream )
{
  a_xml_stream->writeStartElement("game");
  a_xml_stream->writeAttribute("name", getName() );
  a_xml_stream->writeAttribute("folder", getFolderName() );
  a_xml_stream->writeAttribute("rounds", QString("%1").arg(getNumberOfRounds()) );

  Omega::EntityVector vEnemies = getAvailableEnemies();
  a_xml_stream->writeStartElement("enemies");
  a_xml_stream->writeAttribute("number", QString("%1").arg(vEnemies.size()) );
  a_xml_stream->writeAttribute("min", QString("%1").arg(getMinEnemies()) );
  a_xml_stream->writeAttribute("max", QString("%1").arg(getMaxEnemies()) );
  a_xml_stream->writeAttribute("bosses", QString("%1").arg(getNumberOfBosses()) );
  a_xml_stream->writeAttribute("interval", QString("%1").arg(getIntervalBosses()) );

  Omega::EntityVector vItems = getAvailableItems();
  a_xml_stream->writeStartElement("items");
  a_xml_stream->writeAttribute("number",   QString("%1").arg(vItems.size()) );

  for( int i = 0; i  < vItems.size(); ++i )
  {
	  a_xml_stream->writeStartElement("item");
	  a_xml_stream->writeAttribute("name", vItems[i]->getName());
	  a_xml_stream->writeEndElement(); // enemy
  }

  a_xml_stream->writeEndElement(); // items

  for( int i = 0; i  < vEnemies.size(); ++i )
  {
      a_xml_stream->writeStartElement("enemy");
      a_xml_stream->writeAttribute("name", vEnemies[i]->getName());
      a_xml_stream->writeEndElement(); // enemy
  }

  a_xml_stream->writeEndElement(); // enemies

  a_xml_stream->writeStartElement("player");
  a_xml_stream->writeAttribute("name", _player->getName() );
  a_xml_stream->writeEndElement(); // player

  a_xml_stream->writeStartElement("map");
  a_xml_stream->writeAttribute("name", _scenary->getName());
  a_xml_stream->writeEndElement(); // map

  a_xml_stream->writeEndElement(); // game
}

void
OmgGame::saveConfigurationFile( QString fileName, std::set< std::string > textures )
{
  QFile file( fileName );
  if (!file.open( QIODevice::WriteOnly | QIODevice::Text ))
    return;

  QXmlStreamWriter *stream = new QXmlStreamWriter(); // The stream to save the xml file
  stream->setDevice(&file);

  stream->setAutoFormatting(true);
  stream->writeStartDocument();
  stream->writeStartElement("woxfare");

  _player->writeInfo( stream );
  _scenary->writeInfo( stream );

  stream->writeStartElement("weapons");
  std::set< QString > weapons = getWeaponsSet();
  std::set< QString >::iterator itWb = weapons.begin(), itWe = weapons.end(); 

  for( ;itWb != itWe; ++itWb )
  {
	OmgWeapon * weapon = OmgWeaponsContainer::Instance()->getWeapon(QString(*itWb ));
	if(weapon != 0)
		weapon->writeInfo(stream);
  }
  stream->writeEndElement(); // weapons 

  Omega::EntityVector vEnemies = getAvailableEnemies();
  Omega::EntityVector vItems   = getAvailableItems();
  for( int i = 0; i  < vEnemies.size(); ++i )
    vEnemies[i]->writeInfo( stream );

  for( int i = 0; i  < vItems.size(); ++i )
    vItems[i]->writeInfo( stream );

  // Save the dynamic objects in the file of the wxf
  std::vector< std::pair < std::string, std::vector< Ogre::Vector3 > > > dynamicObjects = _scenary->getDynamicObjects();
  if(!dynamicObjects.empty())
  {
    stream->writeStartElement("dynamicobjects");
    std::vector< std::pair < std::string, std::vector< Ogre::Vector3 > > > dynamicObjects = _scenary->getDynamicObjects();
    std::vector< std::pair < std::string, std::vector< Ogre::Vector3 > > >::iterator it = dynamicObjects.begin(), it_end = dynamicObjects.end();
    for(; it != it_end; ++it )
    {
      std::pair < std::string, std::vector< Ogre::Vector3 > > auxPair = (*it);

      stream->writeStartElement("cube");
	  QString sceneObjStr = QString().fromStdString( auxPair.first );
      stream->writeAttribute( "name" , sceneObjStr );
      stream->writeAttribute( "number" , QString("%1").arg( auxPair.second.size() ) );

      std::vector< Ogre::Vector3 >::iterator it_positions = auxPair.second.begin(), it_positions_end = auxPair.second.end();
      for(; it_positions != it_positions_end ; ++it_positions)
      {
        Ogre::Vector3 position = (*it_positions);
        stream->writeStartElement("pos");
        stream->writeAttribute( "x" , QString("%1").arg(position.x) );
        stream->writeAttribute( "y" , QString("%1").arg(position.y) );
        stream->writeAttribute( "z" , QString("%1").arg(position.z) );
        stream->writeEndElement(); // element
      }

	  //========================== TEXTURES AND COLOUR ===========================//
	  OmgSceneObj* pSceneObj = OmgSceneObjContainer::Instance()->getSceneObj( sceneObjStr );
	  if(pSceneObj)
	  {
		  stream->writeStartElement("textures");
		  std::map< std::string, std::string> textures = pSceneObj->getTextures();
		  std::map< std::string, std::string>::iterator it = textures.begin(), itEnd = textures.end();
		  for(; it!=itEnd; ++it)
			stream->writeAttribute( QString().fromStdString( (*it).first ), QString().fromStdString( (*it).second ) );
		  stream->writeEndElement(); // textures

		  pSceneObj->writeColor( stream );
	  }

	  stream->writeEndElement(); // current cube
    }

    stream->writeEndElement(); // dynamicobjects
  }

  // Save the textures
  if(!textures.empty())
  {
    stream->writeStartElement("textures");
    std::set< std::string >::iterator it_pix = textures.begin(), it_pix_end = textures.end();
    for( ; it_pix != it_pix_end ; ++it_pix )
    {
      stream->writeStartElement("texture");
      stream->writeAttribute( "name" , QString().fromStdString( *it_pix ) );
      stream->writeEndElement(); // current texture
    }
    stream->writeEndElement(); // textures
  }

  writeInfo( stream );

  writeWeapons( stream );

  stream->writeEndElement(); // woxfare

  file.close();
}

void
OmgGame::writeWeapons( QXmlStreamWriter *a_xml_stream )
{
  if(_player->getWeapon())
    _player->getWeapon()->writeInfo( a_xml_stream );

  Omega::EntityVector vEnemies = getAvailableEnemies();
  int nEnemies = vEnemies.size();

  for( int i = 0; i < nEnemies ; ++i )
  {
    OmgEnemy* enemy = dynamic_cast<OmgEnemy*>( vEnemies[i]);

    if( !enemy )
      continue;

    if( enemy->getWeapon() )
      enemy->getWeapon()->writeInfo(a_xml_stream);
  }
}