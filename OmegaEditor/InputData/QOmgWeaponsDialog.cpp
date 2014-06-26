#include "QOmgWeaponsDialog.h"
#include "ui_QOmgWeaponsDialog.h"
#include "OmgEntities/OmgWeapon.h"
#include "OmgEntities/OmgWeaponsContainer.h"
#include "QOmgStyle.h"
#include "QColorButton.h"
#include <QListWidgetItem>
#include <qmessagebox.h>
#include "QOmgWindowMngr.h"
#include "Utils/OgreManager.h"
#include "Saver/OmgSaverMngr.h"
#include "Folders/OmgFoldersMngr.h"
#include <QDebug>
#include "Utils/OgreManager.h"

QOmgWeaponsDialog::QOmgWeaponsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QOmgWeaponsDialog)
{
    ui->setupUi(this);
    _weapon = new OmgWeapon( "WeaponName", "DefaultWeapons");
    putWeaponInQt();
    setStyleSheet(QOmgStyle::CurrentStyleSheet());
    ui->_editWeapon->hide();
    OgreManager::getInstance()->selectScene("EditScenary");
    editingTextures = false;
}

QOmgWeaponsDialog::QOmgWeaponsDialog( OmgWeapon *aWeapon, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QOmgWeaponsDialog)
{

    qDebug() << "Editando weapon" << aWeapon->getName();

    //ui->setupUi(this);
    _weapon = aWeapon;
    ui->setupUi(this);
    putWeaponInQt();
    setStyleSheet(QOmgStyle::CurrentStyleSheet());
    ui->_newWeapon->hide();
}

QOmgWeaponsDialog::~QOmgWeaponsDialog()
{
    delete ui;
}

void
QOmgWeaponsDialog::putWeaponInQt( void )
{
    qDebug() << "Setting weapon name";
    ui->_name->setText(_weapon->getName());

    qDebug() << "Setting folder";
    Omega::FolderVector v_folders = OmgFoldersMngr::Instance()->getAvailableFolders( Omega::WeaponFolder );

    std::vector<OmgFolder*>::iterator it = v_folders.begin(), it_end = v_folders.end();

    for(; it != it_end; ++it)
    {
        OmgFolder* p_folder = (*it);

        ui->folderList->addItem(new QListWidgetItem(QIcon(":/OmegaEditor/Resources/Icons/folder.png"), p_folder->getName()));
    }

    ui->folderList->setCurrentItem(findFolderItemByName( _weapon->getFolderName() ));

    qDebug() << "Setting bullets";
    ui->bulletSpin->setValue(_weapon->getDefaultBullets());

    qDebug() << "Setting color";
    QColorButton *colorButton = dynamic_cast<QColorButton*>(ui->widget);
    colorButton->changeColor(_weapon->getColor());

    qDebug() << "Setting type";
    switch( _weapon->getWeaponType() )
    {
        case Omega::SimpleShot:
        {
            ui->cbTypeWeapon->setCurrentIndex(0);
            qDebug() << "Simple Shot";
        }
        break;
        case Omega::BlastShot:
        {
            ui->cbTypeWeapon->setCurrentIndex(1);
            qDebug() << "Blast Shot";
        }
        break;
        case Omega::MultiShot:
        {
            ui->cbTypeWeapon->setCurrentIndex(2);
            qDebug() << "Multi Shot";
        }
        break;
    }

	ui->_damageSpin->setValue( _weapon->getDamage() );
}

bool
QOmgWeaponsDialog::validate( void )
{
    QString name = ui->_name->text();

    if( name == "" )
    {
        QMessageBox::warning(this,
                             "Error!!",
                             "Select a name for the Weapon");
        return false;
    }

    if( name == "WeaponName" )
    {
        QMessageBox::warning(this,
                             "Error!!",
                             "Please select another name for the weapon instead WeaponName");
        return false;
    }

    QListWidgetItem * p_item = ui->folderList->currentItem();

    if(p_item)
        _folder = p_item->text();
    else
        _folder = "";

    if( _folder == "")
    {
        QMessageBox::warning(this,
                             "Error!!",
                             "Select a folder to store the Weapon");
        return false;
    }

    if( ui->bulletSpin->value() == 0 )
    {
        QMessageBox::warning(this,
                             "Error!!",
                             "Select a default number of bullets for the weapon");
        return false;
    }

    return true;
}

void QOmgWeaponsDialog::on__newWeapon_clicked()
{
    if( validate() )
    {
        if ( OmgWeaponsContainer::Instance()->getWeapon(ui->_name->text()) )
        {
            QMessageBox::warning(this,"Error!!","The weapon already exist!!");
            return;
        }
        storeAndFinnish(createWeapon());
    }
}

void QOmgWeaponsDialog::on__editWeapon_clicked()
{
    if( validate() )
    {
        OmgWeaponsContainer::Instance()->deleteWeapon(_weapon->getName());
        delete _weapon;
        storeAndFinnish(createWeapon());
    }
}

Omega::WeaponType
QOmgWeaponsDialog::getWeaponTypeFromQt( void )
{
    if(ui->cbTypeWeapon->currentText().contains("Simple"))
        return Omega::SimpleShot;

    if( ui->cbTypeWeapon->currentText().contains("Multi"))
        return Omega::MultiShot;

    if( ui->cbTypeWeapon->currentText().contains("Blast"))
        return Omega::BlastShot;

    return Omega::SimpleShot;
}

QListWidgetItem*
QOmgWeaponsDialog::findFolderItemByName(QString aName)
{
    QList<QListWidgetItem*> vItems = ui->folderList->findItems(aName, Qt::MatchCaseSensitive );

    if(vItems.isEmpty())
        return NULL;

    return vItems.first();
}

void
QOmgWeaponsDialog::storeAndFinnish(OmgWeapon *aWeapon)
{
    OmgWeaponsContainer::Instance()->addWeapon(aWeapon);
    QOmgWindowMngr::Instance()->GetMainWindow()->UpdateWidgets(aWeapon);
    OmgSaverMngr::Instance()->addEntityToSave(aWeapon);
    if(editingTextures)
        OgreManager::getInstance()->selectScene("EditScenary");
    emit hideInputData();
    hide();
    deleteLater();
}

OmgWeapon*
QOmgWeaponsDialog::createWeapon( void )
{
    OmgWeapon *newWeapon = new OmgWeapon( ui->_name->text(), ui->folderList->currentItem()->text() );
    QColorButton *colorButton = dynamic_cast<QColorButton*>(ui->widget);
    newWeapon->setColor( colorButton->getSelectedColor() );
    newWeapon->setWeaponType( getWeaponTypeFromQt());
    newWeapon->setDefaultBullets(ui->bulletSpin->value());
	newWeapon->setDamage( ui->_damageSpin->value());
    return newWeapon;
}
