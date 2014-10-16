/*
				 ___  __  __ ______  ____  ___
				/ _ \|  \/  |  ____|/ ___|/ _ \
	 		   | | | |      | |__  | |   | | | |
               | | | | |\/| |  __| | |  _| |_| |
               | |_| | |  | | |____| |_| |  _  |
                \___/|_|  |_|______|\____|_| |_|

	Copyright (c) 2014 Fernando Perera & Alejandro V�zquez

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

#ifndef OMGFOLDER_H
#define OMGFOLDER_H

#include <QString>
#include "Omega.h"

class OmgFolder
{
public:

    /*!
     * \brief OmgFolder
     * \param aName
     * \param aType
     */
    OmgFolder( QString aName, Omega::FolderType aType );

    /*!
     * \brief getName
     * \return
     */
    QString getName( void );

    /*!
     * \brief setName
     * \param aName
     */
    void setName( QString aName );

    /*!
     * \brief getType
     * \return
     */
    Omega::FolderType getType( void );

    /*!
     * \brief setType
     * \param aType
     */
    void setType(Omega::FolderType aType );

    /*!
     * \brief isDefault
     * \return if the folder is default
     */
    bool isDefault( void );

    /*!
     * \brief setDefault Sets the folder to a default
     */
    void setDefault( void );

private:

    /*!
     * \brief _name
     */
    QString  _name;

    /*!
     * \brief _type
     */
    Omega::FolderType _type;

    /*!
     * \brief _def
     */
    bool _def;
};

#endif // OMGFOLDER_H