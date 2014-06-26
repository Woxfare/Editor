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
#ifndef CONTAINER_H
#define CONTAINER_H

#include <map>
#include <QString>

template <class T>
class Container
{
public:
    Container()
    {
    };

    T* find( QString aName )
    {
      if(_map.find(aName) != _map.end() )
      {
        return _map[aName];
      }
      return NULL;
    }

    void erase( QString aName )
    {
      std::map< QString, T* >::iterator it = _map.find(aName);
      if( it != _map.end() )
	  {
		// Free memory
		T* tObject = _map[aName];
		delete tObject;
        _map.erase( it );
	  }
    }

    void add( QString aName, T* apElement )
    {
      if(apElement)
        _map[aName] = apElement;
    }

    std::vector< T* > getAll( void )
    { 
      std::vector< T* > vectorToRtn;
      if(_map.empty())
        return vectorToRtn;

      std::map<QString, T*>::iterator it = _map.begin(), it_end = _map.end();
      for(;it != it_end; ++it)
        vectorToRtn.push_back((*it).second);
      return vectorToRtn;
    }

	int size( void ) { return _map.size();	}

private:

  std::map<QString,T*> _map;
};

#endif // CONTAINER_H
