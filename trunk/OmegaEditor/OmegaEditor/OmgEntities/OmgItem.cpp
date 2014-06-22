#include "OmgItem.h"
#include <QDebug>
#include <QXmlStreamWriter>
#include "OmgEntities/OmgWeapon.h"

OmgItem::OmgItem(QString aName ) : OmgSceneObj ( aName )
{
    setType(Omega::Item);
    _folder = "DefaultItems";
    weapon = NULL;
    quantity = 0;
}

OmgItem::OmgItem(QString a_name, std::map<std::string, std::string> aTextures) : OmgSceneObj ( a_name, aTextures )
{
    setType(Omega::Item);
    _folder = "DefaultItems";
    weapon = NULL;
    quantity = 0;
}

OmgItem::OmgItem(QString aName, std::map<std::string, std::string> aTextures, int rgb[3]) : OmgSceneObj ( aName, aTextures, rgb)
{
    setType(Omega::Item);
    _folder = "DefaultItems";
    weapon = NULL;
    quantity = 0;
}

OmgItem::~OmgItem()
{
  delete weapon;
}

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
	a_xml_stream->writeAttribute("weapon", weapon->getName() );
  a_xml_stream->writeEndElement(); // type

  a_xml_stream->writeStartElement("textures");
  std::map< std::string, std::string>::iterator it = _m_textures.begin(), itEnd = _m_textures.end();
  for(; it!=itEnd; ++it)
    a_xml_stream->writeAttribute( QString().fromStdString( (*it).first ), QString().fromStdString( (*it).second ) );
  a_xml_stream->writeEndElement(); // textures

  a_xml_stream->writeEndElement(); // item
}

void
OmgItem::setWeapon( OmgWeapon* a_weapon )
{
  weapon = a_weapon;
}

OmgWeapon*
OmgItem::getWeapon( void )
{
  return weapon;
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

