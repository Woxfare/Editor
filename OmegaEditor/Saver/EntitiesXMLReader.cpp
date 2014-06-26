#include "EntitiesXMLReader.h"

#include <QXmlStreamReader>
#include <QFile>
#include <QString>
#include <QTextStream>

#include "OmgEntities/OmgEntity.h"
#include "OmgEntities/OmgWeapon.h"
#include "OmgEntities/OmgMap.h"
#include "OmgEntities/OmgGame.h"
#include "Omega.h"

#include "Folders/OmgFoldersMngr.h"
#include "OmgEntities/OmgPlayer.h"
#include "OmgEntities/OmgEnemyContainer.h"
#include "OmgEntities/OmgItemContainer.h"
#include "OmgEntities/OmgPlayerContainer.h"
#include "OmgEntities/OmgSceneObjContainer.h"
#include "OmgEntities/OmgWeaponsContainer.h"
#include "OmgEntities/OmgMapContainer.h"
#include "OmgEntities/OmgGameContainer.h"
#include "InputData/QOmgWindowMngr.h"

EntitiesXMLReader::EntitiesXMLReader( const QString a_fileName )
{
   if( a_fileName == "" )
    return;

  QFile file(a_fileName);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return;

  QXmlStreamReader xml;

  xml.setDevice( &file );

  bool endOfFile( xml.atEnd() );
  while (!endOfFile ) 
  {
    QString debugName = xml.name().toString();
    if( xml.isStartElement() )
    {
      if(xml.name() == "player")
        parsePlayer(xml);
      if(xml.name() == "enemy")
        parseEnemy(xml);
      if(xml.name() == "sceneobject")
        parseSceneObject(xml);
      if(xml.name() == "item")
        parseItem(xml);
      if(xml.name() == "map")
        parseMap(xml);
      if(xml.name() == "game")
        parseGame(xml);
      if(xml.name() == "weapon")
        parseWeapon(xml);

      xml.readNext();
    } else {
      xml.readNext();
    }

    endOfFile = xml.atEnd();
  }

  if (xml.hasError()) {
    //... // do error handling
  }

  QOmgWindowMngr::Instance()->GetMainWindow()->UpdateWidgets();

  file.close();
}

void
EntitiesXMLReader::parsePlayer( QXmlStreamReader& xml )
{
  QString playerName = xml.attributes().value("name").toString();
  QString playerFolder = xml.attributes().value("folder").toString();

  if( !OmgFoldersMngr::Instance()->getFolder(playerFolder))
  {
    OmgFolder *folder = new OmgFolder( playerFolder, Omega::WeaponFolder );
    OmgFoldersMngr::Instance()->addFolder( folder );
  }

  OmgPlayer* newPlayer = new OmgPlayer( playerName, playerFolder );

  xml.readNext();

  while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "player"))
  {
    QString debugName = xml.name().toString();
    if( xml.tokenType() == QXmlStreamReader::EndElement || xml.name() == "")
    {
      xml.readNext(); // next loop
      continue;
    }
      
    if( xml.name() == "color")
    {
      int r,g,b;
      parseColor( xml, r, g, b );
      newPlayer->setColor(QColor(r,g,b));
    }

    if( xml.name() == "life")
    {
      int life = xml.attributes().value("value").toString().toInt();
      newPlayer->setTotalLife( life );
      xml.readNext();
    }

    if( xml.name() == "textures")
    {
      std::map<std::string, std::map<std::string, std::string>> textures;
      parseCharacterTextures( xml, textures );
      newPlayer->setTextures( textures );
    }

    if( xml.name() == "weapons")
    {
		Omega::EntityVector vWeapons;
		while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "weapons"))
		{
			QString debugName = xml.name().toString();
			
			if( xml.isStartElement() )
			{
				if( xml.name() == "weapon")
					vWeapons.push_back( OmgWeaponsContainer::Instance()->getWeapon( xml.attributes().value("name").toString()));
			}
			else 
				xml.readNext();
		}

      newPlayer->setWeapons( vWeapons );
    }

    xml.readNext();
  }

  newPlayer->createCustomPixmap();
  OmgPlayerContainer::Instance()->addPlayer(newPlayer);
}

