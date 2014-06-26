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

#ifndef QOMGITEMDIALOG_H
#define QOMGITEMDIALOG_H

#include <QDialog>

#include "Omega.h"
#include "InputData.h"

class OmgItem;
class QListWidgetItem;
class QString;

namespace Ui {
class QOmgItemDialog;
}

class QOmgItemDialog : public InputData
{
    Q_OBJECT

public:
    /*!
     * \brief QOmgItemDialog
     * \param apItem
     * \param parent
     */
    explicit QOmgItemDialog( OmgItem* apItem = 0, QWidget *parent = 0);

    ~QOmgItemDialog();

private slots:

    /*!
     * \brief on_cbItemType_currentIndexChanged
     * \param arg1
     */
    void on_cbItemType_currentIndexChanged(const QString &arg1);

    /*!
     * \brief on__newItem_clicked
     */
    void on__newItem_clicked();

    /*!
     * \brief on__editItem_clicked
     */
    void on__editItem_clicked();

    /*!
     * \brief on__cancel_clicked
     */
    void on__cancel_clicked();

    /*!
     * \brief on__pb_textures_clicked
     */
    void on__pb_textures_clicked();

    void on_deleteTextures_clicked();

    void on_texturesEqual_clicked();

private:
    /*!
     * \brief ui
     */
    Ui::QOmgItemDialog *ui;

    /*!
     * \brief _item
     */
    OmgItem* _item;

    /*!
     * \brief _folder
     */
    QString _folder;

    /*!
     * \brief _color
     */
    QColor _color;

    /*!
     * \brief hideAndShowWidgets
     * \param aItemType
     */
    void hideAndShowWidgets( QString aItemType );

    /*!
     * \brief putItemInQt
     */
    void putItemInQt( );

    /*!
     * \brief getItemTypeFromQt
     * \return
     */
    Omega::ItemType getItemTypeFromQt( void );

    /*!
     * \brief validate
     * \return
     */
    bool validate( void );

    /*!
     * \brief createSceneObject
     * \return
     */
    OmgItem* createItem( void );

    /*!
     * \brief storeAndFinnish
     * \param aObject
     */
    void storeAndFinnish( OmgItem* aObject );
};

#endif // QOMGITEMDIALOG_H
