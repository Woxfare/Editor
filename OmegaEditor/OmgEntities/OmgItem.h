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

#ifndef OMGITEM_H
#define OMGITEM_H

#include "OmgCube.h"
#include "InputData/QOmgListItem.h"

class QXmlStreamWriter;

class OmgItem : public OmgCube
{
public:

    /*!
     * \brief OmgItem
     * \param aName
     * \param aTextures
     * \param avRgb
     */
    OmgItem( const QString &aName, const QString &folderName, std::map<std::string, std::string> aTextures, int avRgb[3]);

    /*!
     * \brief OmgItem Default Destructor
     */
    ~OmgItem();

    /*!
     * \brief setItemType
     * \param aType
     */
    void setItemType( Omega::ItemType aType );

    /*!
     * \brief itemType
     * \return
     */
    Omega::ItemType itemType( void );

    /*!
     * \brief itemTypeStr
     * \return
     */
    QString itemTypeStr( void );

    /*!
     * \brief getWeapon
     * \return
     */
    QString getWeapon( void );

    /*!
     * \brief setWeapon
     * \return
     */
    void setWeapon( QString weapon );

    /*!
     * \brief getWeapon
     * \return
     */
    int getQuantity( void );

    /*!
     * \brief setWeapon
     * \return
     */
    void setQuantity( int a_quantity );

    /*!
     * \brief writeInfo
     * \param[in] QXmlStreamWriter a_xml_stream
     */
    virtual void writeInfo( QXmlStreamWriter *a_xml_stream );

private:
    /*!
     * \brief _itemType
     */
    Omega::ItemType _itemType;

    QString weaponName;

    int quantity;
};

#endif // OMGITEM_H
