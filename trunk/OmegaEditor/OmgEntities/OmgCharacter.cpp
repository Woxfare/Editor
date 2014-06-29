/*
				         ___  __  __ ______  ____  ___
				        / _ \|  \/  |  ____|/ ___|/ _ \
	 		         | | | |      | |__  | |   | | | |
               | | | | |\/| |  __| | |  _| |_| |
               | |_| | |  | | |____| |_| |  _  |
                \___/|_|  |_|______|\____|_| |_|

	Copyright (c) 2014 Fernando Perera & Alejandro Vázquez

	Permission is hereby granted, free of charge, to any person obtaining
	a copy of this software and associated documentation files (the
	"Software"), to deal in the Software without restriction, including
	without limitation the rights to use, copy, modify, merge, publish,
	distribute, sublicense, and/or sell copies of the Software, and to
	permit persons to whom the Software is furnished to do so, subject to
	the following conditions:

	The above copyright notice and this permission notice shall be
	included in all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
	MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
	LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
	OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
	WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#include "OmgCharacter.h"
#include <QDebug>
#include "qpainter.h"
#include "qbrush.h"
#include "qpixmap.h"
#include "qfile.h"

#include <QXmlStreamWriter>
#include "OmgEntities/OmgWeapon.h"

OmgCharacter::OmgCharacter(QString aName, QString aFolderName) : OmgEntity( aName, aFolderName), _totalLife( 0 ), _points( 0 ){}

int
OmgCharacter::getTotalLife( void )
{
    return _totalLife;
}


void
OmgCharacter::setTotalLife(int aLife)
{
    _totalLife = aLife;
}

int
OmgCharacter::getPoints( void )
{
    return _points;
}

void
OmgCharacter::setPoints( int aPoints )
{
    _points = aPoints;
}

void
OmgCharacter::setTextures( std::map<std::string, std::map<std::string, std::string>> aTextures )
{
  _textures = aTextures;
  createCustomPixmap();
}

std::map<std::string, std::map<std::string, std::string>>
OmgCharacter::getTextures( void )
{
  return _textures;
}

void
OmgCharacter::createCustomPixmap( void )
{ 
    QString textureName = "";

    std::map<std::string, std::string> head_textures = _textures["Head"];
    if(head_textures["Front"] != "")
      textureName = QString().fromStdString(head_textures["Front"]);
    else{
      QPixmap pix(200,200);
      QPainter painter(&pix);
      painter.setBackground(QBrush(_color));
      painter.setPen(_color);
      painter.drawPoint(0,0);
      painter.fillRect(QRectF(0,0,200,200),_color);
      painter.end();

      setPixmap(pix);
      return;
    }

    QPixmap image = QPixmap( );
    image.load( "Resources/materials/textures/" + textureName );
    image = image.scaled( QSize( 128, 128 ), Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
    setPixmap(image);
}

void
OmgCharacter::writeTextures( QXmlStreamWriter *a_xml_stream )
{
  a_xml_stream->writeStartElement("textures");
  std::string characterParts[] = {"Head", "Body", "ArmL", "ArmR", "LegL", "LegR" };
  for( int i = 0; i < 6 ; ++i )
  {
    std::map<std::string, std::string> part = _textures[characterParts[i]];
    a_xml_stream->writeStartElement( QString().fromStdString(characterParts[i]) );

    std::map< std::string, std::string >::iterator it = part.begin(), itEnd = part.end();
    for(; it!=itEnd; ++it)
      a_xml_stream->writeAttribute( QString().fromStdString( (*it).first ), QString().fromStdString( (*it).second ) );

    a_xml_stream->writeEndElement(); // current part
  }

  a_xml_stream->writeEndElement(); // textures
}

void
OmgCharacter::setWeapon( OmgWeapon* a_weapon )
{
  weapon = a_weapon;
}

OmgWeapon*
OmgCharacter::getWeapon( void )
{
  return weapon;
}