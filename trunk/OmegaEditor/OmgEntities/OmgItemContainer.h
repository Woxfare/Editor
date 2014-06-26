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

#ifndef OMGITEMCONTAINER_H
#define OMGITEMCONTAINER_H

#include "OmgItem.h"
#include <QString>
#include <map>
#include "InputData/QOmgListItem.h"

class OmgItemContainer
{
public:

    /*!
     * \brief Instance
     * \return
     */
    static OmgItemContainer* Instance( void );

    /*!
     * \brief getItem
     * \param aName
     * \return
     */
    OmgItem* getItem( QString aName );

    /*!
     * \brief AddItem
     * \param a_player
     * \return
     */
    bool addItem( OmgItem* aItem );

    /*!
     * \brief deleteItem
     * \param aName
     * \return
     */
    bool deleteItem(QString aName );

    /*!
     * \brief availableItems
     * \return
     */
    Omega::EntityVector availableItems( void );

    /*!
     * \brief availableListItems
     * \return
     */
    Omega::ListItemVector availableListItems(void);

    /*!
     * \brief ItemsInFolder
     * \param aFolderName
     * \return
     */
    Omega::EntityVector itemsInFolder(QString aFolderName );

    /*!
     * \brief Load
     * \param filename
     */
    //void load(QString filename);

    /*!
     * \brief Destructor
     */
    ~OmgItemContainer();

    /*!
     * \brief buildItem
     * \param aItemParams
     */
    void buildItem( QStringList aItemParams );

protected:
    /*!
     * \brief OmgItemContainer
     */
    OmgItemContainer();

private:
    /*!
     * \brief _map_items
     */
    std::map< QString, OmgItem*> _map_items;

    /*!
     * \brief _p_instance
     */
    static OmgItemContainer* _p_instance;
};

#endif // OMGITEMCONTAINER_H
