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
// Omega Namespace
// ======================================================================*/
#ifndef OMEGA_H
#define OMEGA_H

class OmgSceneObj;
class OmgEntity;
class OmgPlayer;
class OmgItem;
class OmgEnemy;
class QOmgListItem;
class OmgFolder;
class OmgWeapon;

#include <vector>
#include <map>
#include <stdio.h>
#include <QString>

namespace Omega{

	//!-------------------------------------------------------------------------
	//! TYPEDEF DECLARATIONS
	//!-------------------------------------------------------------------------
	/*!
	 * \brief EntityType
	 */
    typedef enum{
        Entity,
        Player,
        Enemy,
        Item,
        SceneObj,
        Weapon,
        Map,
        BuildUpObj,
        Game
    } EntityType;

    /*!
     * \brief FolderType
     */
    typedef enum{
        EntityFolder,
        PlayerFolder,
        EnemyFolder,
        ItemFolder,
        SceneObjFolder,
        WeaponFolder,
        MapFolder,
        GameFolder,
        BuildUpObjFolder
    } FolderType;

    /*!
     * \brief LeafType
     */
    typedef enum{
        FolderLeaf,
        PlayerLeaf,
        EnemyLeaf,
        ItemLeaf,
        SceneObjLeaf,
        WeaponLeaf,
        MapLeaf,
        GameLeaf,
        BuildUpObjLeaf

    } LeafType;

    /*!
     * \brief EnemyType
     */
    typedef enum{
        Runner,
        Gunner,
        JuniorBoss,
        BigBoss
    } EnemyType;


    /*!
     * \brief ItemType
     */
    typedef enum{
        Health,
        Gold,
        Ammo
    } ItemType;

    /*!
     * \brief SceneObjType
     */
    typedef enum{
        Dynamic,
        Static
    } SceneObjType;

    /*!
     * \brief WeaponType
     */
    typedef enum{
        SimpleShot,
        BlastShot,
        MultiShot
    } WeaponType;

    //!-------------------------------------------------------------------------
    //! ENTITIES
    //!-------------------------------------------------------------------------
    /*!
     * \brief EntityVector
     */
    typedef std::vector<OmgEntity*> EntityVector;

    /*!
     * \brief EntityIterator
     */
    typedef std::vector<OmgEntity*>::iterator EntityIterator;

    /*!
     * \brief EntityConstIterator
     */
    typedef std::vector<OmgEntity*>::const_iterator EntityConstIterator;

    //!-------------------------------------------------------------------------
    //! SCENE OBJECTS
    //!-------------------------------------------------------------------------
    /*!
     * \brief SceneObjVector
     */
    typedef std::vector<OmgSceneObj*> SceneObjVector;

    /*!
     * \brief SceneObjIterator
     */
    typedef std::vector<OmgSceneObj*>::iterator SceneObjIterator;

    //!-------------------------------------------------------------------------
    //! PLAYERS
    //!-------------------------------------------------------------------------
    /*!
     * \brief PlayersVector
     */
    typedef std::vector< OmgPlayer* > PlayersVector;

    /*!
     * \brief PlayersIterator
     */
    typedef std::vector< OmgPlayer* >::iterator PlayersIterator;

    /*!
     * \brief PlayersMap
     */
    typedef std::map< QString, OmgPlayer* > PlayersMap;

    /*!
     * \brief PlayersMapIterator
     */
    typedef std::map< QString, OmgPlayer* >::iterator PlayersMapIterator;

    //!-------------------------------------------------------------------------
    //! WEAPONS
    //!-------------------------------------------------------------------------
    /*!
     * \brief WeaponsVector
     */
    typedef std::vector< OmgWeapon* > WeaponsVector;

    /*!
     * \brief WeaponsIterator
     */
    typedef std::vector< OmgWeapon* >::iterator WeaponsIterator;

    /*!
     * \brief WeaponsMap
     */
    typedef std::map< QString, OmgWeapon* > WeaponsMap;

    /*!
     * \brief WeaponsMapIterator
     */
    typedef std::map< QString, OmgWeapon* >::iterator WeaponsMapIterator;

    //!-------------------------------------------------------------------------
    //! ENEMIES
    //!-------------------------------------------------------------------------
    /*!
     * \brief EnemiesVector
     */
    typedef std::vector< OmgEnemy* > EnemiesVector;

    /*!
     * \brief EnemiesIterator
     */
    typedef std::vector< OmgEnemy* >::iterator EnemiesIterator;

    //!-------------------------------------------------------------------------
    //! ITEMS
    //!-------------------------------------------------------------------------
    /*!
     * \brief ItemsVector
     */
    typedef std::vector< OmgItem* > ItemsVector;

    /*!
     * \brief EnemiesIterator
     */
    typedef std::vector< OmgItem* >::iterator ItemsIterator;

    //!-------------------------------------------------------------------------
    //! FOLDERS
    //!-------------------------------------------------------------------------
    /*!
     * \brief FolderPack
     */
    typedef std::vector< std::pair< QString, EntityVector> > FolderPack;

    /*!
     * \brief FolderVector
     */
    typedef std::vector<OmgFolder*> FolderVector;

    /*!
     * \brief FolderIterator
     */
    typedef std::vector<OmgFolder*>::iterator FolderIterator;

    //!-------------------------------------------------------------------------
    //! QT COMPONENTS
    //!-------------------------------------------------------------------------
    /*!
     * \brief ListItemVector
     */
    typedef std::vector<QOmgListItem*> ListItemVector;
    /*!
     * \brief ListItemIterator
     */
    typedef std::vector<QOmgListItem*>::iterator ListItemIterator;
}

#endif // OMEGA_H
