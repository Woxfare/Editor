/*
				        ____  __  __ ______  ____  ___
				       /  _ \|  \/  |  ____|/ ___|/ _ \
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

#ifndef OmgWeaponsContainer_H
#define OmgWeaponsContainer_H

class OmgWeapon;

#include "Omega.h"

class OmgWeaponsContainer
{
public:
    /*!
     * \brief Instance
     * \return
     */
    static OmgWeaponsContainer* Instance( void );

    /*!
     * \brief getWeapon
     * \param aName
     * \return
     */
    OmgWeapon* getWeapon( QString aName );

    /*!
     * \brief addWeapon
     * \param aWeapon
     * \return
     */
    bool addWeapon( OmgWeapon* aWeapon );

    /*!
     * \brief deleteWeapon
     * \param aName
     */
    void deleteWeapon( QString aName );

    /*!
     * \brief availableWeapons
     * \return
     */
    Omega::EntityVector availableWeapons( void );

    /*!
     * \brief availableWeponsItems
     * \return
     */
    Omega::ListItemVector availableWeaponsItems( void );

    /*!
     * \brief weaponsInFolder
     * \param aFolderName
     * \return
     */
    Omega::EntityVector weaponsInFolder( QString aFolderName );

    /*!
     * \brief buildWeapon
     * \param weaponParams
     */
    void buildWeapon( QStringList weaponParams );

protected:
    /*!
     * \brief OmgWeaponsContainer
     */
    OmgWeaponsContainer();

private:

    /*!
     * \brief _map_Weapons
     */
    Omega::WeaponsMap _mapWeapons;

    /*!
     * \brief _p_instance
     */
    static OmgWeaponsContainer* _p_instance;
};

#endif // OmgWeaponsContainer_H
