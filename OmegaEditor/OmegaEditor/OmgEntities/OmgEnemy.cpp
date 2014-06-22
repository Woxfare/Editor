#include "OmgEnemy.h"
#include <QXmlStreamWriter>
#include "OmgEntities/OmgWeapon.h"

OmgEnemy::OmgEnemy( QString a_name, QString folderName ) : OmgCharacter ( a_name, folderName )
{
    setType(Omega::Enemy);
    setPixmap(QPixmap(":/Media/enemy.png"));
    _enemyType = Omega::Runner;
    weapon = NULL;
}

OmgEnemy::~OmgEnemy(){}

void
OmgEnemy::setEnemyType(Omega::EnemyType aType)
{
    _enemyType = aType;
}

Omega::EnemyType
OmgEnemy::enemyType( void )
{
    return _enemyType;
}

QString
OmgEnemy::getItemName()
{
	return _itemName;
}

void
OmgEnemy::setItemName( QString aName )
{
	_itemName = aName;
}

void
OmgEnemy::writeInfo( QXmlStreamWriter *a_xml_stream )
{
  a_xml_stream->writeStartElement("enemy");
  a_xml_stream->writeAttribute("name", getName() );
  a_xml_stream->writeAttribute("folder", getFolderName() );

  writeColor(a_xml_stream);

  a_xml_stream->writeStartElement("life");
  a_xml_stream->writeAttribute("value", QString("%1").arg( getTotalLife() ) );
  a_xml_stream->writeEndElement(); // life

  a_xml_stream->writeStartElement("points");
  a_xml_stream->writeAttribute("value", QString("%1").arg( getPoints() ) );
  a_xml_stream->writeEndElement(); // points

  a_xml_stream->writeStartElement("type");
  a_xml_stream->writeAttribute("value", getEnemyTypeStr() );
  a_xml_stream->writeEndElement(); // type

  a_xml_stream->writeStartElement("item");
  a_xml_stream->writeAttribute("value", getItemName() );
  a_xml_stream->writeEndElement(); // type

  if( weapon )
  {
    a_xml_stream->writeStartElement("weapon");
    a_xml_stream->writeAttribute("name", weapon->getName() );
    a_xml_stream->writeEndElement(); // weapon
  }

  writeTextures(a_xml_stream);

  a_xml_stream->writeEndElement(); // enemy
}

QString
OmgEnemy::getEnemyTypeStr()
{
	if( _enemyType == Omega::BigBoss )
		return "BigBoss";
	if( _enemyType == Omega::JuniorBoss )
		return "JuniorBoss";
	if( _enemyType == Omega::Runner )
		return "Runner";

	return "Gunner";
}

