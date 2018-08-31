#pragma once

#include "IAppState.h"

enum APPSTATE
{
    APPSTATE_NONE,
    APPSTATE_INTRO,
    APPSTATE_GAME,
    APPSTATE_GAMEOVER
};

inline const char* ToString(int v)
{
    switch (v)
    {
        case APPSTATE_NONE:   return "APPSTATE_NONE";
        case APPSTATE_INTRO:   return "APPSTATE_INTRO";
        case APPSTATE_GAME: return "APPSTATE_GAME";
        case APPSTATE_GAMEOVER: return "APPSTATE_GAMEOVER";
        default:      return "[Unknown]";
    }
}

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
