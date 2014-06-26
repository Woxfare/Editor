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

#ifndef OMGCHARACTER_H
#define OMGCHARACTER_H

#include "OmgEntity.h"
#include <set>

class QXmlStreamWriter;
class OmgWeapon;
class OmgCharacter : public OmgEntity
{
public:
    /*!
     * \brief OmgCharacter Default Constructor
     * \param a_name
     * \param a_folder
     */
    OmgCharacter(QString aName, QString aFolderName );

    /*!
     * \brief getTotalLife
     * \return int total life
     */
    int getTotalLife( void );

    /*!
     * \brief setTotalLife
     * \param aLife
     */
    void setTotalLife( int aLife );

    /*!
     * \brief getPoints
     * \return
     */
    int getPoints( void );

    /*!
     * \brief setPoints
     * \param aPoints
     */
    void setPoints( int aPoints );

    /*!
     * \brief Sets the textures to the player
     */
    void setTextures( std::map<std::string, std::map<std::string, std::string>> aTextures );

    /*!
     * \brief Gets the textures of the player
     */
    std::map<std::string, std::map<std::string, std::string>> getTextures(void);

    /*!
     * \brief getWeapon
     * \return
     */
    OmgWeapon* getWeapon( void );

    /*!
     * \brief setWeapon
     * \return
     */
    void setWeapon( OmgWeapon* weapon );

    /*!
     * \brief Creates a custom pixmap with the textures
     */
    void createCustomPixmap( void );

protected:

 /*!
  * \brief Gets the textures of the player
  */
  void writeTextures( QXmlStreamWriter *a_xml_stream );

protected:

    /*!
     * \brief _totalLife
    */
    int _totalLife;

    /*!
     * \brief _weapons
     */
    OmgWeapon* weapon;

    /*!
     * \brief _points
     */
    int _points;

    /*!
     * \brief _textures
     */
    std::map<std::string, std::map<std::string, std::string>> _textures;
};

#endif // OMGCHARACTER_H
