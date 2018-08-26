#pragma once

#include "IAppState.h"

enum
{
    APPSTATE_NONE,
    APPSTATE_INTRO,
    APPSTATE_GAME,
    APPSTATE_GAMEOVER
};

class AppStateManager
{
public:
    AppStateManager();

    static AppStateManager instance;

    void onEvent(SDL_Event* Event);

    void loop();

    void render(SDL_Surface* Surf_Display);

    void setActiveAppState(int AppStateID);

    IAppState* getActiveAppState();

private:
    static IAppState* ActiveAppState;
};
