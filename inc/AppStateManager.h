#pragma once

#include "IAppState.h"

#include "AppStateIntro.h"
#include "AppStateGame.h"

#include <memory>


template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

enum {
    // Add your Other App States Here
    APPSTATE_NONE,
    APPSTATE_INTRO,
    APPSTATE_GAME
};

class AppStateManager {
public:
    AppStateManager();

    static AppStateManager instance;

    void OnEvent(SDL_Event* Event);

    void OnLoop();

    void OnRender(SDL_Surface* Surf_Display);

    void SetActiveAppState(int AppStateID);

    IAppState* GetActiveAppState();

private:
    static IAppState* ActiveAppState;

    std::unique_ptr<AppStateIntro> mIntro;
    std::unique_ptr<AppStateGame> mGame;
};
