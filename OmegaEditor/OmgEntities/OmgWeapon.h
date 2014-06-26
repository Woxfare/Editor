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

#ifndef OMGWEAPON_H
#define OMGWEAPON_H

#include "OmgEntity.h"

class QXmlStreamWriter;

class OmgWeapon : public OmgEntity
{
public:
    /*!
     * \brief OmgWeapon
     * \param a_name
     */
    OmgWeapon( QString a_name, QString a_folderName );

    /*!
     * \brief getWeaponType
     * \return
     */
    Omega::WeaponType getWeaponType( void );

    /*!
     * \brief getWeaponType
     * \return
     */
    QString getWeaponTypeStr( void );

    /*!
     * \brief setWeaponType
     * \param aType
     */
    void setWeaponType( Omega::WeaponType aType );

    /*!
     * \brief getDefaultBullets
     * \return
     */
    int getDefaultBullets( void );

    /*!
     * \brief setDefaultBullets
     */
    void setDefaultBullets( int nBullets);

	
    /*!
     * \brief getDefaultBullets
     * \return
     */
    int getDamage( void );

    /*!
     * \brief setDefaultBullets
     */
    void setDamage( int damage );

    /*!
     * \brief writeInfo
     * \param[in] QXmlStreamWriter a_xml_stream
     */
    virtual void writeInfo( QXmlStreamWriter *a_xml_stream );
private:

    /*!
     * \brief _weaponType
     */
    Omega::WeaponType _weaponType;

    /*!
     * \brief _nBullets
     */
    int _nBullets;

	int _damage;
};

#endif // OMGWEAPON_H
