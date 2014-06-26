#ifndef __OGRE_WIDGET_H__
#define __OGRE_WIDGET_H__

#include <QTimer>
#include <QApplication>
#include <QWidget>
#include <Ogre.h>
#include <QString>

#ifndef WIN32
#include <QX11Info>
#endif

class OgreWidget : public QWidget, public Ogre::FrameListener, public Ogre::RenderSystem::Listener, public Ogre::MeshSerializerListener
{
  Q_OBJECT

public:
  bool  mOgreInitialised;
  bool  mRenderStop;
  float mFrameRate;
  QString       mfps;
  Ogre::RenderWindow *mRenderWindow;

  OgreWidget(QWidget *parent=0, bool doLoadFile = false, Qt::WindowFlags f=0);

  virtual ~OgreWidget();

  // Override QWidget::paintEngine to return NULL
  QPaintEngine* paintEngine() const; // Turn off QTs paint engine for the Ogre widget.

  void showCursorEx(bool bShow)
  {
    if(mCursorHidden == bShow)
    {
      if(!bShow)
        setCursor(Qt::BlankCursor);
      else
        setCursor(Qt::ArrowCursor);

      mCursorHidden = !bShow;
    }
  };

  void initializeOGRE();
  void setTimerInterval(int value);

  bool isSizing()
  {
    return mScreenResize;
  }

  bool isSwitchingScene() {return mSwitchingScene;};
  void setSwitchingScene(bool switching) {mSwitchingScene = switching;};
  void processMaterialName(Ogre::Mesh *mesh, Ogre::String *name);
  void processSkeletonName(Ogre::Mesh *mesh, Ogre::String *name){};
  void processMeshCompleted(Ogre::Mesh *mesh){};
  void stopRendering(bool stop) {mRenderStop = stop;};

  public Q_SLOTS:
    void contextMenu(int id);

protected:
  Ogre::Root         *mOgreRoot;
  Ogre::SceneManager  *mSceneManager;
  bool                mSwitchingScene;

  unsigned int  mLastKeyEventTime;
  volatile bool mScreenResize;
  int           mFrameCounter;
  double        mTotalFrameTime;
  bool          mCursorHidden;
  bool          mDoLoadFile;
  std::string   currentObjName;

  virtual void resizeEvent(QResizeEvent* evt);
  virtual void paintEvent(QPaintEvent* evt);
  virtual void focusOutEvent(QFocusEvent *evt);
  virtual void focusInEvent(QFocusEvent *evt);
  virtual void keyPressEvent(QKeyEvent *evt);
  virtual void keyReleaseEvent(QKeyEvent *evt);
  virtual void mouseMoveEvent(QMouseEvent *evt);
  virtual void mousePressEvent(QMouseEvent *evt);
  virtual void mouseReleaseEvent(QMouseEvent *evt);
  virtual void mouseDoubleClickEvent(QMouseEvent *evt);
  virtual void leaveEvent(QEvent *evt);
  virtual void wheelEvent(QWheelEvent *evt);
  virtual void dragEnterEvent(QDragEnterEvent *evt);
  virtual void dragLeaveEvent(QDragLeaveEvent *evt);
  virtual void dragMoveEvent(QDragMoveEvent *evt);
  virtual void dropEvent(QDropEvent *evt);

  void eventOccurred (const Ogre::String &eventName, const Ogre::NameValuePairList *parameters=0)
  {
    if(mScreenResize)
      return;
  };

  bool frameStarted(const Ogre::FrameEvent& evt);

  void displayFPS(float time);
  void showObjectMenu();
  std::set<Qt::Key> mSet_arrows;
};

#endif // __OGRE_WIDGET_H__

