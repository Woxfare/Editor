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

#ifndef OMGFOLDERSMNGR_H
#define OMGFOLDERSMNGR_H

#include <map>
#include <vector>
#include <QString>
#include "OmgFolder.h"

class OmgFoldersMngr
{
public:
    /*!
     * \brief Instance
     * \return
     */
    static OmgFoldersMngr* Instance( void );

    /*!
     * \brief getFolder
     * \param aName
     * \return OmgFolder
     */
    OmgFolder* getFolder(QString aName );

    /*!
     * \brief addFolder
     * \param a_folder
     */
    void addFolder( OmgFolder* a_folder );

    /*!
     * \brief deleteFolder
     * \param aFolder
     */
    void deleteFolder(QString aFolder);

    /*!
     * \brief getAvailableFolders
     * \param aType
     * \return
     */
    Omega::FolderVector getAvailableFolders(Omega::FolderType aType );

protected:
    /*!
     * \brief OmgFoldersMngr
     */
    OmgFoldersMngr();

private:
    /*!
     * \brief _map_folders
     */
    std::map<QString,OmgFolder*> _map_folders;

    /*!
     * \brief _p_instance
     */
    static OmgFoldersMngr * _p_instance;
};

#endif // OMGFOLDERSMNGR_H
