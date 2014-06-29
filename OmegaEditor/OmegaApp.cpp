#include "InputData/OmegaWindow.h"
#include <QApplication>
#include <QThread>
#include <QFILE>
#include <QTextStream>
#include <QtDebug>
#include "InputData/QOmgWindowMngr.h"
#include <QSplashScreen>
#include <Windows.h>

#include "Utils/OgreManager.h"
#include "EditionManagers/EditSceneManager.h"
#include "EditionManagers/EditCharacterManager.h"
#include "EditionManagers/EditCubeManager.h"
#include "Input/InputManager.h"
#include "Saver/EntitiesXMLReader.h"
#include "Input/MouseController.h"


static void customMsgHandler(QtMsgType type, const QMessageLogContext &, const QString &message)
{
  QString txt;
  switch (type) {
  case QtDebugMsg:
    txt = QString("Debug: %1").arg(message);
    break;
  case QtWarningMsg:
    txt = QString("Warning: %1").arg(message);
    break;
  case QtCriticalMsg:
    txt = QString("Critical: %1").arg(message);
    break;
  case QtFatalMsg:
    txt = QString("Fatal: %1").arg(message);
    abort();
  }

  QFile outFile("log.txt");
  outFile.open(QIODevice::WriteOnly | QIODevice::Append);
  QTextStream ts(&outFile);
  ts << txt << endl;
}

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  qInstallMessageHandler(customMsgHandler);
  
  QSplashScreen splash( QPixmap( ":/OmegaEditor/Resources/Icons/splash.png" ) );
  splash.show();
  a.processEvents();

  OmegaWindow * w = QOmgWindowMngr::Instance()->GetMainWindow();

  splash.showMessage("Loading Scene Manager");
  EditSceneManager::getInstance();
  splash.showMessage("Loading Character Manager");
  EditCharacterManager::getInstance();
  splash.showMessage("Loading Cube Manager");
  EditCubeManager::getInstance();

  splash.showMessage("Loading Controllers");
  InputManager::getInstance();
  OgreManager::getInstance()->selectScene("EditScenary");
  InputManager::getInstance()->getController("EditScenary")->rotateCam(0,0,OgreManager::getInstance()->getSceneManager()->getCamera("EditScenaryCamera"));
  InputManager::getInstance()->getController("EditCube")->rotateCam(0,0,OgreManager::getInstance()->getSceneManager()->getCamera("EditCubeCamera"));
  InputManager::getInstance()->getController("EditCharacter")->rotateCam(0,0, OgreManager::getInstance()->getSceneManager()->getCamera("EditCharacterCamera"));

  splash.showMessage("Reading weapons");
  EntitiesXMLReader xmlReaderWeapons("weapons.xml");
  xmlReaderWeapons.executeForWeapons();
  splash.showMessage("Reading players...");
  EntitiesXMLReader xmlReaderPlayers("players.xml");
  xmlReaderPlayers.executeForPlayers();
  splash.showMessage("Reading enemies");
  EntitiesXMLReader xmlReaderEnemies("enemies.xml");
  xmlReaderEnemies.executeForEnemies();
  splash.showMessage("Reading scene objects");
  EntitiesXMLReader xmlReaderSceneObj("sceneobj.xml");
  xmlReaderSceneObj.executeForSceneObj();
  splash.showMessage("Reading items");
  EntitiesXMLReader xmlReaderItems("items.xml");
  xmlReaderItems.executeForItems();
  splash.showMessage("Reading map");
  EntitiesXMLReader xmlReaderMaps("map.xml");
  xmlReaderMaps.executeForMaps();
  splash.showMessage("Reading games");
  EntitiesXMLReader xmlReaderGames("games.xml");
  xmlReaderGames.executeForGames();


  splash.showMessage("Update Widgets");
  QOmgWindowMngr::Instance()->GetMainWindow()->UpdateWidgets();

  w->show();

  splash.finish(w);

  return a.exec();
}
