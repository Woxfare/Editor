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

#ifndef MOUSESCENARYEDIT_H
#define MOUSESCENARYEDIT_H

#include <Ogre.h>
#include <Qt>
#include "MouseController.h"

class MouseScenaryEdit : public MouseController
{
public:

    /*!
     * \brief Controler constructor
     */
    MouseScenaryEdit();

    /*!
     * \brief Handles a moved mouse event
     * \param Wich button is pressed
     * \param x Window x
     * \param y Window y
     * \param width Window width
     * \param height Window height
     */
    virtual void buttonPressed( Qt::MouseButton pressed, int x, int y, int width, int height );

    /*!
     * \brief Handles a moved mouse event
     * \param x Window x
     * \param y Window y
     * \param width Window width
     * \param height Window height
     */
    virtual void moved(int x, int y, int width, int height);

    /*!
     * \brief buttonReleased
     * \param x Window x
     * \param y Window y
     * \param width Window width
     * \param height Window height
     */
    virtual void buttonReleased(int x, int y, int width, int height);

    /*!
     * \brief Handles a wheel rotation event
     * \param delta
     */
    virtual void wheelMoved(int delta);

    /*!
     * \brief Handles a double click event
     * \brief Options: RightButton Changes the look at Point
     * \param x Window x
     * \param y Window y
     * \param width Window width
     * \param height Window height
     * \param widget Not used
     */
    virtual void doubleClickEvent(int x, int y, int width, int height, QWidget * widget);

    /*!
     * \brief Change the current object
     * \param nameObjet The name of the new current obj
     */
    void changeCurrentObject(std::string nameObject);

    /*!
     * \brief Gets the current object name
     * \return std::string with the current object name
     */
    std::string currentObjectName( void );

    /*!
     * \brief Changes the state of pressed or relased of the control button
     * \param True pressed or false released
     */
    void controlKeyPressed( bool pressed );

    /*!
     * \brief Enables or disables the delete mode of the scenery
     * \param True to enable or false to disable
     */
    void deleteMode( bool pressed );

    
    /*!
     * \brief Enables or disables the scaling mode of the scenery
     * \param True to enable or false to disable
     */
    void scaleMode( bool pressed );

    /*!
     * \brief Deletes an object in the scene
     * \param x Window x
     * \param y Window y
     * \param width Window width
     * \param height Window height
     */
    void deleteMeshOnRay(int x, int y , int width, int height);

    /*!
     * \brief Scales an object in the scene
     * \param x Window x
     * \param y Window y
     * \param width Window width
     * \param height Window height
     */
    void scaleMeshOnRay(int x, int y , int width, int height);

    /*!
     * \brief Rotates the camera with the given differences of x and y values, taking into account the look at point of the camera
     * \param dx Difference between lastX and currentX
     * \param dy Difference between lastX and currentX
     * \param cam The scenery camera
     */
    virtual void rotateCam(Ogre::Real dx, Ogre::Real dy, Ogre::Camera *cam);

    void arrowKeyPressed( Qt::Key key );

private:

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Members ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
    /*!
     * \brief _p_currentObject
     */
    Ogre::SceneNode        * _p_currentObject;

    /*!
     * \brief _editScenaryCamera
     */
    Ogre::Camera           * _editScenaryCamera;

    /*!
     * \brief _currentObjectName
     */
    std::string             _currentObjectName;

    /*!
     * \brief mCount
     */
    int                      mCount;

    /*!
     * \brief _lastPnt
     */
    Ogre::Vector3          _lastPnt;

    /*!
     * \brief _pointToLookAt
     */
    Ogre::Vector3          _pointToLookAt;

    /*!
     * \brief _controlKeyPressed
     */
    bool                    _controlKeyPressed;

    /*!
     * \brief _deleteMode
     */
    bool                    _deleteMode;

    /*!
     * \brief _scaleMode
     */
    bool                    _scaleMode;

    /*!
     * \brief _radius
     */
    Ogre::Real              _radius;

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Methods ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
    /*!
     * \brief Inits the edit scenary camera
     */
    void initControlerCamera( void );

    /*!
     * \brief Adds a new object to the scene
     * \param mouseRay The ray of the scene
     * \param x Position x to draw the object
     * \param y Position y to draw the object
     */
    void addObjectToScene( Ogre::Ray mouseRay, int x, int y);

    /*!
     * \brief Change the look at point of the edit scenary camera
     * \param mouseRay The ray of the scene
     * \param x Position x to draw the object
     * \param y Position y to draw the object
     */
    void changeLookAt( Ogre::Ray mouseRay, int x, int y);

    /*!
     * \brief Stores the yaw and pitch values of the rotation
     */
    void finnishRotation();

    /*!
     * \brief Gets the new position of the camera with a yaw and pitch
     * \param newYaw
     * \param newPitch
     * \return Ogre::Vector3
     */
    Ogre::Vector3 getNewCameraRotationPos( Ogre::Radian newYaw, Ogre::Radian newPitch);

    /*!
     * \brief Translates the camera
     * \param x Window x
     * \param y Window y
     * \param width Window width
     * \param height Window height
     */
    void translateCamera( int x, int y, float width, float height );


    /*!
     * \brief Moves the object
     * \param x Window x
     * \param y Window y
     * \param width Window width
     * \param height Window height
     */
    void moveObject( int x, int y, float width, float height );
};

#endif // MOUSECONTROLLER_H
