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
#ifndef QOMGDIALOGCHARACTER_H
#define QOMGDIALOGCHARACTER_H

#include "ui_QOmgDialogCharacter.h"
#include "QOmgFolderDialog.h"
#include "InputData.h"

namespace Ui {
class QOmgDialogCharacter;
}

class QOmgDialogCharacter : public InputData
{
    Q_OBJECT
    
public:
    explicit QOmgDialogCharacter(QWidget *parent = 0, bool a_edit = false );
    ~QOmgDialogCharacter();

public slots:
    void ChangeWidgetsForPlayer( void );

    void ChangeWidgetsForEnemy( void );
    
    virtual void on__new_char_clicked();

    virtual void on__edit_char_clicked();

protected:

    Ui::QOmgDialogCharacter *ui;
    bool _editing;
    QString _folder;

private slots:
    void on_pushButton_clicked();
    void on__pb_textures_clicked();
    void on__type_enemy_currentIndexChanged(const QString &arg1);
    void on_deleteTextures_clicked();
};

#endif // QOMGDIALOGCHARACTER_H
