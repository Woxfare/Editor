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

#ifndef EditCubeManager_H
#define EditCubeManager_H

#include <Ogre.h>

class EditCubeManager
{
public:

  ~EditCubeManager();
  /*!
   * \brief Gets an instance to the manager
   * \return
   */
  static EditCubeManager * getInstance();

  /*!
   * \brief Clears the character
   */
  void clearEditCube( void );

  /*!
  * \brief Gets whole edited character in the scene
	* \return the character edited
  */
  std::map<std::string, std::string> getEditCube( void );

 /*!
  * \brief Changes the edit cube color
  */
  void changeEditCubeColor( int rgb[3] );

  /*!
  * \brief Changes the edit cube color
  */
  void changeEditCubeTextures( std::map<std::string, std::string> textures );

 /*!
  * \brief setLastTexture to the edit cube manager
  */
  void setLastTexture( std::string texture );

 /*!
  * \brief Sets all the textures equal to the last textures
  */
  void setAllTexturesEqual( void );

private:

  /*!
  * \brief EditCubeManager Constructor
  */
  EditCubeManager();

  /*!
  * \brief _p_instance
  */
  static EditCubeManager  * _p_instance;

  /*!
  * \brief _lastTexture
  */
  std::string _lastTexture;

  /*!
  * \brief Creates the character to edit
  */
  void createEditCube();
};

#endif // EditCubeManager_H