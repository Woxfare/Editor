#include "QColorButton.h"
#include "ui_QColorButton.h"
#include <QColor>
#include <qDebug>
#include <QColorDialog>
#include "Display/OgreManager.h"
#include "EditionManagers/EditSceneManager.h"
#include "EditionManagers/EditCharacterManager.h"
#include "EditionManagers/EditCubeManager.h"

QColorButton::QColorButton(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QColorButton)
{
    ui->setupUi(this);
}

QColorButton::~QColorButton()
{
    delete ui;
}

void QColorButton::on_colorButton_clicked()
{
    QColorDialog *pColorDialog = new QColorDialog();

    pColorDialog->show();

    connect(pColorDialog,SIGNAL(colorSelected(QColor)),this,SLOT(on_colorChanged(QColor)));
}

void
QColorButton::setEditionMode(editionMode mode)
{
    edMode = mode;
}

void
QColorButton::on_colorChanged(QColor aColor)
{
    _color = aColor;
    QString style = ("background-color:rgb(") + QString("%1").arg(aColor.red())+ QString(",%1").arg(aColor.green()) +  QString(",%1").arg(aColor.blue())  + (");");
    ui->prewiewColor->setStyleSheet(style);

    int rgb[3] ={_color.red(), _color.green(), _color.blue()};

    switch(edMode)
    {
        case SCENARY:
        {
            EditSceneManager::getInstance()->changeBasePlaneColor(rgb);
            break;
        }
        case CUBE:
        {
            EditCubeManager::getInstance()->changeEditCubeColor(rgb);
            break;
        }
        case CHARACTER:
           EditCharacterManager::getInstance()->changeCharacterColor(rgb);
        break;
    }
}

QColor
QColorButton::getSelectedColor( void )
{
    return _color;
}

void
QColorButton::changeColor(QColor aColor)
{
    QString style = ("background-color:rgb(") + QString("%1").arg(aColor.red())+ QString(",%1").arg(aColor.green()) +  QString(",%1").arg(aColor.blue())  + (");");
    ui->prewiewColor->setStyleSheet(style);
    _color = aColor;
}
