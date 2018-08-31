#pragma once

#include "Button.h"
#include "CAnimation.h"
#include "CCamera.h"
#include "CountDown.h"
#include "Entity.h"
#include "Grid.h"
#include "IAppState.h"
#include "Surface.h"

#include <SDL.h>
#include <SDL_events.h>


class AppStateGame : public IAppState
{
public:
    AppStateGame();

    ~AppStateGame();

    void onKeyDown(SDL_Keycode sym, Uint16 mod, SDL_Scancode unicode);

    bool activate();

    void deactivate();

    void loop();

    void render(SDL_Surface* Surf_Display);

    void onEvent(SDL_Event* event);

    void cleanup();

private:
    SDL_Surface* mBackground;

    Button* mMuteButton;

    CountDown* mCountDown;

    Grid mGrid;
};
