#pragma once

#include "IAppState.h"
#include "Surface.h"

class AppStateGameOver : public IAppState
{
public:
    AppStateGameOver();

    bool activate();

    void deactivate();

    void loop();

    void render(SDL_Surface* Surf_Display);

private:
    SDL_Surface* Background_Surf;
    SDL_Surface* GameOver_Surf;

    unsigned int StartTime;
};
