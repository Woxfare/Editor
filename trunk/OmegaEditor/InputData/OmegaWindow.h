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

#ifndef OMEGAWINDOW_H
#define OMEGAWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include "./Folders/OmgFolder.h"
#include "InputData/QOmgDragableEntities.h"

class OgreWidget;

class OmgEnemy;
class OmgPlayer;
class OmgEntity;
class OmgItem;
class QtOgreWidget;
class OmgSceneObj;
class OmgWeapon;
class OmgMap;
class OmgGame;

namespace Ui {
class OmegaWindow;
}

class OmegaWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    /*!
     * \brief OmegaWindow
     * \param parent
     */
    explicit OmegaWindow(QWidget *parent = 0);
    ~OmegaWindow();

    /*!
     * \brief closeEvent
     * \param event
     */
    virtual void closeEvent ( QCloseEvent * event );

    virtual void showEvent(QShowEvent * event );

    void deselectCurrentObj( void );

    void showCharacterPartsSelector( void );

    void hideCharacterPartsSelector( void );

    void showEditScenearyWidget( void );

    void hideEditScenearyWidget( void );
    
public Q_SLOTS:

    /*!
     * \brief on_actionNew_Player_triggered
     */
    void on_actionNew_Player_triggered();

    /*!
     * \brief on_actionNew_Enemy_triggered
     */
    void on_actionNew_Enemy_triggered();

    /*!
     * \brief on_actionEdit_Player_triggered
     * \param ap_player
     */
    void on_actionEdit_Player_triggered(OmgPlayer* ap_player);

    /*!
     * \brief on_actionEdit_Enemy_triggered
     * \param ap_player
     */
    void on_actionEdit_Enemy_triggered(OmgEnemy* ap_player);

    /*!
     * \brief on_actionNew_Folder_triggered
     */
    void on_actionNew_Folder_triggered();

    /*!
     * \brief on_actionEdit_Folder_triggered
     * \param ap_folder
     */
    void on_actionEdit_Folder_triggered(OmgFolder* ap_folder );

    /*!
     * \brief New Map Slot
     */
    void on_actionNew_Map_triggered();

    /*!
     * \brief New Game Slot
     */
    void on_actionNewGame_triggered();

    /*!
     * \brief Edit Map Slot
     */
    void on_actionEdit_Map_triggered( OmgMap* apMap );

    /*!
     * \brief Edit Game Slot
     */
    void on_actionEditGame_triggered( OmgGame* apGame );

    /*!
     * \brief on__preview_entities_clicked
     */
    void on__preview_entities_clicked();

    /*!
     * \brief on__p_tree_entities_clicked
     */
    void on__p_tree_entities_clicked();

    /*!
     * \brief hideWidgetArea
     */
    void hideWidgetArea( void );

    /*!
     * \brief hideWidgetArea
     */
    void hideBigWidgetArea( void );

    /*!
     * \brief UpdateWidgets
     * \param p_entity
     */
    void UpdateWidgets( OmgEntity* p_entity );

    /*!
     * \brief UpdateWidgets
     */
    void UpdateWidgets( );

    /*!
     * \brief on_treeWidget_itemClicked
     * \param item
     * \param column
     */
    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

    /*!
     * \brief on_actionNew_Item_triggered
     */
    void on_actionNew_Item_triggered();

    /*!
     * \brief on_actionNew_Scene_Object_triggered
     */
    void on_actionNew_Scene_Object_triggered();

    /*!
     * \brief on_actionEdit_Item_triggered
     * \param aItem
     */
    void on_actionEdit_Item_triggered( OmgItem* aItem );

    /*!
     * \brief on_actionEdit_Scene_Object_triggered
     * \param apObject
     */
    void on_actionEdit_Scene_Object_triggered( OmgSceneObj* apObject );

    /*!
     * \brief on_actionExport_To_Omg_triggered
     */
    void on_actionExport_To_Omg_triggered(void);

    /*!
     * \brief on_actionNew_Weapon_triggered
     */
    void on_actionNew_Weapon_triggered();

    void on_actionEdit_Weapon_triggered( OmgWeapon* aWeapon );

    /*!
     * \brief on_actionExit_triggered
     */
    void on_actionExit_triggered();

    /*!
     * \brief on_actionSave_triggered
     */
    void on_actionSave_triggered();

    void timerLoop();

private:
    /*!
     * \brief ui
     */
    Ui::OmegaWindow *ui;

    OgreWidget* mOgreWidget;

    QTimer                          *mTimer;
};

#endif // OMEGAWINDOW_H
