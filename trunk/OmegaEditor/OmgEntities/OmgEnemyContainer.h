/* ==================== Copyright (c) 2013 OMEGA Team ====================
//    ___  __  __ ______  ____  ___
//   / _ \|  \/  |  ____|/ ___|/ _ \
//  | | | |      | |__  | |   | | | |
//  | | | | |\/| |  __| | |  _| |_| |
//  | |_| | |  | | |____| |_| |  _  |
//   \___/|_|  |_|______|\____|_| |_|
//
// Members:
// Fernando Perera ( datiner )
// Alejandro Vazquez ( Vazquinhos )
// ==================== Copyright (c) 2013 OMEGA Team ====================
// Description:
// This class implements the container of enemies and their management
// =====================================================================*/

#ifndef OMGENEMYCONTAINTER_H
#define OMGENEMYCONTAINTER_H

#include "OmgEnemy.h"
#include <QString>
#include <map>
#include <vector>
class OmgEnemyContainer
{
public:

    /*!
     * \brief Instance
     * \return  OmgEnemyContainer
     */
    static OmgEnemyContainer* Instance( void );

    /*!
     * \brief getEnemy
     * \param a_name
     * \return
     */
    OmgEnemy* getEnemy( QString aName );

    /*!
     * \brief addEnemy
     * \param a_enemy
     * \return
     */
    bool addEnemy(OmgEnemy* apEnemy );

    /*!
     * \brief deleteEnemy
     * \param aName
     * \return
     */
    bool deleteEnemy(QString aName );

    /*!
     * \brief availableEnemies
     * \return
     */
    Omega::EntityVector availableEnemies( void );

    /*!
     * \brief availableItemsEnemies
     * \return Vector with the widgets
     */
    Omega::ListItemVector availableItemsEnemies( void );


    /*!
     * \brief enemiesInFolder
     * \param aFolderName
     * \return
     */
    Omega::EntityVector enemiesInFolder( QString aFolderName );

    /*!
     * \brief Default Destructor
     */
    ~OmgEnemyContainer();

    /*!
     * \brief buildEnemy
     * \param aEnemyParams
     */
    void buildEnemy( QStringList aEnemyParams );

    std::map<std::string, std::string> getPartTextures( int beginIndex, QStringList enemyParams );

protected:
    /*!
     * \brief OmgEnemyContainer
     */
    OmgEnemyContainer();

private:

    /*!
     * \brief _map_enemies
     */
    std::map<QString,OmgEnemy*> _map_enemies;

    /*!
     * \brief _p_instance
     */
    static OmgEnemyContainer* _p_instance;
};

#endif // OMGENEMYCONTAINTER_H
