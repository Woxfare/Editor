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

#ifndef OmgGameContainer_H
#define OmgGameContainer_H

class OmgGame;

#include "Omega.h"

class OmgGameContainer
{
public:
    /*!
     * \brief Instance
     * \return
     */
    static OmgGameContainer* Instance( void );

    /*!
     * \brief getgame
     * \param aName
     * \return
     */
    OmgGame *getGame( QString aName );

    /*!
     * \brief addgame
     * \param agame
     */
    void addGame( OmgGame* aGame );

    /*!
     * \brief deletePlayer
     * \param aName
     */
    void deleteGame( QString aName );

    /*!
     * \brief availablegames
     * \return
     */
    Omega::EntityVector availableGames( void );

    /*!
     * \brief gamesInFolder
     * \param aFolderName
     * \return
     */
    Omega::EntityVector gamesInFolder( QString aFolderName );

protected:
    /*!
     * \brief OmgGameContainer
     */
    OmgGameContainer();

private:

    /*!
     * \brief _game_games
     */
    std::map<QString,OmgGame*> _map_games;

    /*!
     * \brief _p_instance
     */
    static OmgGameContainer* _p_instance;
};

#endif // OmgGameContainer_H
