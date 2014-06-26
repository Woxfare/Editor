#include "KeyboardController.h"
#include <QDebug>

KeyboardController::KeyboardController() : _lastKey( Qt::Key_No ){}

void
KeyboardController::keyPressed( Qt::Key key )
{
  _lastKey = key;
  _set_keys.insert( key );
}

void
KeyboardController::keyReleased( Qt::Key key )
{
  _lastKey = Qt::Key_No;
  _set_keys.erase(key);
}

bool
KeyboardController::isKeyPressed( Qt::Key key )
{
  return (_set_keys.count(key) == 1);
}


