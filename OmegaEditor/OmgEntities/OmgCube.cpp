#include "OmgCube.h"
#include "Utils/OgreManager.h"
#include <QDebug>
#include <stdio.h>
#include <QPixmap>
#include <QBitmap>
#include <QPainter>
#include "Utils/CubeUtils.h"
#include <QXmlStreamWriter>

OmgCube::OmgCube(QString a_name, std::map<std::string, std::string> a_textures, int rgb[3]) : OmgEntity ( a_name )
{
    _color.setRgb(rgb[0],rgb[1],rgb[2]);
    _m_textures = a_textures;
}

OmgCube::~OmgCube()
{

}

std::map<std::string, std::string>
OmgCube::getTextures( void )
{
    return _m_textures;
}

void
OmgCube::createCustomPixmap( void )
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
		painter.setBackgroundMode(Qt::TransparentMode);
        painter.setPen(_color);
        painter.drawPoint(0,0);
        painter.fillRect(QRectF(0,0,200,200),_color);
        painter.end();
        setPixmap(pix);
        return;
    }
	QPixmap customPix( "Resources/materials/textures/" + textureName  );
    setPixmap( customPix );

}

void
OmgCube::writeInfo( QXmlStreamWriter *a_xml_stream )
{
}

