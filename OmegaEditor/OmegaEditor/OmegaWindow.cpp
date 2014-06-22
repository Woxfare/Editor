#include "OmegaWindow.h"
#include "ui_OmegaWindow.h"

#include "QtComponents/QOmgTreeEntities.h"
#include "QtComponents/QOmgVerticalButton.h"
#include "QtComponents/QOmgDialogEnemy.h"
#include "QtComponents/QOmgDialogPlayer.h"
#include "QtComponents/QOmgSceneObjectsDialog.h"
#include "QtComponents/QOmgExporterDialog.h"
#include "QtComponents/QOmgFolderDialog.h"
#include "QtComponents/QOmgWeaponsDialog.h"
#include "QtComponents/QOmgMapDialog.h"
#include "OmgEntities/OmgItemContainer.h"
#include "OmgEntities/OmgPlayerContainer.h"
#include "OmgEntities/OmgEnemyContainer.h"
#include "OmgEntities/OmgSceneObjContainer.h"
#include "OmgEntities/OmgWeaponsContainer.h"
#include "QtComponents/QOmgGameCreatorDialog.h"
#include "QtComponents/QOmgStyle.h"
#include "Omega.h"
#include "QtComponents/QOmgLeaf.h"
#include "Folders/OmgFoldersMngr.h"
#include "QtComponents/QOmgItemDialog.h"
#include "Saver/OmgSaverMngr.h"
#include <QMessageBox>
#include <QDebug>
#include "Input/MouseScenaryEdit.h"
#include "Input/InputManager.h"
#include "QtComponents/QOmgWindowMngr.h"
#include "OmgEntities/OmgMapContainer.h"
#include "OmgEntities/OmgGameContainer.h"
#include "OmgEntities/OmgGame.h"
#include "QtComponents/CharacterPartsSelectorWidget.h"
#include "OgreWidget.h"

OmegaWindow::OmegaWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::OmegaWindow)
{
    ui->setupUi(this);
    ui->scrollArea->hide();
    ui->bigScrollArea->hide();
    setStyleSheet(QOmgStyle::CurrentStyleSheet());
    
    mOgreWidget = new OgreWidget( ui->renderWidget );

    QVBoxLayout *renderWindowLayout = new QVBoxLayout();
    renderWindowLayout->setSpacing(0);
    renderWindowLayout->setMargin(0);
    renderWindowLayout->addWidget(mOgreWidget, 1);

    ui->renderWidget->setLayout(renderWindowLayout);

    mTimer = new QTimer(this);
    mTimer->setInterval(0);
    connect(mTimer, SIGNAL(timeout()), this, SLOT(timerLoop()));
    mTimer->start();
}
void
OmegaWindow::timerLoop()
{
  //OgreManager::getInstance()->getRoot()->renderOneFrame(0.01f);
  mOgreWidget->update();
  ui->_fps_label->setText(mOgreWidget->mfps);
}

OmegaWindow::~OmegaWindow()
{
    delete ui;
}

void OmegaWindow::on_actionNew_Player_triggered()
{
    QOmgDialogPlayer* p_player = new QOmgDialogPlayer(this);

    int w = p_player->size().width();
    ui->treeWidget->setMaximumWidth(w);
    ui->scrollArea->setMaximumSize(p_player->size());
    ui->treeWidget->setMinimumWidth(w);
    ui->scrollArea->setWidget(p_player);
    ui->scrollArea->show();
    connect(p_player,SIGNAL(hideInputData()),this,SLOT(hideWidgetArea()));
}

void OmegaWindow::on_actionNew_Enemy_triggered()
{
    QOmgDialogEnemy* p_enemy = new QOmgDialogEnemy( this );

    int w = p_enemy->size().width();
    ui->treeWidget->setMaximumWidth(w);
    ui->scrollArea->setMaximumSize(p_enemy->size());
    ui->treeWidget->setMinimumWidth(w);
    ui->scrollArea->setWidget(p_enemy);
    ui->scrollArea->show();
    connect(p_enemy,SIGNAL(hideInputData()),this,SLOT(hideWidgetArea()));
}

void OmegaWindow::on_actionEdit_Player_triggered( OmgPlayer* ap_player )
{
    QOmgDialogPlayer* p_player = new QOmgDialogPlayer(this, ap_player);

    int w = p_player->size().width();
    ui->treeWidget->setMaximumWidth(w);
    ui->scrollArea->setMaximumSize(p_player->size());
    ui->treeWidget->setMinimumWidth(w);
    ui->scrollArea->setWidget(p_player);
    ui->scrollArea->show();
    connect(p_player,SIGNAL(hideInputData()),this,SLOT(hideWidgetArea()));
}

