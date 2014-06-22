#include "OgreWidget.h"
#include "Display/OgreManager.h"
#include "Input/InputManager.h"
#include "Input/MouseController.h"
#include "Input/KeyboardController.h"
#include <QWheelEvent>
#include "Input/MouseScenaryEdit.h"
#include "qmessagebox.h"

bool ViewKeyboard[1024];

//----------------------------------------------------------------------------------------
OgreWidget::OgreWidget(QWidget *parent, bool doLoadFile, Qt::WindowFlags f): QWidget( parent,  f /*| Qt::MSWindowsOwnDC*/ ),
            mOgreRoot(0), mRenderWindow(0), mOgreInitialised(false), mLastKeyEventTime(0),
            mRenderStop(false), mScreenResize(false), mCursorHidden(false), mDoLoadFile(doLoadFile)
{
    mFrameCounter = 0;
    mTotalFrameTime = 0;
    mSwitchingScene = false;

    for(int i = 0;i < 1024;i++)
        ViewKeyboard[i] = false;

    setAcceptDrops(true);
    setContextMenuPolicy( Qt::PreventContextMenu );

    setFocusPolicy(Qt::WheelFocus);
    setMouseTracking(true);

    setAttribute( Qt::WA_PaintOnScreen );
    setAttribute( Qt::WA_NoSystemBackground );
    setAttribute( Qt::WA_NoBackground );
    setAttribute( Qt::WA_NativeWindow );
    setAttribute( Qt::WA_OpaquePaintEvent );

    initializeOGRE();

    mSet_arrows.insert(Qt::Key_Up);
    mSet_arrows.insert(Qt::Key_Down);
    mSet_arrows.insert(Qt::Key_Right);
    mSet_arrows.insert(Qt::Key_Left);
}
//----------------------------------------------------------------------------------------
OgreWidget::~OgreWidget()
{
    if(mOgreInitialised)
    {
        Ogre::Root::getSingletonPtr()->removeFrameListener(this);
        mOgreRoot->getRenderSystem()->removeListener(this);
    }
    
    destroy();
}
//----------------------------------------------------------------------------------------
static Ogre::Vector3 oldCamPos = Ogre::Vector3::ZERO;
int oldTris = 0;

