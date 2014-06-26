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

#ifndef MouseCharacterEDIT_H
#define MouseCharacterEDIT_H
#include <Ogre.h>
#include <Qt>
#include "MouseController.h"

class MouseCharacterEdit: public MouseController
{
public:
    MouseCharacterEdit();
    virtual void buttonPressed( Qt::MouseButton pressed, int x, int y, int width, int height );
    virtual void moved(int x, int y, int width, int height);
    virtual void buttonReleased(int x, int y, int width, int height);
    virtual void wheelMoved(int delta);
	virtual void doubleClickEvent(int x, int y, int width, int height, QWidget * widget);
	std::string  selectCharacterFace(Ogre::Vector3 colisionPoint);

protected:

    virtual void initControlerCamera( void );

private:

	Ogre::Camera *_editCharacterCamera;

	void changeTextureOfFace(Ogre::ManualObject * selectedFace , QWidget * widget);

};

#endif // MOUSECONTROLLER_H
