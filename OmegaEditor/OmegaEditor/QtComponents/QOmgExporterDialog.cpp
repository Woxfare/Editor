#include "QOmgExporterDialog.h"
#include "ui_QOmgExporterDialog.h"
#include "OmgEntities/OmgSceneObjContainer.h"
#include "OmgEntities/OmgEnemyContainer.h"
#include "OmgEntities/OmgPlayerContainer.h"
#include "OmgEntities/OmgItemContainer.h"
#include "QtComponents/QOmgListWidgetItem.h"
#include "OmgEntities/OmgPlayer.h"
#include "QtComponents/QOmgStyle.h"
#include <QMessageBox>
#include <QMimeData>
#include <QFile>
#include <QTextStream>
#include <QDate>
#include "Display/OgreManager.h"
#include "Saver/EntitiesXMLWriter.h"

QOmgExporterDialog::QOmgExporterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QOmgExporterDialog)
{
    ui->setupUi(this);
    setStyleSheet(QOmgStyle::CurrentStyleSheet());
    fillListOfEntities();
    configureButtons();
    OgreManager::getInstance()->selectScene("EditScenary");
}

QOmgExporterDialog::~QOmgExporterDialog()
{
    delete ui;
}

void QOmgExporterDialog::on_pbExport_clicked()
{
    if( validate())
    {
        exportEntities();
        emit HideInputData();
        hide();
        deleteLater();
    }
}

void QOmgExporterDialog::on_pbCancel_clicked()
{
    emit HideInputData();
    hide();
    deleteLater();
}

void
QOmgExporterDialog::exportEntities(void)
{
    QList<QOmgListWidgetItem*> vItems = getSelectedEntities();

    Omega::EntityVector vEntities;
    QList<QOmgListWidgetItem*>::iterator it = vItems.begin(), itEnd = vItems.end();

    for( ; it!=itEnd; ++it )
    {
        QOmgListWidgetItem* item = (*it);

        switch(item->getType())
        {
        case Omega::Player:
            vEntities.push_back( OmgPlayerContainer::Instance()->getPlayer(item->text()));
            break;
        case Omega::Item:
            vEntities.push_back( OmgItemContainer::Instance()->getItem(item->text()));
            break;
        case Omega::SceneObj:
            vEntities.push_back( OmgSceneObjContainer::Instance()->getSceneObj(item->text()));
            break;
        case Omega::Enemy:
            vEntities.push_back( OmgEnemyContainer::Instance()->getEnemy(item->text()));
            break;

        }
    }
    saveEntitiesInFile(vEntities);
}

void
QOmgExporterDialog::saveEntitiesInFile(Omega::EntityVector avEntities)
{

    if("" == ui->fileName->text())
    {
        QMessageBox::warning(this,
                             "Error!!",
                             "Select a filename");
        return;
    }

    if( ui->fileName->text().contains( "," ) ||
        ui->fileName->text().contains( "?" ) ||
        ui->fileName->text().contains( "!" ) ||
        ui->fileName->text().contains( "¿" ) ||
        ui->fileName->text().contains( "¡" ) ||
        ui->fileName->text().contains( "<" ) ||
        ui->fileName->text().contains( ">" ) ||
        ui->fileName->text().contains( "<" ) ||
        ui->fileName->text().contains( ">" ) ||
        ui->fileName->text().contains( "#" ) ||
        ui->fileName->text().contains( "'" ) ||
        ui->fileName->text().contains( "$" ) ||
        ui->fileName->text().contains( "@" ) ||
        ui->fileName->text().contains( "%" ) )
    {
        QMessageBox::warning(this,
                             "Error!!",
                             "The FileName can not contain:  , ? , ¿, \, >, <, |, %, @, $, # ");
        return;

    }

    QString filename = ui->fileName->text() + (".omg");

    EntitiesXMLWriter( avEntities, filename );
}

bool
QOmgExporterDialog::validate( void )
{
    QList<QOmgListWidgetItem*> vItems = getSelectedEntities();
    if(ui->fileName->text() == "")
    {
        QMessageBox::warning(this,
                             "Error!!",
                             "Please write a filename...");
        return false;
    }
    if( vItems.isEmpty() )
    {
        QMessageBox::warning(this,
                             "Error!!",
                             "Please select at least one entity to export...");
        return false;
    }
    return true;
}

