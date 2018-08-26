#pragma once

#include "IAppState.h"
#include "Surface.h"

class AppStateIntro : public IAppState
{
public:
    AppStateIntro();

    bool activate();

    void deactivate();

    void loop();

    void render(SDL_Surface* Surf_Display);

private:
    SDL_Surface* Surf_Logo;

    unsigned int StartTime;
};
