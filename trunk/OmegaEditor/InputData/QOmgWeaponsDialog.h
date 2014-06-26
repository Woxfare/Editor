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

#ifndef QOMGWEAPONSDIALOG_H
#define QOMGWEAPONSDIALOG_H

#include <QDialog>

class OmgWeapon;
class QListWidgetItem;

#include "Omega.h"


namespace Ui {
class QOmgWeaponsDialog;
}

class QOmgWeaponsDialog : public QDialog
{
    Q_OBJECT

public:
    /*!
     * \brief QOmgWeaponsDialog
     * \param parent
     */
    explicit QOmgWeaponsDialog(QWidget *parent = 0);

    /*!
     * \brief QOmgWeaponsDialog
     * \param aWeapon
     * \param parent
     */
    explicit QOmgWeaponsDialog( OmgWeapon * aWeapon, QWidget *parent = 0);

    ~QOmgWeaponsDialog();

private:
    /*!
     * \brief ui
     */
    Ui::QOmgWeaponsDialog *ui;

    /*!
     * \brief _weapon
     */
    OmgWeapon* _weapon;

    /*!
     * \brief _folder
     */
    QString _folder;

    /*!
     * \brief editingTextures
     */
    bool editingTextures;

    /*!
     * \brief Configures the input data with the given weapon
     */
    void putWeaponInQt( void );

    /*!
     * \brief Validates the data of the input data
     * \return true if all the data is correct
     */
    bool validate();

    /*!
     * \brief Gets the weapon type from the window
     * \return
     */
    Omega::WeaponType getWeaponTypeFromQt( void );

    /*!
     * \brief Finds the folder in the list
     * \param aName The folder name
     * \return
     */
    QListWidgetItem* findFolderItemByName(QString aName);

    /*!
     * \brief Stores the weapon in the container and hides the input data
     * \param aWeapon
     */
    void storeAndFinnish( OmgWeapon * aWeapon );

    /*!
     * \brief Creates a weapon with the options in the input data
     */
    OmgWeapon *createWeapon( void );


signals:
    /*!
     * \brief Signal emited to hide the input data
     */
    void hideInputData( void );

private slots:

    /*!
     * \brief Slot called when the user clicks new weapon button
     */
    void on__newWeapon_clicked();

    /*!
     * \brief Slot called when the user clicks edit weapon button
     */
    void on__editWeapon_clicked();
};

#endif // QOMGWEAPONSDIALOG_H
