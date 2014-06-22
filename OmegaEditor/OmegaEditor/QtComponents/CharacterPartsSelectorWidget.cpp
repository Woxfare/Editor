#include "CharacterPartsSelectorWidget.h"
#include "ui_CharacterPartsSelectorWidget.h"
#include "EditionManagers/EditCharacterManager.h"

CharacterPartsSelectorWidget::CharacterPartsSelectorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CharacterPartsSelectorWidget)
{
    ui->setupUi(this);

    bodyVisible     = true;
    headVisible     = true;
    legLeftVisible  = true;
    legRightVisible = true;
    armLeftVisible  = true;
    armRightVisible = true;

    pushedStyle = QString("QPushButton  {"
                          "border: 2px solid black;"
                          "background-color: #FF6666 "
                      "}");

    noPushedStyle = QString("QPushButton  {"
                          "border: 2px solid black;"
                          "background-color: white "
                      "}");

    ui->head->setStyleSheet( pushedStyle );
    ui->body->setStyleSheet( pushedStyle );
    ui->rightArm->setStyleSheet( pushedStyle );
    ui->rightLeg->setStyleSheet( pushedStyle );
    ui->leftArm->setStyleSheet( pushedStyle );
    ui->leftLeg->setStyleSheet( pushedStyle );

    ShowSelectedParts();
}

CharacterPartsSelectorWidget::~CharacterPartsSelectorWidget()
{
    delete ui;
}

void
CharacterPartsSelectorWidget::ShowSelectedParts( void )
{
    std::vector< characterParts > parts;

    if( headVisible )
        parts.push_back( head );

    if( bodyVisible )
    parts.push_back( body );

    if( armRightVisible )
        parts.push_back( armRight );

    if( armLeftVisible )
        parts.push_back( armLeft );

    if( legLeftVisible )
        parts.push_back( legLeft );

    if( legRightVisible )
        parts.push_back( legRight );

    EditCharacterManager::getInstance()->setPartsToShow( parts );
}

void
CharacterPartsSelectorWidget::on_head_clicked()
{
    if( headVisible )
    {
        ui->head->setStyleSheet( noPushedStyle );
        headVisible = false;
    } else {
        ui->head->setStyleSheet( pushedStyle );
        headVisible = true;
    }

    ShowSelectedParts();
}

void
CharacterPartsSelectorWidget::on_body_clicked()
{
    if( bodyVisible )
    {
        ui->body->setStyleSheet( noPushedStyle );
        bodyVisible = false;
    } else {
        ui->body->setStyleSheet( pushedStyle );
        bodyVisible = true;
    }

    ShowSelectedParts();
}

void
CharacterPartsSelectorWidget::on_rightArm_clicked()
{
    if( armRightVisible )
    {
        ui->rightArm->setStyleSheet( noPushedStyle );
        armRightVisible = false;
    } else {
        ui->rightArm->setStyleSheet( pushedStyle );
        armRightVisible = true;
    }

    ShowSelectedParts();
} 



void CharacterPartsSelectorWidget::on_leftArm_clicked()
{
    if( armLeftVisible )
    {
        ui->leftArm->setStyleSheet( noPushedStyle );
        armLeftVisible = false;
    } else {
        ui->leftArm->setStyleSheet( pushedStyle );
        armLeftVisible = true;
    }

    ShowSelectedParts();
}

void CharacterPartsSelectorWidget::on_rightLeg_clicked()
{
    if( legRightVisible )
    {
        ui->rightLeg->setStyleSheet( noPushedStyle );
        legRightVisible = false;
    } else {
        ui->rightLeg->setStyleSheet( pushedStyle );
        legRightVisible = true;
    }

    ShowSelectedParts();
}

void CharacterPartsSelectorWidget::on_leftLeg_clicked()
{
    if( legLeftVisible )
    {
        ui->leftLeg->setStyleSheet( noPushedStyle );
        legLeftVisible = false;
    } else {
        ui->leftLeg->setStyleSheet( pushedStyle );
        legLeftVisible = true;
    }

    ShowSelectedParts();
}
