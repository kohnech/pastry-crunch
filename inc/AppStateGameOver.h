#pragma once

#include "IAppState.h"
#include "Surface.h"
#include "Button.h"

class AppStateGameOver : public IAppState
{
public:
    explicit AppStateGameOver();

    ~AppStateGameOver() = default;

    bool activate();

    void deactivate();

    void loop();

    void render(SDL_Surface* Surf_Display);

    void cleanup();

    void onEvent(SDL_Event* event);

private:
    SDL_Surface* mBackground;
    SDL_Surface* GameOver_Surf;

    Button* mRestartBtn;
    //Button* mExitBtn;
};
