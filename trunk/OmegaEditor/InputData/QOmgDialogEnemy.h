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

#ifndef QOMGDIALOGENEMY_H
#define QOMGDIALOGENEMY_H

#include "QOmgDialogCharacter.h"
#include "OmgEntities/OmgEnemy.h"

class QListWidgetItem;

class QOmgDialogEnemy : public QOmgDialogCharacter
{
public:

    //- QOmgDialogEnemy
    //? Default constructor for new enemies
    //> QWidget the parent widget
    QOmgDialogEnemy(QWidget *ap_parent);


    //- QOmgDialogEnemy
    //? Default constructor for edit enemies
    //> QWidget the parent widget
    //> OmgEnemy the enemy to edit
    QOmgDialogEnemy( QWidget *ap_parent, OmgEnemy* ap_enemy );

protected:

    //? The enemy
    OmgEnemy* _p_enemy;

    void SetEnemyInDialog( void );

    bool Validate( void );

    void PutEnemyInQt( void );

protected slots:
    virtual void on__new_char_clicked( void );

    virtual void on__edit_char_clicked( void );

private:

    QListWidgetItem* findFolderItemByName(QString aName);
    OmgEnemy* createEnemy( void );
    void storeAndFinish( OmgEnemy* apEnemy );
};

#endif // QOMGDIALOGENEMY_H
