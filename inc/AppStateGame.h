#pragma once

#include "IAppState.h"
#include "CAnimation.h"
#include "CCamera.h"
#include "Button.h"
#include "CountDown.h"
#include "Entity.h"
#include "Surface.h"
#include "Grid.h"

#include <SDL.h>
#include <SDL_events.h>


class AppStateGame : public IAppState {
public:
    AppStateGame();

    void onKeyDown(SDL_Keycode sym, Uint16 mod, SDL_Scancode unicode);

    bool OnActivate();

    void OnDeactivate();

    void OnLoop();

    void OnRender(SDL_Surface* Surf_Display);

    void onEvent(SDL_Event* event);

private:
    SDL_Surface* Background_Surf;
    SDL_Surface* GameOver_Surf;

    std::vector<Entity*> EntityList;

    Button mMuteButton;

    CountDown mCountDown;
    bool mIsGameOver;

    void gameOver();

    Grid mGrid;
};