void
EntitiesXMLReader::parseEnemy( QXmlStreamReader& xml )
{
  QString enemyName = xml.attributes().value("name").toString();
  QString enemyFolder = xml.attributes().value("folder").toString();

  if( !OmgFoldersMngr::Instance()->getFolder(enemyFolder))
  {
    OmgFolder *folder = new OmgFolder( enemyFolder, Omega::WeaponFolder );
    OmgFoldersMngr::Instance()->addFolder( folder );
  }

  OmgEnemy* newEnemy = new OmgEnemy( enemyName, enemyFolder );

  xml.readNext();

  while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "enemy"))
  {
    QString debugName = xml.name().toString();
    if( xml.tokenType() == QXmlStreamReader::EndElement || xml.name() == "")
    {
      xml.readNext(); // next loop
      continue;
    }

    if( xml.name() == "color")
    {
      int r,g,b;
      parseColor( xml, r, g, b );
      newEnemy->setColor(QColor(r,g,b));
    }

    if( xml.name() == "life")
    {
      int life = xml.attributes().value("value").toString().toInt();
      newEnemy->setTotalLife( life );
      xml.readNext();
    }

    if( xml.name() == "points")
    {
      int points = xml.attributes().value("value").toString().toInt();
      newEnemy->setPoints( points );
      xml.readNext();
    }

    if( xml.name() == "textures")
    {
      std::map<std::string, std::map<std::string, std::string>> textures;
      parseCharacterTextures( xml, textures );
      newEnemy->setTextures( textures );
    }

    if( xml.name() == "weapon")
      newEnemy->setWeapon( OmgWeaponsContainer::Instance()->getWeapon( xml.attributes().value("name").toString() ) );

	if( xml.name() == "type")
	{
		if( "BigBoss" == xml.attributes().value("value").toString())
			newEnemy->setEnemyType( Omega::BigBoss );
		if( "JuniorBoss" == xml.attributes().value("value").toString())
			newEnemy->setEnemyType( Omega::JuniorBoss );
		if( "Runner" == xml.attributes().value("value").toString())
			newEnemy->setEnemyType( Omega::Runner );
		if( "Gunner" == xml.attributes().value("value").toString())
			newEnemy->setEnemyType( Omega::Gunner );

		xml.readNext();
	}

	if( xml.name() == "item")
		newEnemy->setItemName( xml.attributes().value("value").toString() );

    xml.readNext(); // next loop
  }

  newEnemy->createCustomPixmap();
  OmgEnemyContainer::Instance()->addEnemy(newEnemy);
}

void
EntitiesXMLReader::parseSceneObject( QXmlStreamReader& xml )
{
  QString sceneObjName = xml.attributes().value("name").toString();
  QString sceneObjFolder = xml.attributes().value("folder").toString();
  
  if( !OmgFoldersMngr::Instance()->getFolder(sceneObjFolder))
  {
    OmgFolder *folder = new OmgFolder( sceneObjFolder, Omega::WeaponFolder );
    OmgFoldersMngr::Instance()->addFolder( folder );
  }

  QColor color(0,0,0);
  Omega::SceneObjType type = Omega::Static;
  std::map<std::string, std::string> textures;

  xml.readNext();

  while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "sceneobject"))
  {
    QString debugName = xml.name().toString();

    if( xml.isStartElement() )
    {
      if( xml.name() == "color")
      {
        int r,g,b;
        parseColor( xml, r, g, b );
        color = QColor(r,g,b);
      }

      if( xml.name() == "type")
      {
        if( "Dynamic" == xml.attributes().value("value").toString())
          type = Omega::Dynamic;

        xml.readNext();
      }

      if( xml.name() == "textures")
        parseCubeTextures( xml, textures );

      xml.readNext(); // next loop
    }
    else
      xml.readNext(); // next loop
  }

  int rgb[3] = { color.red(), color.green(), color.blue() };
  
  OmgSceneObj* newSceneObj = new OmgSceneObj( sceneObjName, textures, rgb );
  newSceneObj->setFolderName( sceneObjFolder );
  newSceneObj->setColor( color );
  newSceneObj->setObjectType( type );
  
  OmgSceneObjContainer::Instance()->AddObject(newSceneObj);
}

