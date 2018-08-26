#pragma once

#include "Event.h"

class IAppState : public Event {
public:
    IAppState(){}

    virtual bool OnActivate() = 0;

    virtual void OnDeactivate() = 0;

    virtual void OnLoop() = 0;

    virtual void OnRender(SDL_Surface* Surf_Display) = 0;
};
