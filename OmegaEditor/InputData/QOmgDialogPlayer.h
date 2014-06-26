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

#ifndef QOMGDIALOGPLAYER_H
#define QOMGDIALOGPLAYER_H

#include "QOmgDialogCharacter.h"
#include "OmgEntities/OmgPlayer.h"

class QListWidgetItem;

class QOmgDialogPlayer : public QOmgDialogCharacter
{
public:
    QOmgDialogPlayer(QWidget *ap_parent);

    QOmgDialogPlayer( QWidget *ap_parent, OmgPlayer *ap_player );

protected:

    OmgPlayer* _p_player;

    bool Validate( void );

    void putPlayerInQt( void );

protected slots:
    virtual void on__new_char_clicked( void );

    virtual void on__edit_char_clicked( void );

private:
    QListWidgetItem* findFolderItemByName(QString aName);

    OmgPlayer* createPlayer( void );
    void storeAndFinish( OmgPlayer* apPlayer );
};

#endif // QOMGDIALOGPLAYER_H
