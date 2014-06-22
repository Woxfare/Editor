#include "InputManager.h"
#include "KeyboardController.h"
#include "MouseScenaryEdit.h"
#include "MouseCubeEdit.h"
#include "MouseCharacterEdit.h"

InputManager * InputManager::_p_instance = NULL;

InputManager::InputManager()
{
    _m_mouseControllers["EditScenary"] = new MouseScenaryEdit();
    _m_mouseControllers["EditCube"] = new MouseCubeEdit();
    _m_mouseControllers["EditCharacter"] = new MouseCharacterEdit();
    _keyboard_controller = new KeyboardController();
}

InputManager * InputManager::getInstance()
{
    if(!_p_instance)
        _p_instance = new InputManager();

    return _p_instance;
}

MouseController * InputManager::getController( std::string sceneName )
{
    return _m_mouseControllers[sceneName];
}

KeyboardController* InputManager::getKeyBoardController()
{
  return _keyboard_controller;
}