void
QOmgExporterDialog::fillListOfEntities( void )
{
    ui->entitiesList->setSelectionMode(QAbstractItemView::MultiSelection);

    Omega::EntityVector vPlayers = OmgPlayerContainer::Instance()->availablePlayers();
    Omega::EntityIterator it = vPlayers.begin(), itEnd = vPlayers.end();

    for(; it != itEnd ;++it)
    {
        OmgPlayer* pPlayer = dynamic_cast<OmgPlayer*>(*it);
        if(!pPlayer)
            continue;
        QOmgListWidgetItem* pItem = new QOmgListWidgetItem(QIcon(":/Media/character.png"), pPlayer->getName(), Omega::Player);

        ui->entitiesList->addItem(pItem);
    }

    Omega::EntityVector vEnemies = OmgEnemyContainer::Instance()->availableEnemies();
    it      = vEnemies.begin();
    itEnd   = vEnemies.end();

    for(; it != itEnd ;++it)
    {
        OmgEnemy* pEnemy = dynamic_cast<OmgEnemy*>(*it);
        if(!pEnemy)
            continue;
        QOmgListWidgetItem* pItem = new QOmgListWidgetItem(QIcon(":/Media/enemy.png"), pEnemy->getName(), Omega::Enemy);

        ui->entitiesList->addItem(pItem);
    }

    Omega::EntityVector vItems = OmgItemContainer::Instance()->availableItems();
    it      = vItems.begin();
    itEnd   = vItems.end();

    for(; it != itEnd ;++it)
    {
        OmgItem* pOmgItem = dynamic_cast<OmgItem*>(*it);
        if(!pOmgItem)
            continue;
        QOmgListWidgetItem* pItem = new QOmgListWidgetItem(QIcon(":/Media/item.png"), pOmgItem->getName(), Omega::Item);

        ui->entitiesList->addItem(pItem);
    }

    Omega::EntityVector vSceneObj = OmgSceneObjContainer::Instance()->GetAvailableSceneObjects();
    it      = vSceneObj.begin();
    itEnd   = vSceneObj.end();

    for(; it != itEnd ;++it)
    {
        OmgSceneObj* pSceneObj = dynamic_cast<OmgSceneObj*>(*it);
        if(!pSceneObj)
            continue;
        QOmgListWidgetItem* pItem = new QOmgListWidgetItem(QIcon(":/Media/sceneobj.png"), pSceneObj->getName(), Omega::SceneObj);

        ui->entitiesList->addItem(pItem);
    }

}

void
QOmgExporterDialog::configureButtons( void )
{
    //! Setting the first style sheet
    ui->pbBuildUpObj->setStyleSheet("QPushButton{"
                                "background-color:#585858;"
                                "border:2px solid black;"
                                "}");
    ui->pbEnemies->setStyleSheet("QPushButton{"
                                "background-color:#585858;"
                                "border:2px solid black;"
                                "}");
    ui->pbPlayers->setStyleSheet("QPushButton{"
                                "background-color:#585858;"
                                "border:2px solid black;"
                                "}");
    ui->pbItems->setStyleSheet("QPushButton{"
                                "background-color:#585858;"
                                "border:2px solid black;"
                                "}");
    ui->pbSceneObj->setStyleSheet("QPushButton{"
                                "background-color:#585858;"
                                "border:2px solid black;"
                                "}");
    ui->pbMaps->setStyleSheet("QPushButton{"
                                "background-color:#585858;"
                                "border:2px solid black;"
                                "}");
    ui->pbWeapons->setStyleSheet("QPushButton{"
                                "background-color:#585858;"
                                "border:2px solid black;"
                                "}");

    //! Make connections
    connect(ui->pbBuildUpObj, SIGNAL(clicked()),this,SLOT(on_pb_clicked()));
    connect(ui->pbEnemies, SIGNAL(clicked()),this,SLOT(on_pb_clicked()));
    connect(ui->pbPlayers, SIGNAL(clicked()),this,SLOT(on_pb_clicked()));
    connect(ui->pbItems, SIGNAL(clicked()),this,SLOT(on_pb_clicked()));
    connect(ui->pbSceneObj, SIGNAL(clicked()),this,SLOT(on_pb_clicked()));
    connect(ui->pbWeapons, SIGNAL(clicked()),this,SLOT(on_pb_clicked()));
    connect(ui->pbMaps, SIGNAL(clicked()),this,SLOT(on_pb_clicked()));

    //! Add The entities to the set
    set_entities.insert(Omega::BuildUpObj);
    set_entities.insert(Omega::Map);
    set_entities.insert(Omega::Weapon);
    set_entities.insert(Omega::Enemy);
    set_entities.insert(Omega::Player);
    set_entities.insert(Omega::Item);
    set_entities.insert(Omega::SceneObj);
}

