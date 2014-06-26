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

#ifndef EntitiesXMLReader_H
#define EntitiesXMLReader_H

#include <vector>
#include <map>
#include <QFile>
#include <Ogre.h>

class QString;
class QXmlStreamReader;

class OmgEntity;

class EntitiesXMLReader
 {
public:
  EntitiesXMLReader( const QString a_fileName );

private:

  void parsePlayer( QXmlStreamReader& xml );
  void parseEnemy( QXmlStreamReader& xml );
  void parseSceneObject( QXmlStreamReader& xml );
  void parseItem( QXmlStreamReader& xml );
  void parseWeapon( QXmlStreamReader& xml );
  void parseMap( QXmlStreamReader& xml );
  void parseGame( QXmlStreamReader& xml );

  void parseColor( QXmlStreamReader& xml, int& r, int& g, int& b );
  void parseCharacterTextures( QXmlStreamReader& xml, std::map<std::string, std::map<std::string, std::string>>& ar_textures );
  void parseCubeTextures( QXmlStreamReader& xml, std::map<std::string, std::string>& ar_textures );
  void parseMapObjects( QXmlStreamReader& xml, std::vector< std::pair < std::string, std::vector< Ogre::Vector3 > > >& ar_objects );
  void parseSingleCube( QXmlStreamReader& xml, std::pair< std::string, std::vector< Ogre::Vector3 > > &cube );
};

#endif // EntitiesXMLReader_H