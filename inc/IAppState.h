#pragma once

#include "Event.h"

class IAppState : public Event
{
public:
    IAppState() = default;

    virtual ~IAppState() = default;

    virtual bool activate() = 0;

    virtual void deactivate() = 0;

    virtual void loop() = 0;

    virtual void render(SDL_Surface* Surf_Display) = 0;
};
