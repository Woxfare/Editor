#include "OmgSceneObj.h"
#include "Display/OgreManager.h"
#include <QDebug>
#include <stdio.h>
#include <QPixmap>
#include <QPainter>
#include "Utils/CubeUtils.h"
#include <QXmlStreamWriter>

OmgSceneObj::OmgSceneObj(QString a_name )
    : OmgEntity ( a_name )
{
    _texture = QPixmap(":/Media/sceneobj.png");
    setType(Omega::SceneObj);
    setPixmap(QPixmap(":/Media/sceneobj.png"));
    _folder = QString("DefaultObjects" );
    _baseColor.setRgb(1,1,1);

    _m_textures;
    _m_textures["Top"] = "";
    _m_textures["Bottom"]="";
    _m_textures["Left"]="";
    _m_textures["Right"]="";
    _m_textures["Front"]="";
    _m_textures["Back"]="";

    _baseColor.setRed(255);

    int rgb[3] = {
      _baseColor.red(),
      _baseColor.green(),
      _baseColor.blue()
    };

    CubeUtils::createCubeMesh(a_name.toStdString(), _m_textures, rgb);
    OgreManager::getInstance()->createEntity0(a_name.toStdString());
    createCustomPixmap();
}

OmgSceneObj::OmgSceneObj(QString a_name, std::map<std::string, std::string> a_textures)
    : OmgEntity ( a_name )
{
    _texture = QPixmap(":/Media/sceneobj.png");

    a_textures.find("Top");
    setType(Omega::SceneObj);
    setPixmap(QPixmap(":/Media/sceneobj.png"));
    _folder = QString("DefaultObjects" );
    _color.setRgb(1,1,1);

    int rgb[3] = {
      _color.red(),
      _color.green(),
      _color.blue()
    };

    CubeUtils::createCubeMesh(a_name.toStdString(), a_textures, rgb);
    OgreManager::getInstance()->createEntity0(a_name.toStdString());
    createCustomPixmap();
}

OmgSceneObj::OmgSceneObj(QString a_name, std::map<std::string, std::string> a_textures, int rgb[3])
    : OmgEntity ( a_name )
{
    _texture = QPixmap(":/Media/sceneobj.png");
    setType(Omega::SceneObj);
    setPixmap(QPixmap(":/Media/sceneobj.png"));
    _folder = QString("DefaultObjects" );
    _color.setRgb(rgb[0],rgb[1],rgb[2]);

    qDebug() << _color.red() << _color.green() << _color.blue();

    _m_textures = a_textures;

    CubeUtils::createCubeMesh(a_name.toStdString(), a_textures, rgb);
    OgreManager::getInstance()->createEntity0(a_name.toStdString());
    createCustomPixmap();
}

OmgSceneObj::~OmgSceneObj()
{

}

QPixmap
OmgSceneObj::GetMainTexture( void )
{
    return _texture;
}

void
OmgSceneObj::setTexture(std::string textureName, std::string textureFilename)
{
    _m_textures[textureName] = textureFilename;

    //Hay que copiar las texturas al sitio que toca

    Ogre::MaterialPtr mat;
    mat = Ogre::MaterialManager::getSingleton().getByName(_name.toStdString() + textureName);
    mat->getTechnique(0)->getPass(0)->removeTextureUnitState(0);
    mat->getTechnique(0)->getPass(0)->createTextureUnitState(_m_textures[textureName]);
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

std::map<std::string, std::string>
OmgSceneObj::getTextures( void )
{
    return _m_textures;
}

QString
OmgSceneObj::getObjectTypeStr( void )
{
    if(_typeObj == Omega::Dynamic )
        return "Dynamic";
    return "Static";
}

void
OmgSceneObj::createCustomPixmap( void )
{
    QString textureName = "";

    if(_m_textures["Front"] != "")
        textureName = QString().fromStdString(_m_textures["Front"]);
    else if(_m_textures["Left"] != "")
        textureName = QString().fromStdString(_m_textures["Left"]);
    else if(_m_textures["Back"] != "")
        textureName = QString().fromStdString(_m_textures["Back"]);
    else if(_m_textures["Right"] != "")
        textureName = QString().fromStdString(_m_textures["Back"]);
    else if(_m_textures["Top"] != "")
        textureName = QString().fromStdString(_m_textures["Top"]);
    else if(_m_textures["Bottom"] != "")
        textureName = QString().fromStdString(_m_textures["Bottom"]);
    else{
        QPixmap pix(200,200);
        QPainter painter(&pix);
        painter.setBackground(QBrush(_color));
        painter.setPen(_color);
        painter.drawPoint(0,0);
        painter.fillRect(QRectF(0,0,200,200),_color);
        painter.end();

        qDebug() << _color.red() << _color.green() << _color.blue();
        setPixmap(pix);
        return;
    }

    qDebug() << textureName;
    setPixmap(QPixmap("mediaOgre/materials/textures/" + textureName ));
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

