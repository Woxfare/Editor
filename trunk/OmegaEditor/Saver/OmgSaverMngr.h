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

#ifndef OMGSAVERMNGR_H
#define OMGSAVERMNGR_H

#include <map>
#include <QString>
#include "Omega.h"
#include "OmgEntities/OmgEntity.h"

class OmgSaverMngr
{
public:

    /*!
     * \brief Instance
     * \return
     */
    static OmgSaverMngr* Instance( void );

    /*!
     * \brief IsAllSaved
     * \return
     */
    bool isAllSaved( void );

    /*!
     * \brief addEntityToSave The entity to be saved
     * \param aEntity
     */
    void addEntityToSave( OmgEntity* aEntity );

    /*!
     * \brief saveAll
     */
    void saveAll(void);

    /*!
     * \brief entityDeleted
     */
    void entityDeleted( void );

protected:
    /*!
     * \brief OmgSaverMngr
     */
    OmgSaverMngr();

private:
    /*!
     * \brief _mapEntitiesToSave
     */
    std::map<QString,OmgEntity*> _mapEntitiesToSave;

    /*!
     * \brief _p_instance
     */
    static OmgSaverMngr * _p_instance;

    /*!
     * \brief _allSaved
     */
    bool _allSaved;
};

#endif // OMGSAVERMNGR_H
