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

#ifndef QOMGMAPDIALOG_H
#define QOMGMAPDIALOG_H

#include "OmgEntities/OmgMap.h"
#include "InputData.h"

namespace Ui {
class QOmgMapDialog;
}

class QListWidgetItem;

class QOmgMapDialog : public InputData
{
    Q_OBJECT

public:
    explicit QOmgMapDialog(QWidget *parent = 0);
    explicit QOmgMapDialog(OmgMap* apMap, QWidget *parent = 0);
    ~QOmgMapDialog();

private slots:
    void on_pbCreate_clicked();

    void on_basePlaneTexture_clicked();

    void on_pbClear_clicked();

    void on_pbLoad_clicked();

    void on_pbremove_clicked();

private:
    Ui::QOmgMapDialog *ui;

    /*!
     * \brief Validates the input data
     */
    bool validate( void );

    /*!
     * \brief Sets the map in the windows
     * \param apMap, the map to set in the window
     */
    void setMapInQt( OmgMap* apMap );

    /*!
    * \brief findFolderObjectsByName
    * \param aName
    * \return
    */
    QListWidgetItem* findFolderMapsByName( QString aName );
    
    /*!
     * \brief Fills the input data when it is shown
     */
    void fillInputData( void );

    /*!
     * \brief Creates a new map with the configured input data
     * \return OmgMap, the new map created
     */
    OmgMap* createMap( void );

    /*!
     * \brief Stores the map and finish the command
     * \param apNewMap
     */
    void storeAndFinish( OmgMap* apNewMap );

    /*!
     * \brief The texture name of the base plane
     */
    QString terrainTextureName;

    /*!
     * \brief The map to edit
     */
    OmgMap* _map;
};

#endif // QOMGMAPDIALOG_H
