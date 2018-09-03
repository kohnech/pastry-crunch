#pragma once

#include "Event.h"

#include <functional>

typedef std::function<void()> ActivatedCallback;

class IAppState : public Event
{
public:
    IAppState();

    virtual ~IAppState() = default;

    virtual bool activate() = 0;

    virtual void deactivate() = 0;

    virtual void loop() = 0;

    virtual void render(SDL_Surface* Surf_Display) = 0;

    void registerOnActivatedCallback(ActivatedCallback cb);

protected:
    ActivatedCallback mActivatedCallback;
    bool mIsDeactivated;
};