void OmegaWindow::on_actionEdit_Enemy_triggered( OmgEnemy* ap_enemy )
{
    QOmgDialogEnemy* p_enemy = new QOmgDialogEnemy( this, ap_enemy );

    int w = p_enemy->size().width();
    ui->treeWidget->setMaximumWidth(w);
    ui->scrollArea->setMaximumSize(p_enemy->size());
    ui->treeWidget->setMinimumWidth(w);
    ui->scrollArea->setWidget(p_enemy);
    ui->scrollArea->show();
    connect(p_enemy,SIGNAL(hideInputData()),this,SLOT(hideWidgetArea()));
}

void OmegaWindow::closeEvent(QCloseEvent *event)
{
    //! Ignore the event by default.. otherwise the window will be closed always.
    event->ignore();

    if(!OmgSaverMngr::Instance()->isAllSaved())
    {
        QMessageBox msgBox;
        msgBox.setWindowIcon(QIcon(":/Media/omega.png"));
        msgBox.setIconPixmap(QPixmap(":/Media/omega2.png"));
        QString strToShow = QString("Some Entities has been created or modified...");
        msgBox.setText(strToShow);
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        msgBox.setStyleSheet(QOmgStyle::CurrentStyleSheet());
        int ret = msgBox.exec();

        switch (ret) {
          case QMessageBox::Save:
            {
              // Save was clicked
              qDebug() << "SAVE";
              OmgSaverMngr::Instance()->saveAll();
              event->accept();
              break;
            }
          case QMessageBox::Discard:
            {
                // Don't Save was clicked
                qDebug() << "DISCARD";
                event->accept();
                break;
            }
          case QMessageBox::Cancel:
            {
              // Cancel was clicked
              qDebug() << "CANCEL";
              break;
            }
          default:
              // should never be reached
              break;
        }
    } else {
        event->accept();
    }
}

void
OmegaWindow::showEvent( QShowEvent * event )
{
  //loader->hide();
  //loader->deleteLater();
}

void OmegaWindow::on__preview_entities_clicked()
{
    if(ui->entities->isVisible())
        ui->entities->hide();
    else
        ui->entities->show();
}

void OmegaWindow::on__p_tree_entities_clicked()
{
    if(ui->treeWidget->isVisible())
        ui->treeWidget->hide();
    else
        ui->treeWidget->show();
}

void
OmegaWindow::hideWidgetArea( void )
{
    ui->scrollArea->hide();
    ui->treeWidget->adjustSize();
    OgreManager::getInstance()->selectScene("EditScenary");
}

void
OmegaWindow::hideBigWidgetArea( void )
{
    ui->bigScrollArea->hide();
}

void
OmegaWindow::UpdateWidgets( OmgEntity *p_entity )
{
    ui->treeWidget->UpdateTree( p_entity );
    ui->entities->Update(p_entity);
}

void
OmegaWindow::UpdateWidgets( )
{
    ui->treeWidget->UpdateTree( );
    ui->entities->Update();
}

void
OmegaWindow::deselectCurrentObj( void )
{
    ui->entities->deselectItem();
}

void OmegaWindow::on_actionNew_Folder_triggered()
{
    QOmgFolderDialog* p_folder = new QOmgFolderDialog( this );

    int w = p_folder->size().width();
    ui->treeWidget->setMaximumWidth(w);
    ui->scrollArea->setMaximumSize(p_folder->size());
    ui->treeWidget->setMinimumWidth(w);
    ui->scrollArea->setWidget(p_folder);
    ui->scrollArea->show();
    connect(p_folder,SIGNAL(HideInputData()),this,SLOT(hideWidgetArea()));
}

void OmegaWindow::on_actionEdit_Folder_triggered( OmgFolder* ap_folder )
{
    QOmgFolderDialog* p_folder = new QOmgFolderDialog( ap_folder, this );

    int w = p_folder->size().width();
    ui->treeWidget->setMaximumWidth(w);
    ui->scrollArea->setMaximumSize(p_folder->size());
    ui->treeWidget->setMinimumWidth(w);
    ui->scrollArea->setWidget(p_folder);
    ui->scrollArea->show();
    connect(p_folder,SIGNAL(HideInputData()),this,SLOT(hideWidgetArea()));
}

void OmegaWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int /*column*/)
{
    QOmgLeaf *leaf = dynamic_cast<QOmgLeaf*>(item);

    switch( leaf->GetLeafType() )
    {
    case Omega::EnemyLeaf:
    {
        OmgEnemy* p_enemy = OmgEnemyContainer::Instance()->getEnemy(leaf->GetLeafName());

        if(p_enemy)
            on_actionEdit_Enemy_triggered( p_enemy );
        else
            on_actionNew_Enemy_triggered( );
    break;
    }
    case Omega::PlayerLeaf:
    {
        OmgPlayer* p_player = OmgPlayerContainer::Instance()->getPlayer(leaf->GetLeafName());

        if(p_player)
            on_actionEdit_Player_triggered( p_player );
        else
            on_actionNew_Player_triggered();
    break;
    }
    case Omega::WeaponLeaf:
    {
        OmgWeapon *pWeapon = OmgWeaponsContainer::Instance()->getWeapon(leaf->GetLeafName());
        if( pWeapon )
        {
            on_actionEdit_Weapon_triggered( pWeapon );
        }
        else
        {
            on_actionNew_Weapon_triggered();
        }
        break;
    }
    case Omega::FolderLeaf:
    {
        OmgFolder* p_folder = OmgFoldersMngr::Instance()->getFolder(leaf->GetLeafName());

        if(p_folder)
        {
            on_actionEdit_Folder_triggered(p_folder);
        } else {
            on_actionNew_Folder_triggered();
        }

    break;
    }
    case Omega::SceneObjLeaf:
    {
        OmgSceneObj *pObject = OmgSceneObjContainer::Instance()->getSceneObj(leaf->GetLeafName());
        if(pObject)
        {
            MouseScenaryEdit * mouseEdit = dynamic_cast<MouseScenaryEdit*>(InputManager::getInstance()->getController("EditScenary"));

            if(mouseEdit)
            {
              // Avoid future headaches
                QString objectName = QString().fromStdString(mouseEdit->currentObjectName()).remove("0");
                if( pObject->getName() == objectName )
                    deselectCurrentObj();
            }
            on_actionEdit_Scene_Object_triggered( pObject );
        }
        else
            on_actionNew_Scene_Object_triggered();
        break;
    }
    case Omega::ItemLeaf:  
    {
        OmgItem* pItem = OmgItemContainer::Instance()->getItem(leaf->GetLeafName());

        if(pItem)
            on_actionEdit_Item_triggered( pItem );
        else
            on_actionNew_Item_triggered();
        break;
    }
    case Omega::MapLeaf:  
      {
        OmgMap* pMap = OmgMapContainer::Instance()->getMap(leaf->GetLeafName());

        if(pMap)
          on_actionEdit_Map_triggered(pMap);
        else
          on_actionNew_Map_triggered();
        break;
      }
    case Omega::GameLeaf:  
      {
        OmgGame* pGame = OmgGameContainer::Instance()->getGame( leaf->GetLeafName());

        if(pGame)
          on_actionEditGame_triggered(pGame);
        else
          on_actionNewGame_triggered();
        break;
      }
    }
}

void
OmegaWindow::on_actionEditGame_triggered( OmgGame* apGame )
{
  QOmgGameCreatorDialog* pGame = new QOmgGameCreatorDialog( apGame, this );

  ui->bigScrollArea->setMaximumWidth(pGame->size().width());
  ui->bigScrollArea->setWidget(pGame);
  ui->bigScrollArea->show();
  connect( pGame, SIGNAL(hideInputData()),this, SLOT(hideBigWidgetArea()));
}


void
OmegaWindow::on_actionEdit_Map_triggered( OmgMap* apMap )
{
  QOmgMapDialog *pMap = new QOmgMapDialog( apMap, this );

  int w = pMap->size().width();
  ui->treeWidget->setMaximumWidth(w);
  ui->scrollArea->setMaximumSize( pMap->size());
  ui->treeWidget->setMinimumWidth(w);
  ui->scrollArea->setWidget(pMap);
  ui->scrollArea->show();
  connect( pMap,SIGNAL(hideInputData()),this,SLOT(hideWidgetArea()));
}


void
OmegaWindow::on_actionNew_Item_triggered()
{
    QOmgItemDialog* pItem = new QOmgItemDialog( 0, this );

    int w = pItem->size().width();
    ui->treeWidget->setMaximumWidth(w);
    ui->scrollArea->setMaximumSize(pItem->size());
    ui->treeWidget->setMinimumWidth(w);
    ui->scrollArea->setWidget(pItem);
    ui->scrollArea->show();
    connect(pItem,SIGNAL( hideInputData() ),this,SLOT(hideWidgetArea()));
}

void
OmegaWindow::on_actionEdit_Item_triggered( OmgItem* aItem )
{
    QOmgItemDialog* pItem = new QOmgItemDialog( aItem, this );

    int w = pItem->size().width();
    ui->treeWidget->setMaximumWidth(w);
    ui->scrollArea->setMaximumSize(pItem->size());
    ui->treeWidget->setMinimumWidth(w);
    ui->scrollArea->setWidget(pItem);
    ui->scrollArea->show();
    connect(pItem,SIGNAL( hideInputData() ),this,SLOT(hideWidgetArea()));
}

