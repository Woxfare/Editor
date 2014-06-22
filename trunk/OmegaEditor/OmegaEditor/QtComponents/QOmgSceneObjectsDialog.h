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

#ifndef QOMGSCENEOBJECTSDIALOG_H
#define QOMGSCENEOBJECTSDIALOG_H

#include <QDialog>

class OmgSceneObj;
class QListWidgetItem;
namespace Ui {
class QOmgSceneObjectsDialog;
}

class QOmgSceneObjectsDialog : public QDialog
{
    Q_OBJECT

public:
    /*!
     * \brief QOmgSceneObjectsDialog
     * \param parent
     */
    explicit QOmgSceneObjectsDialog(QWidget *parent = 0);

    /*!
     * \brief QOmgSceneObjectsDialog
     * \param aObject
     * \param parent
     */
    explicit QOmgSceneObjectsDialog(OmgSceneObj *aObject, QWidget *parent = 0);
    ~QOmgSceneObjectsDialog();

private:
    /*!
     * \brief ui
     */
    Ui::QOmgSceneObjectsDialog *ui;

    /*!
     * \brief editingTextures
     */
    bool editingTextures;

    /*!
     * \brief putSceneObjectInQt
     */
    void putSceneObjectInQt( void );

    /*!
     * \brief findFolderObjectsByName
     * \param aName
     * \return
     */
    QListWidgetItem* findFolderObjectsByName( QString aName );

    /*!
     * \brief _sceneObj
     */
    OmgSceneObj* _sceneObj;

    /*!
     * \brief _folder
     */
    QString _folder;

    /*!
     * \brief validate
     * \return
     */
    bool validate( void );

    /*!
     * \brief createSceneObject
     * \return
     */
    OmgSceneObj* createSceneObject( void );

    /*!
     * \brief storeAndFinnish
     * \param aObject
     */
    void storeAndFinnish( OmgSceneObj* aObject );

signals:

    /*!
     * \brief HideInputData
     */
    void HideInputData();
private slots:

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
     * \brief on__pbTextures_clicked
     */
    void on__pbTextures_clicked();

    void on_deleteTextures_clicked();
    void on_texturesEqual_clicked();
};

#endif // QOMGSCENEOBJECTSDIALOG_H
