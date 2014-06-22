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

#ifndef OMGSCENEOBJ_H
#define OMGSCENEOBJ_H

#include "OmgCharacter.h"
#include "QtComponents/QOmgListItem.h"
#include <QPixmap>


class OmgSceneObj : public OmgEntity
{
public:
    //- OmgSceneObj
    //? String Constructor
    //> QString a_name
    OmgSceneObj(QString a_name);

    //- OmgSceneObj
    //? String Constructor
    //> QString a_name
    //> std::map<std::string, std::string> a_texture
    OmgSceneObj(QString a_name, std::map<std::string, std::string> a_textures);

    //- OmgSceneObj
    //? String Constructor
    //> QString a_name
    //> std::map<std::string, std::string> a_texture
    OmgSceneObj(QString a_name, std::map<std::string, std::string> a_textures, int rgb[3]);

    //- OmgSceneObj
    //? Default Destructor
    ~OmgSceneObj();

    /*!
     * \brief GetMainTexture
     * \return
     */
    QPixmap GetMainTexture( void );

    /*!
     * \brief setTexture
     * \param textureName
     * \param textureFilename
     */
    void setTexture(std::string textureName, std::string textureFilename);


    /*!
     * \brief getTextures
     * \return
     */
    std::map<std::string, std::string> getTextures( void );

    /*!
     * \brief setObjectType
     * \param aType
     */
    void setObjectType( Omega::SceneObjType aType );

    /*!
     * \brief getObjectType
     * \return
     */
    Omega::SceneObjType getObjectType( void );

    /*!
     * \brief getObjectTypeStr
     * \return
     */
    QString getObjectTypeStr( void );

    /*!
     * \brief createCustomPixmap
     */
    void createCustomPixmap( void );

    /*!
     * \brief writeInfo
     * \param[in] QXmlStreamWriter a_xml_stream
     */
    virtual void writeInfo( QXmlStreamWriter *a_xml_stream );

protected:

    /*!
     * \brief _texture The pixmap with main texture of the object, a representative one
     */
    QPixmap _texture;

    /*!
     * \brief _typeObj
     */
    Omega::SceneObjType _typeObj;

    /*!
     * \brief _m_textures
     */
    std::map< std::string, std::string> _m_textures;

    /*!
     * \brief _baseColor
     */
    QColor _baseColor;

};

#endif // OMGSCENEOBJ_H