void
QOmgExporterDialog::on_pb_clicked()
{
    std::set<Omega::EntityType>::iterator it;

    if(sender() == (QPushButton*)ui->pbBuildUpObj )
    {
        if(set_entities.count(Omega::BuildUpObj) != 0)
        {
            it = set_entities.find(Omega::BuildUpObj);
            set_entities.erase(it);
            ui->pbBuildUpObj->setStyleSheet(QOmgStyle::CurrentStyleSheet());

        } else {
            ui->pbBuildUpObj->setStyleSheet("QPushButton{"
                                        "background-color:#585858;"
                                        "border:2px solid black;"
                                        "}");
            set_entities.insert(Omega::BuildUpObj);
        }
    }
    if(sender() == (QPushButton*)ui->pbEnemies )
    {
        if(set_entities.count(Omega::Enemy) != 0)
        {
            it = set_entities.find(Omega::Enemy);
            set_entities.erase(it);
            ui->pbEnemies->setStyleSheet(QOmgStyle::CurrentStyleSheet());

        } else {
            ui->pbEnemies->setStyleSheet("QPushButton{"
                                        "background-color:#585858;"
                                        "border:2px solid black;"
                                        "}");
            set_entities.insert(Omega::Enemy);
        }
    }
    if(sender() == (QPushButton*)ui->pbPlayers )
    {
        if(set_entities.count(Omega::Player) != 0)
        {
            it = set_entities.find(Omega::Player);
            set_entities.erase(it);
            ui->pbPlayers->setStyleSheet(QOmgStyle::CurrentStyleSheet());

        } else {
            ui->pbPlayers->setStyleSheet("QPushButton{"
                                        "background-color:#585858;"
                                        "border:2px solid black;"
                                        "}");
            set_entities.insert(Omega::Player);
        }
    }
    if(sender() == (QPushButton*)ui->pbItems )
    {
        if(set_entities.count(Omega::Item) != 0)
        {
            it = set_entities.find(Omega::Item);
            set_entities.erase(it);
            ui->pbItems->setStyleSheet(QOmgStyle::CurrentStyleSheet());

        } else {
            ui->pbItems->setStyleSheet("QPushButton{"
                                        "background-color:#585858;"
                                        "border:2px solid black;"
                                        "}");
            set_entities.insert(Omega::Item);
        }
    }
    if(sender() == (QPushButton*)ui->pbSceneObj )
    {
        if(set_entities.count(Omega::SceneObj) != 0)
        {
            it = set_entities.find(Omega::SceneObj);
            set_entities.erase(it);
            ui->pbSceneObj->setStyleSheet(QOmgStyle::CurrentStyleSheet());

        } else {
            ui->pbSceneObj->setStyleSheet("QPushButton{"
                                        "background-color:#585858;"
                                        "border:2px solid black;"
                                        "}");
            set_entities.insert(Omega::SceneObj);
        }
    }
    if(sender() == (QPushButton*)ui->pbWeapons )
    {
        if(set_entities.count(Omega::Weapon) != 0)
        {
            it = set_entities.find(Omega::Weapon);
            set_entities.erase(it);
            ui->pbWeapons->setStyleSheet(QOmgStyle::CurrentStyleSheet());

        } else {
            ui->pbWeapons->setStyleSheet("QPushButton{"
                                        "background-color:#585858;"
                                        "border:2px solid black;"
                                        "}");
            set_entities.insert(Omega::Weapon);
        }
    }
    if(sender() == (QPushButton*)ui->pbMaps )
    {
        if(set_entities.count(Omega::Map) != 0)
        {
            it = set_entities.find(Omega::Map);
            set_entities.erase(it);
            ui->pbMaps->setStyleSheet(QOmgStyle::CurrentStyleSheet());

        } else {
            ui->pbMaps->setStyleSheet("QPushButton{"
                                        "background-color:#585858;"
                                        "border:2px solid black;"
                                        "}");
            set_entities.insert(Omega::Map);
        }
    }

    //! An update is needed
    updateListOfEntities();
}

void
QOmgExporterDialog::updateListOfEntities( void )
{
    for(int row = 0; row < ui->entitiesList->count(); row++)
    {
        QOmgListWidgetItem* pItem = dynamic_cast<QOmgListWidgetItem*>(ui->entitiesList->item(row));

        if(!pItem)
            continue;

        if( set_entities.count(pItem->getType()) != 0)
            pItem->setHidden(false);
        else
            pItem->setHidden(true);
    }
}

QList<QOmgListWidgetItem*>
QOmgExporterDialog::getSelectedEntities( void )
{
    QList<QOmgListWidgetItem*> vItems;
    for(int row = 0; row < ui->entitiesList->count(); row++)
    {
        QOmgListWidgetItem* pItem = dynamic_cast<QOmgListWidgetItem*>(ui->entitiesList->item(row));

        if(!pItem)
            continue;
        if(!pItem->isSelected())
            continue;
        if( set_entities.count(pItem->getType()) != 0)
            vItems.push_back(pItem);
    }

    return vItems;
}
