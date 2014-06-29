#include "OmgSceneObj.h"
#include "Utils/OgreManager.h"
#include <QDebug>
#include <stdio.h>
#include <QPixmap>
#include <QPainter>
#include "Utils/CubeUtils.h"
#include <QXmlStreamWriter>

OmgSceneObj::OmgSceneObj(QString &a_name, const QString &folderName, std::map<std::string, std::string> a_textures, int rgb[3]) : OmgCube( a_name, folderName, a_textures, rgb )
{
    setType(Omega::SceneObj);
    CubeUtils::createCubeMesh(a_name.toStdString(), a_textures, rgb);
    OgreManager::getInstance()->createEntity0(a_name.toStdString());
    createCustomPixmap();
}

OmgSceneObj::~OmgSceneObj()
{

}

void
OmgSceneObj::setObjectType(Omega::SceneObjType aType)
{
    _typeObj = aType;
}

Omega::SceneObjType
OmgSceneObj::getObjectType( void )
{
    return _typeObj;
}

QString
OmgSceneObj::getObjectTypeStr( void )
{
    if(_typeObj == Omega::Dynamic )
        return "Dynamic";
    return "Static";
}

void
OmgSceneObj::writeInfo( QXmlStreamWriter *a_xml_stream )
{
  a_xml_stream->writeStartElement("sceneobject");
  a_xml_stream->writeAttribute("name", getName() );
  a_xml_stream->writeAttribute("folder", getFolderName() );

  writeColor(a_xml_stream);

  a_xml_stream->writeStartElement("type");
  a_xml_stream->writeAttribute("value", getObjectTypeStr() );
  a_xml_stream->writeEndElement(); // type

  a_xml_stream->writeStartElement("textures");
  std::map< std::string, std::string>::iterator it = _m_textures.begin(), itEnd = _m_textures.end();
  for(; it!=itEnd; ++it)
    a_xml_stream->writeAttribute( QString().fromStdString( (*it).first ), QString().fromStdString( (*it).second ) );
  a_xml_stream->writeEndElement(); // textures

  a_xml_stream->writeEndElement(); // sceneobject
}

