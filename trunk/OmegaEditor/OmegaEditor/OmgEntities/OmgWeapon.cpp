#include "OmgWeapon.h"
#include <QDebug>
#include <QXmlStreamWriter>

OmgWeapon::OmgWeapon(QString a_name, QString a_folderName) : OmgEntity( a_name )
{
    setPixmap(QPixmap(":/Media/gun.png"));
    setType(Omega::Weapon);
    setWeaponType(Omega::SimpleShot);
    setFolderName(a_folderName);
    _nBullets = 0;
	_damage = 0;
}

void
OmgWeapon::setWeaponType(Omega::WeaponType aType)
{
    _weaponType = aType;
}

Omega::WeaponType
OmgWeapon::getWeaponType( void )
{
    return _weaponType;
}

QString
OmgWeapon::getWeaponTypeStr( void )
{
    if(_weaponType == Omega::BlastShot )
        return QString("BlastShot");
    if(_weaponType == Omega::SimpleShot )
        return QString("SimpleShot");
    return QString("MultiShot");
}

int
OmgWeapon::getDefaultBullets( void )
{
    return _nBullets;
}

void
OmgWeapon::setDefaultBullets( int nBullets )
{
    _nBullets = nBullets;
}

int
OmgWeapon::getDamage( void )
{
    return _damage;
}

void
OmgWeapon::setDamage( int damage )
{
    _damage = damage;
}

void
OmgWeapon::writeInfo( QXmlStreamWriter *a_xml_stream )
{
  a_xml_stream->writeStartElement("weapon");
  a_xml_stream->writeAttribute("name", getName() );
  a_xml_stream->writeAttribute("folder", getFolderName() );

  writeColor(a_xml_stream);

  a_xml_stream->writeStartElement("type");
  a_xml_stream->writeAttribute("value", getWeaponTypeStr() );
  a_xml_stream->writeEndElement(); // type

  a_xml_stream->writeStartElement("features");
  a_xml_stream->writeAttribute("bullets", QString("%1").arg(_nBullets) );
  a_xml_stream->writeAttribute("damage", QString("%1").arg(_damage) );
  a_xml_stream->writeEndElement(); // features

  a_xml_stream->writeEndElement(); // weapon
}
