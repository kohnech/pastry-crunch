#include "AppStateManager.h"

#include "AppStateGame.h"
#include "AppStateIntro.h"
#include "AppStateGameOver.h"

#include <iostream>

AppStateManager AppStateManager::instance;

IAppState* AppStateManager::ActiveAppState = 0;

AppStateManager::AppStateManager()
{
}

void AppStateManager::onEvent(SDL_Event* EventHolder)
{
    if (ActiveAppState)
        ActiveAppState->onEvent(EventHolder);
}

void AppStateManager::loop()
{
    if (ActiveAppState)
        ActiveAppState->loop();
}

void AppStateManager::render(SDL_Surface* Surf_Display)
{
    if (ActiveAppState)
        ActiveAppState->render(Surf_Display);
}

void AppStateManager::setActiveAppState(int AppStateID)
{
    std::cout << "AppStateManager setActiveState: " << ToString(AppStateID) << std::endl;

    if (ActiveAppState) {
        ActiveAppState->deactivate();
        delete ActiveAppState;
    }

    if (AppStateID == APPSTATE_NONE)
        ActiveAppState = nullptr;
    if (AppStateID == APPSTATE_INTRO)
        ActiveAppState = new AppStateIntro;
    if (AppStateID == APPSTATE_GAME)
        ActiveAppState = new AppStateGame;
    if (AppStateID == APPSTATE_GAMEOVER)
        ActiveAppState = new AppStateGameOver;

    if (ActiveAppState)
        ActiveAppState->activate();
}

IAppState* AppStateManager::getActiveAppState()
{
    return ActiveAppState;
}