void
EntitiesXMLReader::parseItem( QXmlStreamReader& xml )
{
  QString itemName = xml.attributes().value("name").toString();
  QString itemFolder = xml.attributes().value("folder").toString();
  OmgWeapon* weapon = NULL;
  int quantity = 0;

  if( !OmgFoldersMngr::Instance()->getFolder(itemFolder))
  {
    OmgFolder *folder = new OmgFolder( itemFolder, Omega::WeaponFolder );
    OmgFoldersMngr::Instance()->addFolder( folder );
  }

  QColor color(0,0,0);
  Omega::ItemType type = Omega::Gold;
  std::map<std::string, std::string> textures;

  xml.readNext();

  while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "item"))
  {
    QString debugName = xml.name().toString();
    if( xml.tokenType() == QXmlStreamReader::EndElement || xml.name() == "")
    {
      xml.readNext(); // next loop
      continue;
    }

    if( xml.name() == "weapon")
    {
      weapon = OmgWeaponsContainer::Instance()->getWeapon( xml.attributes().value("name").toString() );
    }

    if( xml.name() == "color")
    {
      int r,g,b;
      parseColor( xml, r, g, b );
      color = QColor(r,g,b);
    }

    if( xml.name() == "type")
    {
      if( "Health" == xml.attributes().value("value").toString())
        type = Omega::Health;
      else if( "Ammo" == xml.attributes().value("value").toString())
        type = Omega::Ammo;

      quantity = xml.attributes().value("quantity").toString().toInt();

      xml.readNext();
    }

    if( xml.name() == "textures")
      parseCubeTextures( xml, textures );

    xml.readNext(); // next loop
  }

  int rgb[3] = {
    color.red(),
    color.green(),
    color.blue()
  };

  OmgItem* newItem = new OmgItem( itemName, textures, rgb );
  newItem->setFolderName( itemFolder );
  newItem->setColor( color );
  newItem->setItemType( type );
  newItem->setWeapon( weapon );
  newItem->setQuantity(quantity);

  OmgItemContainer::Instance()->addItem(newItem);
}

void
EntitiesXMLReader::parseWeapon( QXmlStreamReader& xml )
{
  QString weaponName = xml.attributes().value("name").toString();
  QString weaponFolder = xml.attributes().value("folder").toString();

  OmgWeapon * newWeapon = new OmgWeapon( weaponName, weaponFolder );

  if( !OmgFoldersMngr::Instance()->getFolder(weaponFolder) )
  {
    OmgFolder *folder = new OmgFolder( weaponFolder, Omega::WeaponFolder );
    OmgFoldersMngr::Instance()->addFolder( folder );
  }

  xml.readNext();

  while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "weapon"))
  {
    QString debugName = xml.name().toString();

    if( xml.isStartElement() )
    {
      if( xml.name() == "color")
      {
        int r,g,b;
        parseColor( xml, r, g, b );
        newWeapon->setColor( QColor(r,g,b) );
      }

      if( xml.name() == "type")
      {
        if( "BlastShot" == xml.attributes().value("value").toString())
          newWeapon->setWeaponType( Omega::BlastShot );
        else if( "SimpleShot" == xml.attributes().value("value").toString())
          newWeapon->setWeaponType( Omega::SimpleShot );
        else if( "MultiShot" == xml.attributes().value("value").toString())
          newWeapon->setWeaponType( Omega::MultiShot );
      }

      if( xml.name() == "features")
      {
        newWeapon->setDefaultBullets( xml.attributes().value("bullets").toString().toInt() );
		newWeapon->setDamage( xml.attributes().value("damage").toString().toInt() );
      }

      xml.readNext(); // next loop
    }
    else
      xml.readNext(); // next loop
  }

  OmgWeaponsContainer::Instance()->addWeapon(newWeapon);
}