bool OgreWidget::frameStarted(const Ogre::FrameEvent& evt)
{
    displayFPS(evt.timeSinceLastFrame);

    return true;
}
//----------------------------------------------------------------------------------------
void OgreWidget::initializeOGRE()
{
    //== Creating and Acquiring Ogre Window ==//

    // Get the parameters of the window QT created
	std::string resourcesCfg;
	std::string pluginsCfg;
	std::string ogreCfg;
	std::string ogreLog;
    #ifdef _DEBUG
		resourcesCfg = "./debug/resources_d.cfg";
		pluginsCfg = "./debug/plugins_d.cfg";
		ogreCfg = "./debug/ogre_d.cfg";
		ogreLog = "./debug/ogre_d.log";
	#else
		resourcesCfg = "./release/resources.cfg";
		pluginsCfg = "./release/plugins.cfg";
		ogreCfg = "./release/ogre_d.cfg";
		ogreLog = "./release/ogre_d.log";
	#endif

	mOgreRoot = new Ogre::Root( pluginsCfg, ogreCfg, ogreLog );

    // setupResources(); ========================
    // Load resource paths from config file
    Ogre::ConfigFile cf;
    cf.load(resourcesCfg);

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
    // setupResources(); ========================

    // setup a renderer
    Ogre::RenderSystem *rs = mOgreRoot->getRenderSystemByName("OpenGL Rendering Subsystem");

    assert( rs ); // user might pass back a null renderer, which would be bad!

    mOgreRoot->setRenderSystem(rs);
    rs->setConfigOption("Colour Depth", "16");
    rs->setConfigOption("FSAA", "0");
    rs->setConfigOption("Full Screen", "No");
    rs->setConfigOption("RTT Preferred Mode", "FBO");

    QString dimensions = QString( "%1x%2" ).arg(width()).arg(height());
    rs->setConfigOption( "Video Mode", dimensions.toStdString() );

    // initialize without creating window
    mOgreRoot->saveConfig();
    mOgreRoot->initialise(false); // don't create a window

    mSceneManager = mOgreRoot->createSceneManager( Ogre::ST_GENERIC );
    mSceneManager->setAmbientLight( Ogre::ColourValue(0.3,0.3,0.3) );

    //== Creating and Acquiring Ogre Window ==//

    // Get the parameters of the window QT created
    Ogre::String winHandle;
#ifdef WIN32
    // Windows code
    winHandle += Ogre::StringConverter::toString((unsigned long)(this->parentWidget()->winId()));
#elif MACOS
    // Mac code, tested on Mac OSX 10.6 using Qt 4.7.4 and Ogre 1.7.3
    Ogre::String winHandle  = Ogre::StringConverter::toString(winId());
#else
    // Unix code
    QX11Info info = x11Info();
    winHandle  = Ogre::StringConverter::toString((unsigned long)(info.display()));
    winHandle += ":";
    winHandle += Ogre::StringConverter::toString((unsigned int)(info.screen()));
    winHandle += ":";
    winHandle += Ogre::StringConverter::toString((unsigned long)(this->parentWidget()->winId()));
#endif


    Ogre::NameValuePairList params;
#ifndef MACOS
    // code for Windows and Linux
    params["parentWindowHandle"] = winHandle;
    params["externalGLControl"] = "true";
    params["currentGLContext"] = "true";

    mRenderWindow = mOgreRoot->createRenderWindow( "RenderWindow", width(),height(), false, &params);
    mRenderWindow->setActive(true);
    mRenderWindow->setVisible(true);
    mRenderWindow->resize( width(), height() );

    WId window_id;

    //! \note "HWND" causes mousePressEvent not to be called - "WINDOW" should be used instead
    mRenderWindow->getCustomAttribute( "WINDOW", &window_id );
    assert( window_id );

    // Take over the ogre created window.
    QWidget::create( window_id );

    if (mRenderWindow) {
      mRenderWindow->reposition( parentWidget()->x(), parentWidget()->y() );
      mRenderWindow->resize( width(), height() );
      mRenderWindow->windowMovedOrResized();
    }

    OgreManager::getInstance()->setWindow(mRenderWindow);
    mOgreRoot->getRenderSystem()->addListener(this);
    OgreManager::getInstance()->setSceneManager( mSceneManager );
    OgreManager::getInstance()->setRoot( mOgreRoot );
    Ogre::Root::getSingletonPtr()->addFrameListener(this);
    Ogre::MeshManager::getSingletonPtr()->setListener(this);

#else
    // code for Mac
    params["externalWindowHandle"] = winHandle;
    params["macAPI"] = "cocoa";
    params["macAPICocoaUseNSView"] = "true";
    mRenderWindow = mOgreRoot->createRenderWindow("RenderWindow",width(), height(), false, &params);
    makeCurrent();
#endif

    mOgreInitialised = true;
}

//------------------------------------------------------------------------------------
bool adjustFrameTime = false;

void OgreWidget::paintEvent(QPaintEvent* evt)
{
    if(!isVisible())
        return;

    if(!mRenderWindow)
        initializeOGRE();

    if(mOgreInitialised && !mRenderStop)
    {
      int width = this->width();
        if(this->width() > 0 && this->height() > 0)
        {
            if(adjustFrameTime)
            {
                mOgreRoot->renderOneFrame(0.01f);
                adjustFrameTime = false;
            }
            else
                mOgreRoot->renderOneFrame();


#if OGRE_PLATFORM == OGRE_PLATFORM_LINUX
            mRenderWindow->update();
#endif
            
        }
    }
    else
    {
        QString msgstr = tr("Initializing OGRE...");

        if(mOgreInitialised)
        {
            if(mDoLoadFile)
                msgstr = tr("Loading Scene...");
            else
                msgstr = tr("Please load a Scene File...");
        }

        if(mRenderStop)
            msgstr = tr("Rendering stopped...");

       // mOverlayWidget->setMessageString(msgstr);

        adjustFrameTime = true;
    }
}
//------------------------------------------------------------------------------------
void OgreWidget::resizeEvent(QResizeEvent* evt)
{
    if(!mRenderWindow)
      return;

    mScreenResize = true;

    int w = width();
    mRenderWindow->resize(width(), height());

    mScreenResize = false;
}
//------------------------------------------------------------------------------------
void OgreWidget::focusInEvent(QFocusEvent *evt)
{

}
//------------------------------------------------------------------------------------
void OgreWidget::focusOutEvent(QFocusEvent *evt)
{
    
}
//------------------------------------------------------------------------------------
void OgreWidget::keyPressEvent(QKeyEvent *evt)
{
  if( Qt::Key(evt->key()) ==  Qt::Key_D )
  {
    setCursor(Qt::CrossCursor);
    MouseScenaryEdit * mouseController = dynamic_cast<MouseScenaryEdit *>( InputManager::getInstance()->getController("EditScenary") );
    if(mouseController)
    {
      currentObjName = mouseController->currentObjectName();
      mouseController->changeCurrentObject("");
    }
  }

  InputManager::getInstance()->getKeyBoardController()->keyPressed(Qt::Key(evt->key()));
}
//------------------------------------------------------------------------------------
void OgreWidget::keyReleaseEvent(QKeyEvent *evt)
{
  MouseScenaryEdit * mouseController = dynamic_cast<MouseScenaryEdit *>( InputManager::getInstance()->getController("EditScenary") );
  if(mouseController)
  {
    if( Qt::Key_D == evt->key() )
    {
      setCursor(Qt::ArrowCursor);
      mouseController->changeCurrentObject(currentObjName);
    } else if( mSet_arrows.count(Qt::Key(evt->key())) == 1 )
    {
      mouseController->arrowKeyPressed( Qt::Key(evt->key() ));
    }
  }

  InputManager::getInstance()->getKeyBoardController()->keyReleased(Qt::Key(evt->key()));
}
//------------------------------------------------------------------------------------
void OgreWidget::mouseMoveEvent(QMouseEvent *evt)
{
  InputManager::getInstance()->getController(OgreManager::getInstance()->getCurrentScene())->moved(evt->x(), evt->y(), width(), height());
}
//------------------------------------------------------------------------------------
void OgreWidget::mousePressEvent(QMouseEvent *evt)
{
  InputManager::getInstance()->getController(OgreManager::getInstance()->getCurrentScene())->buttonPressed( evt->button(), evt->x(), evt->y(), width(), height());
}

