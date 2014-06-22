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

#ifndef EditCharacterManager_H
#define EditCharacterManager_H

#include <Ogre.h>

// Enum that describes the part of the body of the character
enum  characterParts{ head, body, armLeft, armRight, legLeft, legRight };

class EditCharacterManager
{
public:

  ~EditCharacterManager();
  /*!
   * \brief Gets an instance to the manager
   * \return
   */
  static EditCharacterManager * getInstance();

  /*!
   * \brief Clears the character
   */
  void clearCharacter( void );

  /*!
  * \brief Gets the character part
	* \param[in] The part to get
	* \return the textures and the face of each texture
  */
  std::map<std::string, std::string> getCharacterPart( characterParts aPartToGet );

 /*!
  * \brief Gets the character part
	* \param[in] The part to get
	* \return the textures and the face of each texture
  */
  void setPartsToShow( std::vector< characterParts > partsToShow );

 /*!
  * \brief Gets the character part
	* \param[in] The part to get
	* \return the textures and the face of each texture
   */
  void setCharacterPart( characterParts aPart, std::map<std::string, std::string> textures );

  /*!
  * \brief Gets whole edited character in the scene
	* \return the character edited
  */
  std::map<std::string, std::map<std::string, std::string>> getEditCharacter( void );
  
  /*!
  * \brief Sets whole edited character in the scene
	* \param[in] the character textures
  */
  void setEditCharacter( std::map<std::string, std::map<std::string, std::string>> textures );

  void changeCharacterColor( int rgb[3] );

private:

  /*!
    * \brief EditCharacterManager Constructor
    */
  EditCharacterManager();

  /*!
    * \brief _p_instance
    */
  static EditCharacterManager  * _p_instance;

  /*!
  * \brief Creates the character to edit
  */
  void createEditCharacter();
};

#endif // EditCharacterManager_H