void
EntitiesXMLReader::parseMap( QXmlStreamReader& xml )
{
  QString mapName = xml.attributes().value("name").toString();
  QString mapFolder = xml.attributes().value("folder").toString();

  if( !OmgFoldersMngr::Instance()->getFolder(mapFolder))
  {
    OmgFolder *folder = new OmgFolder( mapFolder, Omega::WeaponFolder );
    OmgFoldersMngr::Instance()->addFolder( folder );
  }

  OmgMap * newMap = new OmgMap( mapName, mapFolder );

  xml.readNext();

  while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "map"))
  {
    QString debugName = xml.name().toString();

    if( xml.isStartElement() )
    {
      if( xml.name() == "color")
      {
        int r,g,b;
        parseColor( xml, r, g, b );
        newMap->setColor( QColor(r,g,b) );
      }

      if( xml.name() == "terrain")
      {
        newMap->setTerrainTextureName( xml.attributes().value("name").toString() );
      }

      if( xml.name() == "objects")
      {
        std::vector< std::pair < std::string, std::vector< Ogre::Vector3 > > > objects;
        parseMapObjects( xml, objects );
        newMap->setSceneObjectsToTheMap( objects );
      }
      
      if( xml.name() == "doors")
      {
        std::vector< Ogre::Vector3 > objects;

        while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "doors"))
        {
          if( xml.isStartElement() )
          {
            if(xml.name() == "pos")
            {
              float x = xml.attributes().value("x").toString().toInt();
              float y = xml.attributes().value("y").toString().toInt();
              float z = xml.attributes().value("z").toString().toInt();

              objects.push_back( Ogre::Vector3( x, y, z ) );
            }
            xml.readNext(); // next loop
          } 
          else
            xml.readNext(); // next loop
        }

        newMap->setEnemyDoors( objects );
      }

	  if( xml.name() == "player" )
	  {
		  float x = xml.attributes().value("x").toString().toInt();
		  float y = xml.attributes().value("y").toString().toInt();
		  float z = xml.attributes().value("z").toString().toInt();
		  newMap->setPlayerDoor( Ogre::Vector3( x, y, z) );
	  }

      xml.readNext(); // next loop
    }
    else
      xml.readNext(); // next loop
  }

  OmgMapContainer::Instance()->addMap(newMap);
}

void
EntitiesXMLReader::parseGame( QXmlStreamReader& xml )
{
  QString gameName = xml.attributes().value("name").toString();
  QString gameFolder = xml.attributes().value("folder").toString();

  if( !OmgFoldersMngr::Instance()->getFolder(gameFolder) )
  {
    OmgFolder *folder = new OmgFolder( gameFolder, Omega::WeaponFolder );
    OmgFoldersMngr::Instance()->addFolder( folder );
  }

  OmgGame * newGame = new OmgGame( gameName, gameFolder );

  newGame->setNumberOfRounds(xml.attributes().value("rounds").toString().toInt());

  xml.readNext();

  while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "game"))
  {
    QString debugName = xml.name().toString();

    if( xml.isStartElement() )
    {
      if( xml.name() == "player")
        newGame->setPlayer( OmgPlayerContainer::Instance()->getPlayer( xml.attributes().value("name").toString() ) );

      if( xml.name() == "map")
       newGame->setMap( OmgMapContainer::Instance()->getMap( xml.attributes().value("name").toString() ) );

      if( xml.name() == "enemies")
      {
        newGame->setMinEnemies(xml.attributes().value("min").toString().toInt());
        newGame->setMaxEnemies(xml.attributes().value("max").toString().toInt());
        newGame->setNumberOfBosses(xml.attributes().value("bosses").toString().toInt());
        newGame->setIntervalBosses(xml.attributes().value("interval").toString().toInt());
        Omega::EntityVector vEnemies;
        while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "enemies"))
        {
          QString debugName = xml.name().toString();

          if( xml.isStartElement() )
          {
            if( xml.name() == "enemy")
            {
              OmgEnemy* enemy = OmgEnemyContainer::Instance()->getEnemy(xml.attributes().value("name").toString());

              if( enemy )
                vEnemies.push_back( enemy );
            }

            xml.readNext(); // next loop
          } else 
            xml.readNext(); // next loop
        }

        newGame->setAvailableEnemies(vEnemies);
      }

      if( xml.name() == "items")
      {
        Omega::EntityVector vItems;

        while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "items"))
        {
          QString debugName = xml.name().toString();

          if( xml.isStartElement() )
          {
            if( xml.name() == "item")
            {
              OmgItem* item = OmgItemContainer::Instance()->getItem( xml.attributes().value("name").toString() );

              if( item )
                vItems.push_back( item );
            }

            xml.readNext(); // next loop
          } else 
            xml.readNext(); // next loop
        }

        newGame->setAvailableItems( vItems );
      }

      xml.readNext(); // next loop
    }
    else
      xml.readNext(); // next loop
  }

  OmgGameContainer::Instance()->addGame(newGame);
}

