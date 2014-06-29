#include "OmgItem.h"
#include <QDebug>
#include <QXmlStreamWriter>

OmgItem::OmgItem(const QString &aName, const QString &folderName, std::map<std::string, std::string> aTextures, int avRgb[3])  : OmgCube ( aName, folderName, aTextures, avRgb ),
      weaponName( QString("")), quantity( 0 )
{
    setType(Omega::Item);
	  createCustomPixmap();
}

OmgItem::~OmgItem(){}

void
OmgItem::setItemType(Omega::ItemType aType)
{
    _itemType = aType;
}

Omega::ItemType
OmgItem::itemType( void )
{
    return _itemType;
}

QString
OmgItem::itemTypeStr( void )
{
    if(_itemType == Omega::Gold )
        return QString("Gold");
    if(_itemType == Omega::Health )
        return QString("Health");

    return QString("Ammo");
}

void
OmgItem::writeInfo( QXmlStreamWriter *a_xml_stream )
{
  a_xml_stream->writeStartElement("item");
  a_xml_stream->writeAttribute("name", getName() );
  a_xml_stream->writeAttribute("folder", getFolderName() );

  writeColor(a_xml_stream);

  a_xml_stream->writeStartElement("type");
  a_xml_stream->writeAttribute("value", itemTypeStr() );
  a_xml_stream->writeAttribute("quantity", QString("%1").arg( getQuantity() ) );
  if( _itemType == Omega::Ammo )
	  a_xml_stream->writeAttribute("weapon", weaponName );
  a_xml_stream->writeEndElement(); // type

  a_xml_stream->writeStartElement("textures");
  std::map< std::string, std::string>::iterator it = _m_textures.begin(), itEnd = _m_textures.end();
  for(; it!=itEnd; ++it)
    a_xml_stream->writeAttribute( QString().fromStdString( (*it).first ), QString().fromStdString( (*it).second ) );
  a_xml_stream->writeEndElement(); // textures

  a_xml_stream->writeEndElement(); // item
}

void
OmgItem::setWeapon( QString a_weapon )
{
  weaponName = a_weapon;
}

QString
OmgItem::getWeapon( void )
{
  return weaponName;
}

int
OmgItem::getQuantity()
{
  return quantity;
}

void
OmgItem::setQuantity( int a_quantity )
{
  quantity = a_quantity;
}

