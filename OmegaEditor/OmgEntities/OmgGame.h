/*
				 ___  __  __ ______  ____  ___
				/ _ \|  \/  |  ____|/ ___|/ _ \
	 		   | | | |      | |__  | |   | | | |
               | | | | |\/| |  __| | |  _| |_| |
               | |_| | |  | | |____| |_| |  _  |
                \___/|_|  |_|______|\____|_| |_|

	Copyright (c) 2014 Fernando Perera & Alejandro V�zquez

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
#ifndef OMGGAME_H
#define OMGGAME_H

#include "OmgEntity.h"
#include "OmgMap.h"
#include "OmgPlayer.h"

class QXmlStreamWriter;

class OmgGame : public OmgEntity
{
public:
    /*!
     * \brief OmgGame Default Constructor
     * \param a_name
     * \param a_folder
     */
    OmgGame(QString aName, QString aFolderName );

    /*!
     * \brief Sets the number of rounds
     * \param nRounds
     */
    void setNumberOfRounds( int nRounds );

    /*!
     * \brief Gets the number of rounds
     * \return
     */
    int getNumberOfRounds(void);

    /*!
     * \brief setMinEnemies
     * \param minEnemies
     */
    void setMinEnemies( int minEnemies );

    /*!
     * \brief getMinEnemies
     * \return
     */
    int getMinEnemies(void);

    /*!
     * \brief setMaxEnemies
     * \param maxEnemies
     */
    void setMaxEnemies( int maxEnemies );

    /*!
     * \brief getMaxEnemies
     * \return
     */
    int getMaxEnemies(void);

    /*!
     * \brief setEnemyIncrement
     * \param increment
     */
    void setEnemyIncrement( float increment );

    /*!
     * \brief getEnemyIncrement
     * \return
     */
    float getEnemyIncrement(void);

    /*!
     * \brief setNumberOfBosses
     * \param nBosses
     */
    void setNumberOfBosses( int nBosses );

    /*!
     * \brief getNumberOfBosses
     * \return
     */
    int getNumberOfBosses(void);

    /*!
     * \brief setIntervalBosses
     * \param interval
     */
    void setIntervalBosses( int interval );

    /*!
     * \brief getIntervalBosses
     * \return
     */
    int getIntervalBosses(void);


    /*!
     * \brief getAvailableEnemies
     * \return
     */
    Omega::EntityVector getAvailableEnemies( void );

    /*!
     * \brief getAvailableItems
     * \return
     */
    Omega::EntityVector getAvailableItems( void );

    
    /*!
     * \brief setAvailableEnemies
     */
    void setAvailableEnemies( Omega::EntityVector vEnemies );

    /*!
     * \brief setAvailableItems
     */
    void setAvailableItems( Omega::EntityVector vItems );

    /*!
     * \brief getMap
     * \return
     */
    OmgMap* getMap( void );

    /*!
     * \brief getPlayer
     * \return
     */
    OmgPlayer* getPlayer( void );

    /*!
     * \brief setMap
     */
    void setMap( OmgMap* apMap );

    /*!
     * \brief setPlayer
     */
    void setPlayer( OmgPlayer* apPlayer );

    /*
     * \brief Saves the game to be loaded in the Woxfare game
     */
    void SaveGameInFile( void );

     /*!
     * \brief writeInfo
     * \param[in] QXmlStreamWriter a_xml_stream
     */
    virtual void writeInfo( QXmlStreamWriter *a_xml_stream );

private:

    /*!
     * \brief _nRounds
     */
    int _nRounds;

    /*!
     * \brief _minEnemies
     */
    int _minEnemies;

    /*!
     * \brief _maxEnemies
     */
    int _maxEnemies;

    /*!
     * \brief _enemyIncrement
     */
    float _enemyIncrement;

    /*!
     * \brief _nBosses
     */
    int _nBosses;

    /*!
     * \brief _intervalBosses
     */
    int _intervalBosses;

    /*!
     * \brief _vEnemies
     */
    Omega::EntityVector _vEnemies;

    /*!
     * \brief _vItems
     */
    Omega::EntityVector _vItems;

    /*!
     * \brief _scenary
     */
    OmgMap* _scenary;

    /*!
     * \brief _player
     */
    OmgPlayer* _player;

    /*
     * \brief Gets a set of pixmaps
     */
    void saveConfigurationFile( QString fileName,  std::set< std::string > textures );

    /*
     * \brief Gets a set of pixmaps
     */
    std::set< std::string > getPixmapSet( );

	 /*
     * \brief Gets a 
     */
    std::set< QString > getWeaponsSet( );

    /*
     * \brief Creates the pixmaps set
     */
    void savePixmaps( std::set< std::string > pixmapSet, QString path );

    void writeWeapons( QXmlStreamWriter *a_xml_stream );

};

#endif // OMGGAME_H
