#include "OmgEntity.h"
#include "QtComponents/QOmgListItem.h"
#include <QDebug>
#include <QXmlStreamWriter>

OmgEntity::OmgEntity(QString aName )
{
    _name = aName;
    _type = Omega::Entity;
    _color = QColor(255,255,255);
}

OmgEntity::~OmgEntity()
{
	int i = 0;
}

QString
OmgEntity::getName( void )
{
    return _name;
}

void
OmgEntity::setName(QString aName)
{
    _name = aName;
}

Omega::EntityType
OmgEntity::getType ( void )
{
    return _type;
}

QPixmap
OmgEntity::getPixmap( void )
{
    return _pixmap;
}

void
OmgEntity::setType(Omega::EntityType aType)
{
    _type = aType;
}

void
OmgEntity::setPixmap(QPixmap aPix)
{
    _pixmap = aPix;
}

QString
OmgEntity::getFolderName( void )
{
   return _folder;
}

void
OmgEntity::setFolderName(QString aFolderName)
{
    _folder = aFolderName;
}

QColor
OmgEntity::getColor( void )
{
    return _color;
}

void
OmgEntity::setColor(QColor aColor)
{
    _color = aColor;
}

QOmgListItem*
OmgEntity::listItem()
{
    return new QOmgListItem( getName(), getPixmap(), getType());
}

void
OmgEntity::writeInfo( QXmlStreamWriter *a_xml_stream )
{

}

void
OmgEntity::writeColor( QXmlStreamWriter *a_xml_stream )
{
  QColor color = getColor();
  a_xml_stream->writeStartElement("color");
  a_xml_stream->writeAttribute("r", QString("%1").arg(color.red() ) );
  a_xml_stream->writeAttribute("g", QString("%1").arg(color.green() ) );
  a_xml_stream->writeAttribute("b", QString("%1").arg(color.blue() ) );
  a_xml_stream->writeEndElement(); // color
}
