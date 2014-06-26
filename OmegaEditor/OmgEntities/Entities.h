/*
				 ___  __  __ ______  ____  ___
				/ _ \|  \/  |  ____|/ ___|/ _ \
	 		   | | | |      | |__  | |   | | | |
               | | | | |\/| |  __| | |  _| |_| |
               | |_| | |  | | |____| |_| |  _  |
                \___/|_|  |_|______|\____|_| |_|

	Copyright (c) 2014 Fernando Perera & Alejandro Vázquez

	Permission is hereby granted, free of charge, to any person obtaining
	a copy of this software and associated documentation files (the
	"Software"), to deal in the Software without restriction, including
	without limitation the rights to use, copy, modify, merge, publish,
	distribute, sublicense, and/or sell copies of the Software, and to
	permit persons to whom the Software is furnished to do so, subject to
	the following conditions:

	The above copyright notice and this permission notice shall be
	included in all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
	MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
	LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
	OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
	WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#ifndef ENTITIES_H
#define ENTITIES_H

#include "Utils/Singleton.h"
#include "Utils/Container.h"
#include "OmgEnemy.h"
#include "OmgPlayer.h"
#include "OmgSceneObj.h"
#include "OmgItem.h"
#include "OmgWeapon.h"
#include "OmgGame.h"
#include "OmgMap.h"

typedef Singleton< Container< OmgEnemy > > EnemyContainer;
typedef Singleton< Container< OmgPlayer > > PlayerContainer;
typedef Singleton< Container< OmgMap > > MapContainer;
typedef Singleton< Container< OmgSceneObj > > SceneObjectContainer;
typedef Singleton< Container< OmgItem > > ItemContainer;
typedef Singleton< Container< OmgGame > > GameContainer;
typedef Singleton< Container< OmgWeapon > > WeaponContainer;

#endif // ENTITIES_H
