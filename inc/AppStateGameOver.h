#pragma once

#include "IAppState.h"
#include "Surface.h"

class AppStateGameOver : public IAppState
{
public:
    AppStateGameOver();

    ~AppStateGameOver();

    bool activate();

    void deactivate();

    void loop();

    void render(SDL_Surface* Surf_Display);

    void cleanup();

private:
    SDL_Surface* mBackground;
    SDL_Surface* GameOver_Surf;

    unsigned int StartTime;
};
