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
#ifndef OMGENEMY_H
#define OMGENEMY_H

#include "OmgCharacter.h"
#include <QString>
#include "QtComponents/QOmgListItem.h"

class QXmlStreamWriter;

class OmgEnemy : public OmgCharacter
{
public:
    /*!
     * \brief Default Constructor
     * \param a_name Enemy Name
     */
    OmgEnemy( QString a_name , QString folderName );

    /*!
     * \brief Default Destructor
     */
    ~OmgEnemy();

    /*!
     * \brief Gets the Enemy Type
     * \return Omega::EnemyType with the type
     */
    Omega::EnemyType enemyType( void );

    /*!
     * \brief SetEnemyType
     * \param aType the type of enemy
     */
    void setEnemyType( Omega::EnemyType aType );

    /*!
     * \brief writeInfo
     * \param[in] QXmlStreamWriter a_xml_stream
     */
    virtual void writeInfo( QXmlStreamWriter *a_xml_stream );

	/*!
     * \brief Gets the enemy type in string format
     */
	QString getEnemyTypeStr( void );

	/*!
     * \brief Gets the enemy type in string format
     */
	QString getItemName();

	/*!
     * \brief Set item name
     */
	void setItemName( QString aName );

private:

    /*!
     * \brief enemyType
     */
    Omega::EnemyType _enemyType;

	/*!
     * \brief item name
     */
	QString _itemName; 
};

#endif // OMGENEMY_H
