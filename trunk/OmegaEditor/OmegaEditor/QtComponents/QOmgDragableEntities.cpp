#include "QOmgDragableEntities.h"
#include "ui_QOmgDragableEntities.h"
#include "QOmgListItem.h"
#include <QScrollArea>
#include <QFrame>
#include "OmgEntities/OmgSceneObjContainer.h"
#include "Omega.h"
#include "QOmgStyle.h"
#include "Input/InputManager.h"
#include "Input/MouseScenaryEdit.h"
#include <QDebug>

QOmgDragableEntities::QOmgDragableEntities(QWidget *parent) :  QWidget(parent), ui(new Ui::QOmgDragableEntities)
{
    ui->setupUi(this);
    setStyleSheet(QOmgStyle::CurrentStyleSheet());

    _p_list_widget = new QVBoxLayout(this);

    // Clear all vectors
    _v_hide_items.clear();
    _v_show_items.clear();
    _v_items.clear();

    viewport = new QWidget();
    viewport->setLayout(_p_list_widget);

    ui->scrollArea->setWidget(viewport);

    // ---------------------------------- Scene Objects ----------------------------------- //
    Omega::ListItemVector v_items = OmgSceneObjContainer::Instance()->GetAvailableSceneItems();

    Omega::ListItemIterator it = v_items.begin(), it_end = v_items.end();

    for(; it != it_end; ++it)
    {
        QOmgListItem* p_item = (*it);

        p_item->setPixmap(QPixmap(":/Media/item.png"));
        QObject::connect(p_item, SIGNAL(ItemSelected(QOmgListItem*)),this, SLOT(ItemSelected(QOmgListItem*)) );
        _p_list_widget->addWidget(p_item,Qt::AlignTop);
        _v_items.push_back(p_item);
    }

    set_entities.insert(Omega::SceneObj);

    // ----------------------------------------------------------------------- //
    _p_list_widget->addItem(new QSpacerItem(10,10, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));
    ui->_counter->setText(QString("%1/ %2 Items").arg(_v_items.size()).arg(_v_items.size()));

    // Enemies door stuff
    QObject::connect( ui->_door_enemy, SIGNAL( pressed()),this, SLOT( enemyDoorButtonPressed() ) );
    _doorButtonPressed = false;

    noPushedStyle = QOmgStyle::CurrentStyleSheet();

    pushedStyle = QString("QPushButton  {"
                              "border: 2px solid black;"
                              "color: white;"
                              "background-color: black "
                            "}");
    ui->_door_enemy->setStyleSheet( noPushedStyle );

	// Player door stuff
	QObject::connect( ui->_door_player, SIGNAL( pressed()),this, SLOT( playerDoorButtonPressed() ) );
	_playerDoorButtonPressed = false;
	ui->_door_player->setStyleSheet( noPushedStyle );

    _lastItemSelected = NULL;

}

QOmgDragableEntities::~QOmgDragableEntities()
{
    delete ui;
}

void
QOmgDragableEntities::ItemSelected(QOmgListItem* item)
{
  MouseScenaryEdit * mouseController = dynamic_cast<MouseScenaryEdit *>(InputManager::getInstance()->getController("EditScenary"));
  mouseController->changeCurrentObject("");
  if( _doorButtonPressed )
  {
    ui->_door_enemy->setStyleSheet( noPushedStyle );
    _doorButtonPressed = false;
  }

  if( _playerDoorButtonPressed )
  {
	  ui->_door_player->setStyleSheet( noPushedStyle );
	  _playerDoorButtonPressed = false;
  }

  if(_lastItemSelected )
  {
      if( _lastItemSelected->GetName() == item->GetName() )
      {
          _lastItemSelected = NULL;
          return;
      }
      else
      {
          _lastItemSelected->deselectItem();
      }
  }

  _lastItemSelected = item;
  if(item->GetItemType() == Omega::SceneObj )
      mouseController->changeCurrentObject((item->GetName() + "_0").toStdString());
}
void
QOmgDragableEntities::deselectItem( void )
{
    if(_lastItemSelected)
		_lastItemSelected->deselectItem();
    _lastItemSelected = NULL;
    MouseScenaryEdit * mouseController = dynamic_cast<MouseScenaryEdit *>(InputManager::getInstance()->getController("EditScenary"));
    mouseController->changeCurrentObject("");
}

void
QOmgDragableEntities::ShowAll( void )
{
    Omega::ListItemIterator it = _v_items.begin(), it_end = _v_items.end();

    int count = 0;
    for (; it != it_end; ++it)
    {
        QOmgListItem* p_item = (*it);

        if(set_entities.count(p_item->GetItemType()) != 0 )
        {
            p_item->show();
            count++;
        }
        else
            p_item->hide();
    }

    ui->_counter->setText(QString("%1/ %2 Items").arg(count).arg(_v_items.size()));
    _v_hide_items.clear();
    _v_show_items.clear();
}

