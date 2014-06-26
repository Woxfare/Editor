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

#ifndef EditSceneManager_H
#define EditSceneManager_H

#include <Ogre.h>

class EditSceneManager
{
public:

  ~EditSceneManager();
  /*!
    * \brief Gets an instance to the manager
    * \return
    */
  static EditSceneManager * getInstance();

  void createBasePlane(float width, float depth, float y=0);

  /*!
    * \brief Changes the color of the base plane
    * \param A vector with the values RGB
    */
  void changeBasePlaneColor( int rgb[3] );

  /*!
    * \brief Changes the texture material of the base plane
    */
  void changeBasePlaneTexture( std::string textureName );

  /*!
    * \brief Gets the number of cubes in the Scene of the same cube
    * \return
    */
  int getNumberOfCubesInTheScene( void );

  /*!
    * \brief Deletes a cube from the Scene
    * \param cubeName
    */
  void  deleteCubeFromScene( std::string cubeName );

  /*!
  * \brief Deletes a cube from the Scene
  * \param cubeName
  */
  void  deleteDoorFromScene( std::string doorName, bool isPlayerDoor = false );

  /*!
    * \brief Adds a new cube into the Scene
    * \param cubeName, The base name of the cube
    * \param position, The position to draw the cube
    */
  void  addCubeToScene(std::string cubeName, Ogre::Vector3 position);

  /*!
  * \brief Adds a new door into the Scene
  * \param position, The position to draw the door
  */
  void  addDoorToScene( Ogre::Vector3 position, bool isPlayerDoor = false );

  /*!
    * \brief Clears the Scenery
    */
  void clearScenary( void );

  /*!
    * \brief Gets the current edited scene
    */
  std::vector< std::pair < std::string, std::vector< Ogre::Vector3 > > > getEditScenary( void );

  /*!
    * \brief setEditScenary
    * \param mapSceneCubes
    * \param mapSceneCubesPositions
    */
  void setEditScenary( std::vector< std::pair < std::string, std::vector< Ogre::Vector3 > > > sceneToSet );

  /*!
  * \brief Changes the name of the objects in the scene
  */
  void changeNodesInfo( std::string oldBaseName, std::string newBaseName );

 /*!
  * \brief Creates the group of entities 
  */
  void createEntityGroup( std::string baseName );

 /*!
  * \brief Delete the group of entities 
  */
  void deleteEntityGroup( std::string baseName );

  /*!
  * \brief Removes the base plain texture
  */
  void removeBasePlaneTexture( void );

  /*!
  * \brief initialize the mesh used in the EnemyDoors
  */
  void initializeEnemyDoorsMesh(Ogre::Vector3 position, float sizex=1, float sizey=2, float sizez=1);

  /*!
  * \brief initialize the mesh used in the EnemyDoors
  */
  std::vector<Ogre::Vector3> getEnemiesDoors( void );

 /*!
  * \brief initialize the mesh used in the EnemyDoors
  */
  void setEnemyDoors( std::vector< Ogre::Vector3 > doors );

  /*!
  * \brief initialize the mesh used in the EnemyDoors
  */
  Ogre::Vector3 getPlayerDoor( void );

private:

  /*!
    * \brief EditSceneManager Constructor
    */
  EditSceneManager();

  /*!
    * \brief _p_instance
    */
  static EditSceneManager  * _p_instance;

  /*!
  * \brief Creates the scenery to edit
  */
  void createEditScenary();

  /*! 
  * \brief Stuff that stores all the information need it for the scenery
  */
  std::map<std::string, std::vector<std::string> >_cubes;
  std::map<std::string, Ogre::Vector3> _positions;
  std::map<std::string, int >  _indexes;
  int  _doors_indexes;
  std::map<std::string, Ogre::Vector3> _doors_positions;
  bool playerDoorInit;
  Ogre::Vector3 playerDoorPos;

};

#endif // EditSceneManager_H
