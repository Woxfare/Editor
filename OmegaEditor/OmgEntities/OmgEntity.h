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
#ifndef OMGENTITY_H
#define OMGENTITY_H

#include <QString>
#include <QPixmap>
#include <QColor>
#include <Ogre.h>

#include "Omega.h"
#include "Folders/OmgFolder.h"

class QOmgListItem;
class QXmlStreamWriter;

class OmgEntity
{
public:

    /*!
     * \brief OmgEntity Default Constructor
     * \param a_name
     */
    OmgEntity( const QString &aName, const QString &folderName );

	virtual ~OmgEntity();

    /*!
     * \brief getName Gets the name of the entity
     * \return QString with the name of the entity
     */
    virtual QString getName( void );

    /*!
     * \brief getType Gets the type of the entity
     * \return EntityType
     */
    Omega::EntityType getType( void );

    /*!
     * \brief getPixmap Gets the pixmap of the entity
     * \return QPixmap
     */
    QPixmap getPixmap( void );

    /*!
     * \brief setName Sets the name to the entity
     * \param a_name The name for the entity
     */
    void setName( QString aName );

    /*!
     * \brief getFolderName
     * \return QString With the name of the folder
     */
    QString getFolderName( void );

    /*!
     * \brief setFolderName Sets the folder name
     * \param aFolderName The name of the folder
     */
    void setFolderName( QString aFolderName );

    /*!
     * \brief setType Sets the type of the entity
     * \param aType
     */
    void setType( Omega::EntityType aType );

    /*!
     * \brief setPixmap Sets the pixmap
     * \param aPix
     */
    void setPixmap( QPixmap aPix );

    /*!
     * \brief setColor
     * \param aColor
     */
    void setColor( QColor aColor );

    /*!
     * \brief getColor
     * \return QColor
     */
    QColor getColor( void );

    /*!
     * \brief getListItem
     */
    virtual QOmgListItem* listItem( void );

    /*!
     * \brief writeInfo
     * \param[in] QXmlStreamWriter a_xml_stream
     */
    virtual void writeInfo( QXmlStreamWriter *a_xml_stream );

	void writeColor( QXmlStreamWriter *a_xml_stream );

protected:

    /*!
     * \brief _name
     */
    QString _name;

    /*!
     * \brief _type
     */
    Omega::EntityType _type;

    /*!
     * \brief _pixmap
     */
    QPixmap _pixmap;

    /*!
     * \brief _folder
     */
    QString _folder;

    /*!
     * \brief _color
     */
    QColor _color;
};

#endif // OMGENTITY_H