void
OmegaWindow::on_actionNew_Scene_Object_triggered()
{
    QOmgSceneObjectsDialog* pObject = new QOmgSceneObjectsDialog( this );

    int w = pObject->size().width();
    ui->treeWidget->setMaximumWidth(w);
    ui->scrollArea->setMaximumSize(pObject->size());
    ui->treeWidget->setMinimumWidth(w);
    ui->scrollArea->setWidget(pObject);
    ui->scrollArea->show();
    connect(pObject,SIGNAL(HideInputData()),this,SLOT(hideWidgetArea()));
}

void
OmegaWindow::on_actionEdit_Scene_Object_triggered( OmgSceneObj* apObject )
{
    QOmgSceneObjectsDialog* pObject = new QOmgSceneObjectsDialog( apObject, this );

    int w = pObject->size().width();
    ui->treeWidget->setMaximumWidth(w);
    ui->scrollArea->setMaximumSize(pObject->size());
    ui->treeWidget->setMinimumWidth(w);
    ui->scrollArea->setWidget(pObject);
    ui->scrollArea->show();
    connect(pObject,SIGNAL(HideInputData()),this,SLOT(hideWidgetArea()));
}

void
OmegaWindow::on_actionExport_To_Omg_triggered( void )
{
    QOmgExporterDialog* pExporter = new QOmgExporterDialog( this );

    int w = pExporter->size().width();
    ui->treeWidget->setMaximumWidth(w);
    ui->scrollArea->setMaximumSize(pExporter->size());
    ui->treeWidget->setMinimumWidth(w);
    ui->scrollArea->setWidget(pExporter);
    ui->scrollArea->show();
    connect(pExporter,SIGNAL(HideInputData()),this,SLOT(hideWidgetArea()));
}

void OmegaWindow::on_actionExit_triggered()
{
    close();
}

void OmegaWindow::on_actionSave_triggered()
{
    OmgSaverMngr::Instance()->saveAll();
}

void OmegaWindow::on_actionNew_Weapon_triggered()
{
    QOmgWeaponsDialog *pWeapon = new QOmgWeaponsDialog( this );

    int w = pWeapon->size().width();
    ui->treeWidget->setMaximumWidth(w);
    ui->scrollArea->setMaximumSize(pWeapon->size());
    ui->treeWidget->setMinimumWidth(w);
    ui->scrollArea->setWidget(pWeapon);
    ui->scrollArea->show();
    connect(pWeapon,SIGNAL(hideInputData()),this,SLOT(hideWidgetArea()));
}

void
OmegaWindow::on_actionEdit_Weapon_triggered( OmgWeapon* aWeapon )
{
    QOmgWeaponsDialog *pWeapon = new QOmgWeaponsDialog( aWeapon, this );

    int w = pWeapon->size().width();
    ui->treeWidget->setMaximumWidth(w);
    ui->scrollArea->setMaximumSize( pWeapon->size());
    ui->treeWidget->setMinimumWidth(w);
    ui->scrollArea->setWidget(pWeapon);
    ui->scrollArea->show();
    connect( pWeapon,SIGNAL(hideInputData()),this,SLOT(hideWidgetArea()));
}

void OmegaWindow::on_actionNew_Map_triggered()
{
    QOmgMapDialog *pMap = new QOmgMapDialog( this );

    int w = pMap->size().width();
    ui->treeWidget->setMaximumWidth(w);
    ui->scrollArea->setMaximumSize( pMap->size());
    ui->treeWidget->setMinimumWidth(w);
    ui->scrollArea->setWidget(pMap);
    ui->scrollArea->show();
    connect( pMap,SIGNAL(hideInputData()),this,SLOT(hideWidgetArea()));
}

void OmegaWindow::on_actionNewGame_triggered()
{
    QOmgGameCreatorDialog* pGame = new QOmgGameCreatorDialog( this );

    ui->bigScrollArea->setMaximumWidth(pGame->size().width());
    ui->bigScrollArea->setWidget(pGame);
    ui->bigScrollArea->show();
    connect(pGame,SIGNAL(hideInputData()),this,SLOT(hideBigWidgetArea()));
}

void
OmegaWindow::showCharacterPartsSelector( void )
{
  CharacterPartsSelectorWidget *pCharacterSelector =  new CharacterPartsSelectorWidget( this );

  ui->bigScrollArea->setMaximumWidth(pCharacterSelector->size().width());
  ui->bigScrollArea->setWidget(pCharacterSelector);
  ui->bigScrollArea->show();

}

void
OmegaWindow::hideCharacterPartsSelector( void )
{
  ui->bigScrollArea->hide();
}

void
OmegaWindow::showEditScenearyWidget()
{
  ui->entities->show();
}

void
OmegaWindow::hideEditScenearyWidget()
{
  ui->entities->hide();
}