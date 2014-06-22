#include "QOmgWindowMngr.h"

QOmgWindowMngr* QOmgWindowMngr::_p_instance = NULL;

QOmgWindowMngr::QOmgWindowMngr()
{
    _main_win = new OmegaWindow( );
}

QOmgWindowMngr*
QOmgWindowMngr::Instance()
{
    if(!_p_instance)
        _p_instance = new QOmgWindowMngr();

    return _p_instance;
}

OmegaWindow*
QOmgWindowMngr::GetMainWindow( void )
{
    return _main_win;
}
