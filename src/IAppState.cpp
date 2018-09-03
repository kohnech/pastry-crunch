#include "IAppState.h"

#include <iostream>

IAppState::IAppState()
: mIsDeactivated{ false }
{
}

void IAppState::registerOnActivatedCallback(ActivatedCallback cb)
{
    std::cout << "setting callback " << &cb << std::endl;
    mActivatedCallback = cb;
}