void
EntitiesXMLReader::parseColor( QXmlStreamReader& xml, int& r, int& g, int& b )
{
  r = xml.attributes().value("r").toString().toInt();
  g = xml.attributes().value("g").toString().toInt();
  b = xml.attributes().value("b").toString().toInt();
}

void
EntitiesXMLReader::parseCharacterTextures( QXmlStreamReader& xml, std::map<std::string, std::map<std::string, std::string>>& ar_textures )
{
  while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "textures"))
  {
    QString debugName = xml.name().toString();
    if( xml.tokenType() == QXmlStreamReader::EndElement || xml.name() == "")
    {
      xml.readNext(); // next loop
      continue;
    }

    if( xml.name() == "Head" )
    {
      std::map<std::string, std::string> head_parts;
      head_parts["Back"]   = xml.attributes().value("Back").toString().toStdString();
      head_parts["Bottom"] = xml.attributes().value("Bottom").toString().toStdString();
      head_parts["Front"]  = xml.attributes().value("Front").toString().toStdString();
      head_parts["Left"]   = xml.attributes().value("Left").toString().toStdString();
      head_parts["Right"]  = xml.attributes().value("Right").toString().toStdString();
      head_parts["Top"]    = xml.attributes().value("Top").toString().toStdString();

      ar_textures["Head"] = head_parts;
      xml.readNext();
    }

    if( xml.name() == "Body" )
    {
      std::map<std::string, std::string> body_parts;
      body_parts["Back"]   = xml.attributes().value("Back").toString().toStdString();
      body_parts["Bottom"] = xml.attributes().value("Bottom").toString().toStdString();
      body_parts["Front"]  = xml.attributes().value("Front").toString().toStdString();
      body_parts["Left"]   = xml.attributes().value("Left").toString().toStdString();
      body_parts["Right"]  = xml.attributes().value("Right").toString().toStdString();
      body_parts["Top"]    = xml.attributes().value("Top").toString().toStdString();

      ar_textures["Body"] = body_parts;
      xml.readNext();
    }

    if( xml.name() == "ArmL" )
    {
      std::map<std::string, std::string> arm_parts;
      arm_parts["Back"]   = xml.attributes().value("Back").toString().toStdString();
      arm_parts["Bottom"] = xml.attributes().value("Bottom").toString().toStdString();
      arm_parts["Front"]  = xml.attributes().value("Front").toString().toStdString();
      arm_parts["Left"]   = xml.attributes().value("Left").toString().toStdString();
      arm_parts["Right"]  = xml.attributes().value("Right").toString().toStdString();
      arm_parts["Top"]    = xml.attributes().value("Top").toString().toStdString();

      ar_textures["ArmL"] = arm_parts;
      xml.readNext();
    }

    if( xml.name() == "ArmR" )
    {
      std::map<std::string, std::string> arm_parts;
      arm_parts["Back"]   = xml.attributes().value("Back").toString().toStdString();
      arm_parts["Bottom"] = xml.attributes().value("Bottom").toString().toStdString();
      arm_parts["Front"]  = xml.attributes().value("Front").toString().toStdString();
      arm_parts["Left"]   = xml.attributes().value("Left").toString().toStdString();
      arm_parts["Right"]  = xml.attributes().value("Right").toString().toStdString();
      arm_parts["Top"]    = xml.attributes().value("Top").toString().toStdString();

      ar_textures["ArmR"] = arm_parts;
      xml.readNext();
    }

    if( xml.name() == "LegL" )
    {
      std::map<std::string, std::string> leg_parts;
      leg_parts["Back"]   = xml.attributes().value("Back").toString().toStdString();
      leg_parts["Bottom"] = xml.attributes().value("Bottom").toString().toStdString();
      leg_parts["Front"]  = xml.attributes().value("Front").toString().toStdString();
      leg_parts["Left"]   = xml.attributes().value("Left").toString().toStdString();
      leg_parts["Right"]  = xml.attributes().value("Right").toString().toStdString();
      leg_parts["Top"]    = xml.attributes().value("Top").toString().toStdString();

      ar_textures["LegL"] = leg_parts;
      xml.readNext();
    }

    if( xml.name() == "LegR" )
    {
      std::map<std::string, std::string> leg_parts;
      leg_parts["Back"]   = xml.attributes().value("Back").toString().toStdString();
      leg_parts["Bottom"] = xml.attributes().value("Bottom").toString().toStdString();
      leg_parts["Front"]  = xml.attributes().value("Front").toString().toStdString();
      leg_parts["Left"]   = xml.attributes().value("Left").toString().toStdString();
      leg_parts["Right"]  = xml.attributes().value("Right").toString().toStdString();
      leg_parts["Top"]    = xml.attributes().value("Top").toString().toStdString();

      ar_textures["LegR"] = leg_parts;
      xml.readNext();
    }

    xml.readNext(); // next loop
  }
}

