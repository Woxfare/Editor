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

#ifndef CHARACTERPARTSSELECTORWIDGET_H
#define CHARACTERPARTSSELECTORWIDGET_H

#include <QWidget>
#include "EditionManagers/EditCharacterManager.h"

namespace Ui {
class CharacterPartsSelectorWidget;
}

class CharacterPartsSelectorWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit CharacterPartsSelectorWidget(QWidget *parent = 0);
    ~CharacterPartsSelectorWidget();
	void changeTextureOfPart( characterParts part, QString textureName );

private slots:
    void on_head_clicked();

    void on_body_clicked();

    void on_rightArm_clicked();

    void on_leftArm_clicked();

    void on_rightLeg_clicked();

    void on_leftLeg_clicked();

private:
    Ui::CharacterPartsSelectorWidget *ui;

    bool headVisible;
    bool bodyVisible;
    bool armLeftVisible;
    bool armRightVisible;
    bool legLeftVisible;
    bool legRightVisible;

    QString pushedStyle;

    QString noPushedStyle;

    void ShowSelectedParts( void );

	std::map< characterParts, QIcon > _map_icons_parts;

};

#endif // CHARACTERPARTSSELECTORWIDGET_H
