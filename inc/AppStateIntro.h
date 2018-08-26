#pragma once

#include "IAppState.h"
#include "Surface.h"

class AppStateIntro : public IAppState {
public:
    AppStateIntro();

    bool OnActivate();

    void OnDeactivate();

    void OnLoop();

    void OnRender(SDL_Surface* Surf_Display);

private:
    SDL_Surface* Surf_Logo;

    unsigned int StartTime;
};
