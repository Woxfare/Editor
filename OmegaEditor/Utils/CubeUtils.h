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
#ifndef CubeUtils_H
#define CubeUtils_H

#include <Ogre.h>

class CubeUtils
{
public:
  /*!
   * \brief Sets the textures to a selected cube
   * \param[in] cube name
   * \param[in] the textures
   */
  static void setTexturesToCube(Ogre::String baseName, std::map<std::string, std::string> textures);

  /*!
   * \brief Sets the color to a selected cube
   * \param[in] cube name
   * \param[in] the color
   */
  static void setColorToCube( Ogre::String baseName, int rgb[3] );

  /*!
   * \brief Clears the textures of a cube
   * \param[in] cube name
   */
  static void clearTexturesOfCube( Ogre::String baseName );

  /*!
   * \brief Gets the textures to a selected cube
   * \param[in] cube name
   * \return the textures
   */
  static std::map<std::string, std::string> getTexturesFromCube(Ogre::String baseName);

  /*!
   * \brief Creates a cube with the given name
   * \param[in] cube name
   */
  static void createCubeByFaces(Ogre::String name, Ogre::uint32 mask, float x=0, float y=0, float z=0, float w=1, float h=1, float zSize = 1);

  /*!
   * \brief Creates a cube with the given name
   * \param[in] cube name
   */
  static void createCubeByFaces(Ogre::String name, float ambientColor[3], Ogre::uint32 mask, float x=0, float y=0, float z=0, float w=1, float h=1, float zSize = 1);

  /*!
   * \brief Creates a cube with the given name
   * \param[in] cube name
   */
  static void createDoorEntity( Ogre::String name, float ambientColor[3], float sizex, float sizey, float sizez);

  /*!
   * \brief Creates a cube Mesh
   * \param[in] cube name
   */
  static void createCubeMesh(std::string a_name, std::map<std::string, std::string> a_textures, int rgb[3]);

  /*!
   * \brief Deletes a cube mesh
   * \param[in] cube name
   */
  static void deleteCubeMesh(std::string a_name);

  /*!
   * \brief Attach a cube by faces
   * \param[in] cube name
   */
  static void attachCubeFaces( std::string a_name );
};

#endif // CubeUtils_H
