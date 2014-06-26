 #include "QOmgListItem.h"
#include "ui_QOmgListItem.h"
#include <QIcon>
#include <QString>
#include "OmgEntities/OmgSceneObj.h"
#include "OmgEntities/OmgSceneObjContainer.h"
#include "Input/InputManager.h"
#include "Input/MouseScenaryEdit.h"
#include "QOmgStyle.h"
#include <QDrag>
#include <QMimeData>
#include <QByteArray>
#include <QDataStream>

#include <QDebug>

QOmgListItem::QOmgListItem(QString a_name , QPixmap a_pix, Omega::EntityType a_type, QWidget *parent ) :
    QWidget(parent),
    ui(new Ui::QOmgListItem)
{
    _isSelected = false;
    ui->setupUi(this);
    ui->_name->setText(a_name);
    _name = a_name;
    ui->pushButton->setIcon(QIcon(a_pix));
    _type = a_type;

    setStyleSheet(QOmgStyle::CurrentStyleSheet());

}

QOmgListItem::~QOmgListItem()
{
    delete ui;
}

QString
QOmgListItem::GetName( void )
{
    return _name;
}

Omega::EntityType
QOmgListItem::GetItemType( void )
{
    return _type;
}

void QOmgListItem::deselectItem()
{
    _isSelected = false;
    ui->pushButton->setStyleSheet(QOmgStyle::CurrentStyleSheet());
}

void QOmgListItem::on_pushButton_clicked()
{
    if(_isSelected)
    {
        _isSelected = false;
        ui->pushButton->setStyleSheet(QOmgStyle::CurrentStyleSheet());
    } else {
        _isSelected = true;
        ui->pushButton->setStyleSheet("QPushButton{"
                                      "background-color:#585858;"
                                      "border:2px solid black;"
                                      "}");
    }
    emit ItemSelected(this);
}
void
QOmgListItem::setPixmap(QPixmap aPix)
{
    ui->pushButton->setIcon(QIcon(aPix));
}
