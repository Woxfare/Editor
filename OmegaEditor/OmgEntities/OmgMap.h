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

#ifndef OMGMAP_H
#define OMGMAP_H

#include "OmgEntity.h"

class QXmlStreamWriter;

class OmgMap : public OmgEntity
{
public:

    /*!
     * \brief OmgMap Default Constructor
     * \param a_name
     * \param a_folder
     */
    OmgMap( QString aName, QString aFolderName );

    /*!
     * \brief Sets the terrain texture name
     * \param terrainTextureName
     */
    void setTerrainTextureName( QString terrainTextureName );

    /*!
     * \brief Gets the terrain texture name
     * \return terrainTextureName
     */
    QString getTerrainTextureName( void );

    /*!
     * \brief Gets the terrain texture name
     * \return terrainTextureName
     */
    std::vector< std::pair < std::string, std::vector< Ogre::Vector3 > > > 
        getSceneObjectsInTheMap( void );

    /*!
    * \brief Gets the terrain texture name
    * \return terrainTextureName
    */
    void setSceneObjectsToTheMap( std::vector< std::pair < std::string, std::vector< Ogre::Vector3 > > > sceneObjectsToSet );

   /*!
    * \brief Gets the terrain texture name
    * \return terrainTextureName
    */
    Ogre::MeshPtr getMeshScenary( void );

   /*!
    * \brief Gets the terrain texture name
    * \return terrainTextureName
    */
    void setMeshScenary( Ogre::MeshPtr meshScenary );

    /*!
    * \brief Calculates the Scenary with the current values
    */
    void CalculateScenary( void );

   /*!
    * \brief gets the Dynamic Objects of the scenary
    */
    std::vector< std::pair < std::string, std::vector< Ogre::Vector3 > > > getDynamicObjects( void );

   /*!
    * \brief sets the Dynamic Objects of the scenary
    */
    void setDynamicObjects( std::vector< std::pair < std::string, std::vector< Ogre::Vector3 > > >  dynamicObjects );

    /*!
     * \brief writeInfo
     * \param[in] QXmlStreamWriter a_xml_stream
     */
    virtual void writeInfo( QXmlStreamWriter *a_xml_stream );

	/*!
     * \brief writeInfo
     * \param[in] QXmlStreamWriter a_xml_stream
     */
    void setEnemyDoors( std::vector< Ogre::Vector3 > aDoors );
	
	/*!
     * \brief Gets a vector of positions of enemies
     */
    std::vector< Ogre::Vector3 > getEnemyDoors(  void );

	/*!
     * \brief Optimizes the materials of the scenary
     */
	std::string optimizeMaterial(std::string materialName);

	/*!
     * \brief Obtains the materials to export
     */
	std::vector<std::string> getMaterialsToExport();

	/*!
     * \brief Gets the player initial position
     */
	Ogre::Vector3 getPlayerDoor( void );

	/*!
     * \brief Sets the player initial position
     */
	void setPlayerDoor( Ogre::Vector3 pos );

private:

  /*!
  * \brief The terrain texture name
  */
  QString _terrainTextureName;
  std::vector< std::pair < std::string, std::vector< Ogre::Vector3 > > > _sceneObjects;
  std::vector< Ogre::Vector3 > _doors;
  Ogre::Vector3 playerPos;

  /*
   *\brief Woxfare Stuff
   */
  Ogre::MeshPtr _scenaryMesh;
  std::vector< std::string > _materialsToExport;
  std::vector< std::pair < std::string, std::vector< Ogre::Vector3 > > > _dynamicSceneObjects;

  /*!
  * \brief optimize the scenary in 1 mesh
  */
  Ogre::MeshPtr getEditScenaryOptimized( std::vector< std::pair < std::string, std::vector< Ogre::Vector3 > > >& dynamicObjVector );

  /*!
  * \brief add the faces to the scenary optimized Mesh
  */
  void addFacesToScenaryOptimized(Ogre::ManualObject * scenary, Ogre::Vector3 position, std::string materialBaseName, std::map<std::string, bool> facesToDraw);

};

#endif // OMGMAP_H
