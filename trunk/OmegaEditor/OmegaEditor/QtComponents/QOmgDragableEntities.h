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

#ifndef QOMGDRAGABLEENTITIES_H
#define QOMGDRAGABLEENTITIES_H

#include <QWidget>
#include <QHBoxLayout>
#include "Omega.h"
#include <set>

namespace Ui {
class QOmgDragableEntities;
}

class QOmgDragableEntities : public QWidget
{
    Q_OBJECT
    
public:
    explicit QOmgDragableEntities(QWidget *parent = 0);
    ~QOmgDragableEntities();

    void Update( OmgEntity* aEntity );
    void Update( void );
    void deselectItem( void );

private slots:

    void on__search_textChanged(const QString &arg1);

    void on__update_clicked();

    void ItemSelected( QOmgListItem* item );

    void enemyDoorButtonPressed( void );

	void playerDoorButtonPressed( void );

private:
    Ui::QOmgDragableEntities *ui;

    QVBoxLayout * _p_list_widget;

    Omega::ListItemVector _v_show_items;

    Omega::ListItemVector _v_hide_items;

    Omega::ListItemVector _v_items;

    QWidget *viewport;

    void ShowAll( void );

    std::set<Omega::EntityType> set_entities;

    QOmgListItem* _lastItemSelected;

    bool _doorButtonPressed;
	bool _playerDoorButtonPressed;

    QString pushedStyle, noPushedStyle;

};

#endif // QOMGDRAGABLEENTITIES_H
