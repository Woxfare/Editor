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

#ifndef OMGPLAYERCONTAINER_H
#define OMGPLAYERCONTAINER_H

class OmgPlayer;

#include "Omega.h"

class OmgPlayerContainer
{
public:
    /*!
     * \brief Instance
     * \return
     */
    static OmgPlayerContainer* Instance( void );

    /*!
     * \brief GetPlayer
     * \param a_name
     * \return
     */
    OmgPlayer* getPlayer( QString aName );

    /*!
     * \brief addPlayer
     * \param aPlayer
     * \return
     */
    bool addPlayer( OmgPlayer* aPlayer );

    /*!
     * \brief deltePlayer
     * \param aName
     * \return
     */
    void deletePlayer( QString aName );

    /*!
     * \brief availablePlayers
     * \return
     */
    Omega::EntityVector availablePlayers( void );

    /*!
     * \brief availablePlayersItems
     * \return
     */
    Omega::ListItemVector availablePlayerItems( void );

    /*!
     * \brief playersInFolder
     * \param aFolderName
     * \return
     */
    Omega::EntityVector playersInFolder( QString aFolderName );

    void buildPlayer( QStringList playerParams );

protected:
    //- OmgPlayerContainer
    //? Default Constructor
    OmgPlayerContainer();

    std::map<std::string, std::string> getPartTextures( int beginIndex, QStringList playerParams );

private:

    //? The map of the class
    Omega::PlayersMap _map_players;

    //? The instance of the class
    static OmgPlayerContainer* _p_instance;
};

#endif // OMGPLAYERCONTAINER_H
