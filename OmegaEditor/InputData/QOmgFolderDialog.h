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

#ifndef QOMGFOLDERDIALOG_H
#define QOMGFOLDERDIALOG_H

#include <QDialog>
#include "Omega.h"
#include "Folders/OmgFoldersMngr.h"
#include "OmgEntities/OmgEntity.h"
#include <vector>

namespace Ui {
class QOmgFolderDialog;
}

class QOmgFolderDialog : public QDialog
{
    Q_OBJECT

public:

    /*!
     * \brief QOmgFolderDialog
     * \param aFolder
     * \param aParent
     */
    explicit QOmgFolderDialog(OmgFolder *aFolder, QWidget *aParent = 0);

    /*!
     * \brief QOmgFolderDialog
     * \param aParent
     */
    explicit QOmgFolderDialog(QWidget *aParent = 0 );

    ~QOmgFolderDialog();

private slots:

    /*!
     * \brief on_pbNew_clicked
     */
    void on_pbNew_clicked();

    /*!
     * \brief on_pbEdit_clicked
     */
    void on_pbEdit_clicked();

    void on_pbCancel_clicked();

signals:

    /*!
     * \brief HideInputData
     */
    void HideInputData( void );
    
private:

    /*!
     * \brief ui
     */
    Ui::QOmgFolderDialog *ui;

    /*!
     * \brief mFolder
     */
    OmgFolder* mFolder;

    /*!
     * \brief GetFolderType
     * \return
     */
    Omega::FolderType getFolderType( void );

    /*!
     * \brief CreateWidget
     */
    void createWidget();

    /*!
     * \brief ValidateData
     * \return
     */
    bool validate( void );

    /*!
     * \brief UpdateEntitiesInFolder
     * \param aFolder
     */
    void updateEntitiesInFolder( OmgFolder* aFolder );

    /*!
     * \brief ChangeFolder
     * \param defName
     * \param vEntities
     */
    void changeFolder( QString name, Omega::EntityVector vEntities );
};

#endif // QOMGFOLDERDIALOG_H
