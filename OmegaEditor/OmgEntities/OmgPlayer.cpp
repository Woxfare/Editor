#include "OmgPlayer.h"
#include <QDebug>
#include <QColor>
#include <QXmlStreamWriter>
#include "OmgEntities/OmgWeapon.h"

OmgPlayer::OmgPlayer( QString a_name, QString folderName ) : OmgCharacter ( a_name, folderName )
{
    setType(Omega::Player);
    weapon = NULL;
}

OmgPlayer::~OmgPlayer()
{

}

void
OmgPlayer::writeInfo( QXmlStreamWriter *a_xml_stream )
{
  a_xml_stream->writeStartElement("player");
  a_xml_stream->writeAttribute("name", getName() );
  a_xml_stream->writeAttribute("folder", getFolderName() );

  writeColor(a_xml_stream);

  a_xml_stream->writeStartElement("life");
  a_xml_stream->writeAttribute("value", QString("%1").arg( getTotalLife() ) );
  a_xml_stream->writeEndElement(); // life

  a_xml_stream->writeStartElement("weapons");
  a_xml_stream->writeAttribute("number", QString("%1").arg( _weapons.size() ) );

  for( std::vector<QString>::iterator it = _weapons.begin(); it != _weapons.end();  ++it )
  {
	  a_xml_stream->writeStartElement("weapon");
	  a_xml_stream->writeAttribute("name", *it );
	  a_xml_stream->writeEndElement(); // weapons
  }

  a_xml_stream->writeEndElement(); // weapons

  writeTextures(a_xml_stream);
  a_xml_stream->writeEndElement(); // player
}

std::vector<QString>
OmgPlayer::getWeapons()
{
	return _weapons;
}

void
OmgPlayer::setWeapons( std::vector<QString> aWeapons )
{
	_weapons = aWeapons;
}