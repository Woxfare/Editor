#include "CharacterPartsSelectorWidget.h"
#include "ui_CharacterPartsSelectorWidget.h"


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
    clearSelector();

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
		ui->head->setIcon(QIcon());
        headVisible = false;
    } else {
        ui->head->setStyleSheet( pushedStyle );
		ui->head->setIcon(_map_icons_parts[head]);
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
		ui->body->setIcon(QIcon());
        bodyVisible = false;
    } else {
        ui->body->setStyleSheet( pushedStyle );
		ui->body->setIcon(_map_icons_parts[body]);
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
		ui->rightArm->setIcon(QIcon());
        armRightVisible = false;
    } else {
        ui->rightArm->setStyleSheet( pushedStyle );
		ui->rightArm->setIcon(_map_icons_parts[armRight]);
        armRightVisible = true;
    }

    ShowSelectedParts();
} 



void CharacterPartsSelectorWidget::on_leftArm_clicked()
{
    if( armLeftVisible )
    {
        ui->leftArm->setStyleSheet( noPushedStyle );
		ui->leftArm->setIcon(QIcon());
        armLeftVisible = false;
    } else {
        ui->leftArm->setStyleSheet( pushedStyle );
		ui->leftArm->setIcon(_map_icons_parts[armLeft]);
        armLeftVisible = true;
    }

    ShowSelectedParts();
}

void CharacterPartsSelectorWidget::on_rightLeg_clicked()
{
    if( legRightVisible )
    {
        ui->rightLeg->setStyleSheet( noPushedStyle );
		ui->rightLeg->setIcon(QIcon());
        legRightVisible = false;
    } else {
        ui->rightLeg->setStyleSheet( pushedStyle );
		ui->rightLeg->setIcon(_map_icons_parts[legRight]);
        legRightVisible = true;
    }

    ShowSelectedParts();
}

void CharacterPartsSelectorWidget::on_leftLeg_clicked()
{
    if( legLeftVisible )
    {
        ui->leftLeg->setStyleSheet( noPushedStyle );
		ui->leftLeg->setIcon(QIcon());
        legLeftVisible = false;
    } else {
        ui->leftLeg->setStyleSheet( pushedStyle );
		ui->leftLeg->setIcon(_map_icons_parts[legLeft]);
        legLeftVisible = true;
    }

    ShowSelectedParts();
}

void
CharacterPartsSelectorWidget::changeTextureOfPart( characterParts part, QString textureName )
{
	switch( part )
	{
	case head:
		{
			if(headVisible)
			{
				QPixmap texture( "Resources/materials/textures/" + textureName  );
				texture = texture.scaled( QSize( ui->head->width() - 2, ui->head->height()-2 ), Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
				QIcon icon( texture );
				_map_icons_parts[part] = icon;
				ui->head->setIcon(texture);
			}
		}
		break;
	case body:
		{
			if(bodyVisible)
			{
				QPixmap texture( "Resources/materials/textures/" + textureName  );
				texture = texture.scaled( QSize( ui->body->width() - 2, ui->body->height()-2 ), Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
				QIcon icon( texture );
				_map_icons_parts[part] = icon;
				ui->body->setIcon(texture);
			}
		}
		break;
	case legLeft:
		{
			if(legLeftVisible)
			{
				QPixmap texture( "Resources/materials/textures/" + textureName  );
				texture = texture.scaled( QSize( ui->leftLeg->width() - 2, ui->leftLeg->height()-2 ), Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
				QIcon icon( texture );
				_map_icons_parts[part] = icon;
				ui->leftLeg->setIcon(texture);
			}
		}
		break;
	case legRight:
		{
			if(legRightVisible)
			{
				QPixmap texture( "Resources/materials/textures/" + textureName  );
				texture = texture.scaled( QSize( ui->rightLeg->width() - 2, ui->rightLeg->height()-2 ), Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
				QIcon icon( texture );
				_map_icons_parts[part] = icon;
				ui->rightLeg->setIcon(texture);
			}
		}
		break;
	case armLeft:
		{
			if(armLeftVisible)
			{
				QPixmap texture( "Resources/materials/textures/" + textureName  );
				texture = texture.scaled( QSize( ui->leftArm->width() - 2, ui->leftArm->height()-2 ), Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
				QIcon icon( texture );
				_map_icons_parts[part] = icon;
				ui->leftArm->setIcon(texture);
			}
		}
		break;
	case armRight:
		{
			if(armRightVisible)
			{
				QPixmap texture( "Resources/materials/textures/" + textureName  );
				texture = texture.scaled( QSize( ui->rightArm->width() - 2, ui->rightArm->height()-2 ), Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
				QIcon icon( texture );
				_map_icons_parts[part] = icon;
				ui->rightArm->setIcon(texture);
			}
		}
		break;
	}
}

void
CharacterPartsSelectorWidget::clearSelector()
{
  _map_icons_parts[head]		= QIcon();
  _map_icons_parts[body]		= QIcon();
  _map_icons_parts[legLeft]	= QIcon();
  _map_icons_parts[armLeft]	= QIcon();
  _map_icons_parts[legRight]	= QIcon();
  _map_icons_parts[legLeft]	= QIcon();
  changeTextureOfPart( head, "" );
  changeTextureOfPart( body,"" );
  changeTextureOfPart( legLeft, "" );
  changeTextureOfPart( armLeft, "" );
  changeTextureOfPart( legRight, "" );
  changeTextureOfPart( legLeft, "" );
}