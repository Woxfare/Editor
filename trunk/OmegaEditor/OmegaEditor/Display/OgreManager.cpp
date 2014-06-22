#include "OgreManager.h"
#include <QDebug>
#include <QFileDialog>
#include <string>
#include <QString>
#include <QStringList>
#include "Utils\CubeUtils.h"
#include "QtComponents\QOmgWindowMngr.h"
#include "EditionManagers\EditCharacterManager.h"

OgreManager * OgreManager::_p_instance = NULL;

OgreManager::OgreManager()
{
}

OgreManager::~OgreManager()
{
    _p_ogreRoot->shutdown();
    delete _p_ogreRoot;
}

OgreManager* OgreManager::getInstance()
{
    if(!_p_instance)
        _p_instance = new OgreManager();
    return _p_instance;
}

Ogre::Root * OgreManager::getRoot()
{
    return _p_ogreRoot;
}

Ogre::RenderWindow * OgreManager::getWindow()
{
    return _p_ogreWindow;
}

Ogre::Viewport * OgreManager::getViewPort()
{
    return _p_viewport;
}

Ogre::SceneManager * OgreManager::getSceneManager()
{
    return _p_sceneManager;
}

void OgreManager::setRoot(Ogre::Root * root)
{
    _p_ogreRoot = root;
}

void OgreManager::setWindow(Ogre::RenderWindow * window)
{
    _p_ogreWindow = window;
}

void OgreManager::setViewport(Ogre::Viewport * viewport)
{
    _p_viewport = viewport;
}

void OgreManager::setSceneManager(Ogre::SceneManager * sceneManager)
{
    _p_sceneManager = sceneManager;
}

void OgreManager::initialize(std::string plugins_file, std::string ogre_cfg_file, std::string ogre_log, int width, int height)
{
    // create the main ogre object
    _p_ogreRoot = new Ogre::Root( plugins_file, ogre_cfg_file, ogre_log );

    setupResources();

    // setup a renderer
    Ogre::RenderSystem *rs = _p_ogreRoot->getRenderSystemByName("OpenGL Rendering Subsystem");

    assert( rs ); // user might pass back a null renderer, which would be bad!

    _p_ogreRoot->setRenderSystem(rs);
    rs->setConfigOption("Colour Depth", "16");
    rs->setConfigOption("FSAA", "0");
    rs->setConfigOption("Full Screen", "No");
    rs->setConfigOption("RTT Preferred Mode", "FBO");

    QString dimensions = QString( "%1x%2" )
                      .arg(width)
                      .arg(height);
    rs->setConfigOption( "Video Mode", dimensions.toStdString() );

    // initialize without creating window
    _p_ogreRoot->saveConfig();
    _p_ogreRoot->initialise(false); // don't create a window

    _p_sceneManager = _p_ogreRoot->createSceneManager( Ogre::ST_GENERIC );
    _p_sceneManager->setAmbientLight( Ogre::ColourValue(0.3,0.3,0.3) );

}

void OgreManager::setupResources()
{
	std::string mResourcesCfg;
	std::string mPluginsCfg;

	#ifdef _DEBUG
		mResourcesCfg = "./debug/resources_d.cfg";
		mPluginsCfg = "./debug/plugins_d.cfg";
	#else
		mResourcesCfg = "./release/resources.cfg";
		mPluginsCfg = "./release/plugins.cfg";
	#endif

    // Load resource paths from config file
    Ogre::ConfigFile cf;
    cf.load(mResourcesCfg);

    // Go through all sections & settings in the file
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

    Ogre::String secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                archName, typeName, secName);
        }
    }
}

void OgreManager::resize(int width, int heigth, int positionX, int positionY)
{
    _p_ogreWindow->reposition(  positionX,
                                positionY );
    _p_ogreWindow->resize( width, heigth );

    Ogre::Camera * camera = _p_sceneManager->getCamera("EditScenaryCamera");
    if (camera)
        camera->setAspectRatio(static_cast<Ogre::Real>(width)/static_cast<Ogre::Real>(heigth));

    camera = _p_sceneManager->getCamera("EditCubeCamera");
    if (camera)
        camera->setAspectRatio(static_cast<Ogre::Real>(width)/static_cast<Ogre::Real>(heigth));
}

void OgreManager::renderFrame()
{
    _p_ogreRoot->renderOneFrame();
}