void
EntitiesXMLReader::parseCubeTextures( QXmlStreamReader& xml, std::map<std::string, std::string>& ar_textures )
{
  while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "textures"))
  {
    QString debugName = xml.name().toString();
    if( xml.tokenType() == QXmlStreamReader::EndElement || xml.name() == "" )
    {
      xml.readNext(); // next loop
      continue;
    }

    ar_textures["Back"]   = xml.attributes().value("Back").toString().toStdString();
    ar_textures["Bottom"] = xml.attributes().value("Bottom").toString().toStdString();
    ar_textures["Front"]  = xml.attributes().value("Front").toString().toStdString();
    ar_textures["Left"]   = xml.attributes().value("Left").toString().toStdString();
    ar_textures["Right"]  = xml.attributes().value("Right").toString().toStdString();
    ar_textures["Top"]    = xml.attributes().value("Top").toString().toStdString();

    xml.readNext(); // next loop
  }
}

void
EntitiesXMLReader::parseMapObjects( QXmlStreamReader& xml, std::vector< std::pair< std::string, std::vector< Ogre::Vector3 > > >& ar_objects )
{
  while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "objects"))
  {
      QString debugName = xml.name().toString();
      if( xml.isStartElement() )
      {
        if(xml.name() == "cube")
        {
          std::pair< std::string, std::vector< Ogre::Vector3 > > cube;
          parseSingleCube(xml, cube );
          ar_objects.push_back( cube );
        }

        xml.readNext(); // next loop
      } else
        xml.readNext(); // next loop
  }
}

void
EntitiesXMLReader::parseSingleCube( QXmlStreamReader& xml, std::pair< std::string, std::vector< Ogre::Vector3 > > &cube )
{
  QString cubeName = xml.attributes().value("name").toString();
  std::vector< Ogre::Vector3 > positions;
  // parsing all the cube positions
  while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "cube"))
  {
    if( xml.isStartElement() )
    {
      if(xml.name() == "pos")
      {
        float x = xml.attributes().value("x").toString().toInt();
        float y = xml.attributes().value("y").toString().toInt();
        float z = xml.attributes().value("z").toString().toInt();

        positions.push_back( Ogre::Vector3( x, y, z ) );
      }
      xml.readNext(); // next loop
    } 
    else
      xml.readNext(); // next loop
  }

  cube = std::make_pair( cubeName.toStdString(), positions );
}