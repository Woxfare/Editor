#ifndef QOMGTREEENTITIES_H
#define QOMGTREEENTITIES_H

#include "QOmgTree.h"
#include <vector>
#include <QTreeWidgetItem>
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

#include <QMouseEvent>
#include <QPoint>
#include "OmgEntities/OmgEntity.h"

class QOmgTreeEntities : public QOmgTree
{
    Q_OBJECT

public:
    explicit QOmgTreeEntities(QWidget *parent = 0);
    ~QOmgTreeEntities();

    void UpdateTree(OmgEntity *p_entity);
    void UpdateTree();

private:

    void AddSceneObjectsToTheTree( void );
    void PushSceneObj( QTreeWidgetItem *p_item );
    void AddEnemiesToTheTree( void );
    void PushEnemies( QTreeWidgetItem* p_item );
    void AddPlayersToTheTree( void );
    void PushPlayers( QTreeWidgetItem* p_item );
    void AddItemsToTheTree( void );
    void PushItems( QTreeWidgetItem* p_item );
    void addWeaponsToTheTree( void );
    void pushWeapons( QTreeWidgetItem* pItem );
    void addMapsToTheTree( void );
    void pushMaps( QTreeWidgetItem* pItem );
	void addGamesToTheTree( void );
	void pushGames( QTreeWidgetItem* pItem );

    std::vector<QTreeWidgetItem*> _v_items;
};

#endif // QOMGTREEENTITIES_H
