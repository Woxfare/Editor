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

#ifndef MOUSECONTROLLER_H
#define MOUSECONTROLLER_H
#include <Ogre.h>
#include <Qt>
#include "Utils/OgreManager.h"

#define MOUSE_SENSIBILITY 10
#define ROTATION_SPEED 0.004

class MouseController
{
public:
    MouseController();
    virtual void buttonPressed( Qt::MouseButton pressed, int x, int y, int width, int height )=0;
    virtual void moved(int x, int y, int width, int height)=0;
    virtual void buttonReleased(int x, int y, int width, int height)=0;
    virtual void wheelMoved(int delta)=0;
    virtual void doubleClickEvent(int x, int y, int width, int height, QWidget * widget)=0;
    virtual void rotateCam(Ogre::Real dx, Ogre::Real dy, Ogre::Camera *cam );

protected:
    Qt::MouseButton          _lastPressed;
    int                      _lastX;
    int                      _lastY;
    bool                     _continuePress;
    Ogre::RaySceneQuery    * _p_raySceneQuery;
    Ogre::Degree             _yawValue;
    Ogre::Degree             _pitchValue;
    Ogre::Degree             _lastYawValue;
    Ogre::Degree             _lastPitchValue;

};

#endif // MOUSECONTROLLER_H

