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

#ifndef OMGSCENEOBJCONTAINER_H
#define OMGSCENEOBJCONTAINER_H

#include "OmgSceneObj.h"
#include <QString>
#include <map>
#include <vector>
#include <QHash>
#include "Omega.h"

class QOmgListItem;

class OmgSceneObjContainer
{
public:

    /*!
     * \brief Instance
     * \return
     */
    static OmgSceneObjContainer* Instance( void );

    //- GetObject
    //? Gets an object from the container
    //> QString, the name of the object to get
    //return OmgSceneObj, with the name, otherwise retunr NULL
    OmgSceneObj* getSceneObj( QString a_name );

    //- AddObject
    //? Adds an object to the container
    //> OmgSceneObj The object to add to the container
    //return bool with the result of the operation
    bool AddObject(OmgSceneObj* a_obj );

    //- DeleteObject
    //? Deletes an object to the container
    //> QString the name of the object to delete
    //return bool with the result of the operation
    bool DeleteObject(QString a_name );

    //- GetAvailableSceneItems
    //? Gets a list of items with the parameters of the object
    Omega::ListItemVector GetAvailableSceneItems(void);

    //- GetAvailableSceneObjects
    //? Gets a list of items with the parameters of the object
    Omega::EntityVector GetAvailableSceneObjects(void);

    /*!
     * \brief sceneObjInFolder
     * \param aFolderName
     * \return
     */
    Omega::EntityVector sceneObjInFolder( QString aFolderName );

    /*!
     * \brief buildSceneObj
     * \param aSceneObjParams
     */
    void buildSceneObj( QStringList aSceneObjParams );

protected:

    //-OmgSceneObjContainer
    //Default constructor of the container
    OmgSceneObjContainer();

private:

    //? The map of the objects in the container
    std::map<QString,OmgSceneObj*> _map_obj;

    //? The instance of the container
    static OmgSceneObjContainer* _p_instance;
};

#endif // OMGSCENEOBJCONTAINER_H