//------------------------------------------------------------------------------------
void OgreWidget::mouseReleaseEvent(QMouseEvent *evt)
{
  InputManager::getInstance()->getController(OgreManager::getInstance()->getCurrentScene())->buttonReleased(evt->x(), evt->y(), width(), height() );
}

//------------------------------------------------------------------------------------
void OgreWidget::mouseDoubleClickEvent(QMouseEvent *evt)
{
  InputManager::getInstance()->getController(OgreManager::getInstance()->getCurrentScene())->doubleClickEvent(evt->x(), evt->y(), width(), height(), this);
}
//------------------------------------------------------------------------------------
void OgreWidget::leaveEvent(QEvent *evt)
{
   /* if(!OgitorsRoot::getSingletonPtr()->IsSceneLoaded())
        return;

    Ogre::Vector2 pos(-1, -1);

    OgitorsRoot::getSingletonPtr()->OnMouseLeave(pos, 0);
    OgreWidgetMouseMovedSincePress = true;*/
}
//------------------------------------------------------------------------------------
void OgreWidget::wheelEvent(QWheelEvent *evt)
{
  InputManager::getInstance()->getController(OgreManager::getInstance()->getCurrentScene())->wheelMoved( evt->delta() );
}

//------------------------------------------------------------------------------------
QPaintEngine* OgreWidget::paintEngine() const
{
    // We don't want another paint engine to get in the way for our Ogre based paint engine.
    // So we return nothing.
    return NULL;
}

//------------------------------------------------------------------------------------
void OgreWidget::displayFPS(float time)
{
    mFrameCounter++;
    mTotalFrameTime += time;
    mFrameRate = (float)mFrameCounter / (float)mTotalFrameTime ;
    if(mTotalFrameTime > 2.0f)
    {
        mTotalFrameTime = 0;
        mFrameCounter = 0;
        char temp[500];
        sprintf(temp,"FPS: %.1f  ", mFrameRate);
        mfps = QString(temp);
    }
}
//----------------------------------------------------------------------------------
void OgreWidget::processMaterialName(Ogre::Mesh *mesh, Ogre::String *name)
{
}
//-------------------------------------------------------------------------------------------
void OgreWidget::dragEnterEvent(QDragEnterEvent *evt)
{
  // Some stuff
}
//-------------------------------------------------------------------------------------------
void OgreWidget::dragLeaveEvent(QDragLeaveEvent *evt)
{
    // Some stuff
}
//-------------------------------------------------------------------------------------------
void OgreWidget::dragMoveEvent(QDragMoveEvent *evt)
{
    // Some stuff
}
//-------------------------------------------------------------------------------------------
void OgreWidget::dropEvent(QDropEvent *evt)
{
    // Some stuff
}
//-------------------------------------------------------------------------------------------
void OgreWidget::showObjectMenu()
{
    
}
//-------------------------------------------------------------------------------------------
void OgreWidget::contextMenu(int id)
{
    
}