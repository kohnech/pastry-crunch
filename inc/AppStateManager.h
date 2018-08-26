#pragma once

#include "IAppState.h"

#include "AppStateIntro.h"
#include "AppStateGame.h"

enum {
    // Add your Other App States Here
    APPSTATE_NONE,
    APPSTATE_INTRO,
    APPSTATE_GAME
};

class AppStateManager {
public:
    static AppStateManager instance;

    void OnEvent(SDL_Event* Event);

    void OnLoop();

    void OnRender(SDL_Surface* Surf_Display);

    void SetActiveAppState(int AppStateID);

    IAppState* GetActiveAppState();

private:
    static IAppState* ActiveAppState;

    AppStateIntro mIntro;
    AppStateGame mGame;
};