void QOmgDragableEntities::on__search_textChanged(const QString &arg1)
{
    _v_hide_items.clear();
    _v_show_items.clear();
    if(arg1 == "")
    {
        ShowAll();
    }

    Omega::ListItemIterator it = _v_items.begin(), it_end = _v_items.end();

    for(; it != it_end; ++it)
    {
        QOmgListItem* p_item = (*it);

        if( p_item->GetName().contains(arg1, Qt::CaseInsensitive)
                && (set_entities.count(p_item->GetItemType()) != 0 ))

            _v_show_items.push_back( p_item );
        else
            _v_hide_items.push_back( p_item );
    }

    Omega::ListItemIterator it_s = _v_show_items.begin(),
                            it_end_s = _v_show_items.end(),
                            it_h = _v_hide_items.begin(),
                            it_end_h = _v_hide_items.end();

    for(;it_s != it_end_s; ++it_s)
    {
        QOmgListItem* p_item = (*it_s);
        p_item->show();
    }

    for(;it_h != it_end_h; ++it_h)
    {
        QOmgListItem* p_item = (*it_h);
        p_item->hide();
    }

    viewport->adjustSize();

    ui->_counter->setText(QString("%1/ %2 Items").arg(_v_show_items.size()).arg(_v_items.size()));
}

void QOmgDragableEntities::on__update_clicked()
{
    _v_items.clear();
    _v_items = OmgSceneObjContainer::Instance()->GetAvailableSceneItems();

    Omega::ListItemIterator it = _v_items.begin(), it_end = _v_items.end();
    for (; it != it_end; ++it)
    {
        QOmgListItem* p_item = (*it);

        p_item->show();
    }

    _v_hide_items.clear();
    _v_show_items.clear();

    //! If the label was with a text..
    on__search_textChanged(ui->_search->text());
}

void
QOmgDragableEntities::Update()
{
    QString lastItemSelectedName;
    if(_lastItemSelected)
        lastItemSelectedName = _lastItemSelected->GetName();
    else
        lastItemSelectedName = "";

    //Limpiar contenido
    _v_items.clear();
    QLayoutItem * item;
    item = _p_list_widget->itemAt(0);
    while(item != NULL)
    {
        if(item->widget() != NULL)
        {
            item->widget()->hide();
            item->widget()->deleteLater();
            _p_list_widget->removeWidget(item->widget());
        }
        _p_list_widget->removeItem(item);
        item = _p_list_widget->itemAt(0);
    }
    // ---------------------------------- Scene Objects ----------------------------------- //
    Omega::ListItemVector v_items = OmgSceneObjContainer::Instance()->GetAvailableSceneItems();

    Omega::ListItemIterator it = v_items.begin(), it_end = v_items.end();

    for(; it != it_end; ++it)
    {
        QOmgListItem* p_item = (*it);
        if(p_item->GetName() != "ObjectName")
        {
            QObject::connect(p_item, SIGNAL(ItemSelected(QOmgListItem*)),this, SLOT(ItemSelected(QOmgListItem*)) );
            _p_list_widget->addWidget(p_item,Qt::AlignTop);
            _v_items.push_back(p_item);
        }
        if (p_item->GetName() == lastItemSelectedName)
            _lastItemSelected = p_item;
    }

    set_entities.insert(Omega::SceneObj);
   

    // ----------------------------------------------------------------------- //
    _p_list_widget->addItem(new QSpacerItem(10,10, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));

    ui->_counter->setText(QString("%1/ %2 Items").arg(_v_items.size()).arg(_v_items.size()));

}

void
QOmgDragableEntities::Update(OmgEntity *aEntity)
{
    Update();
}

void
QOmgDragableEntities::enemyDoorButtonPressed()
{
  MouseScenaryEdit * mouseController = dynamic_cast<MouseScenaryEdit *>( InputManager::getInstance()->getController("EditScenary") );
  if( _doorButtonPressed )
  {
    ui->_door_enemy->setStyleSheet( noPushedStyle );
    _doorButtonPressed = false;
    mouseController->changeCurrentObject("");
  }
  else
  {
    _doorButtonPressed = true;
    ui->_door_enemy->setStyleSheet( pushedStyle );
    mouseController->changeCurrentObject("Enemy_Door");
    if(_lastItemSelected )
    {
      _lastItemSelected->deselectItem();
      _lastItemSelected = NULL;
    }

	if( _playerDoorButtonPressed )
	{
		ui->_door_player->setStyleSheet( noPushedStyle );
		_playerDoorButtonPressed = false;
	}
  }
}

void
QOmgDragableEntities::playerDoorButtonPressed()
{
	MouseScenaryEdit * mouseController = dynamic_cast<MouseScenaryEdit*>( InputManager::getInstance()->getController("EditScenary") );
	if( _playerDoorButtonPressed )
	{
		ui->_door_player->setStyleSheet( noPushedStyle );
		_playerDoorButtonPressed = false;
		mouseController->changeCurrentObject("");
	}
	else
	{
		_playerDoorButtonPressed = true;
		ui->_door_player->setStyleSheet( pushedStyle );
		mouseController->changeCurrentObject("Player_Door");
		if(_lastItemSelected )
		{
			_lastItemSelected->deselectItem();
			_lastItemSelected = NULL;
		}

		if( _doorButtonPressed )
		{
			ui->_door_enemy->setStyleSheet( noPushedStyle );
			_doorButtonPressed = false;
		}

	}
}