std::string OgreManager::getCurrentScene()
{
    return _sceneMode;
}



void OgreManager::selectScene( std::string sceneName )
{
    std::string sceneNodeName = sceneName + "Node",
                sceneCameraName = sceneName + "Camera",
                sceneLightName = sceneName + "Light";

  try
  {
    _p_ogreWindow->removeAllViewports();
    _p_ogreWindow->addViewport( _p_sceneManager->getCamera(sceneCameraName) );
    //_p_sceneManager->getLight(sceneLightName)->setVisible(true);

    _sceneMode = sceneName;

    if( sceneName == "EditCube" )
    {
      EditCharacterManager::getInstance()->setPartsToShow( std::vector< characterParts> () );
      _p_sceneManager->getSceneNode("EditScenaryNode")->setVisible(false);    
      CubeUtils::attachCubeFaces("EditCube");
      _p_sceneManager->getSceneNode("CurrentNode")->setVisible(false);
      //_p_sceneManager->getSceneNode("base_plane")->setVisible(false);

      QOmgWindowMngr::Instance()->GetMainWindow()->hideCharacterPartsSelector();
      QOmgWindowMngr::Instance()->GetMainWindow()->hideEditScenearyWidget();
    }
    else if(sceneName == "EditCharacter")
    {
      _p_sceneManager->getSceneNode("EditCubeNode")->detachAllObjects();
      _p_sceneManager->getSceneNode("EditScenaryNode")->setVisible(false);

      std::vector< characterParts > parts;
      parts.push_back( head );
      parts.push_back( body );
      parts.push_back( armRight );
      parts.push_back( armLeft );
      parts.push_back( legLeft );
      parts.push_back( legRight );

      EditCharacterManager::getInstance()->setPartsToShow( parts );

      _p_sceneManager->getSceneNode("CurrentNode")->setVisible(false);
      //_p_sceneManager->getSceneNode("base_plane")->setVisible(false);

      QOmgWindowMngr::Instance()->GetMainWindow()->showCharacterPartsSelector();
      QOmgWindowMngr::Instance()->GetMainWindow()->hideEditScenearyWidget();
    }
    else if(sceneName =="EditScenary")
    {
      EditCharacterManager::getInstance()->setPartsToShow( std::vector< characterParts> () );
      _p_sceneManager->getSceneNode("EditCubeNode")->detachAllObjects();
      _p_sceneManager->getSceneNode(sceneNodeName)->setVisible(true);
      _p_sceneManager->getSceneNode("CurrentNode")->setVisible(true);
      //_p_sceneManager->getSceneNode("base_plane")->setVisible(true);
	  _p_sceneManager->getLight("EditCharacterLight")->setVisible(false);
	  //_p_sceneManager->getLight("EditCubeLight")->setVisible(false);

      QOmgWindowMngr::Instance()->GetMainWindow()->hideCharacterPartsSelector();
      QOmgWindowMngr::Instance()->GetMainWindow()->showEditScenearyWidget();
    }

  } catch (Ogre::Exception e) {
    qDebug() << e.getFullDescription().c_str();
  }
}

void
OgreManager::deleteMaterialGroup(std::string baseName)
{
    char nameN[256];
    sprintf_s(nameN,"%sMatTop",baseName.c_str());
    Ogre::MaterialManager::getSingleton().remove(nameN);
    sprintf_s(nameN,"%sMatBottom",baseName.c_str());
    Ogre::MaterialManager::getSingleton().remove(nameN);
    sprintf_s(nameN,"%sMatLeft",baseName.c_str());
    Ogre::MaterialManager::getSingleton().remove(nameN);
    sprintf_s(nameN,"%sMatRight",baseName.c_str());
    Ogre::MaterialManager::getSingleton().remove(nameN);
    sprintf_s(nameN,"%sMatFront",baseName.c_str());
    Ogre::MaterialManager::getSingleton().remove(nameN);
    sprintf_s(nameN,"%sMatBack",baseName.c_str());
    Ogre::MaterialManager::getSingleton().remove(nameN);
}

void
OgreManager::createEntity0(std::string a_name)
{
    Ogre::Entity * entity0 = OgreManager::getInstance()->getSceneManager()->createEntity(a_name+"_0", a_name+".mesh");
    entity0->setCastShadows(false);
}