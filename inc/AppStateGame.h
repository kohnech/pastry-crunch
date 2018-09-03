#pragma once

#include "Button.h"
#include "CountDown.h"
#include "Grid.h"
#include "IAppState.h"

#include <SDL.h>
#include <SDL_events.h>


class AppStateGame : public IAppState
{
public:
    explicit AppStateGame();

    ~AppStateGame() = default;

    bool activate() override;

    void deactivate() override;

    void loop() override;

    void render(SDL_Surface* Surf_Display) override;

    // Events

    void onKeyDown(SDL_Keycode sym, Uint16 mod, SDL_Scancode unicode);

    void onEvent(SDL_Event* event);

    void cleanup();

    static void callback();

private:
    SDL_Surface* mBackground;

    Button mMuteButton;

    CountDown mCountDown;

    Grid mGrid;
};
