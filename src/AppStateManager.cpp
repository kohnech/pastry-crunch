#include "AppStateManager.h"

#include "AppStateGame.h"
#include "AppStateIntro.h"
#include "AppStateGameOver.h"

#include <iostream>


AppStateManager AppStateManager::instance;

IAppState* AppStateManager::ActiveAppState = nullptr;

void AppStateManager::onEvent(SDL_Event* EventHolder)
{
    if (ActiveAppState != nullptr)
        ActiveAppState->onEvent(EventHolder);
}

void AppStateManager::loop()
{
    if (ActiveAppState != nullptr)
        ActiveAppState->loop();
}

void AppStateManager::render(SDL_Surface* Surf_Display)
{
    if (ActiveAppState != nullptr) 
    {
        ActiveAppState->render(Surf_Display);
    }
}

void AppStateManager::setActiveAppState(int AppStateID)
{
    std::cout << "AppStateManager setActiveAppState: " << ToString(AppStateID) << std::endl;

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

    if (ActiveAppState != nullptr) {
        ActiveAppState->registerOnActivatedCallback(&callback);
    }

	bool success = false;
    if (ActiveAppState)
		success =ActiveAppState->activate();
    if (!success)
    {
		std::cerr << "Could not activate app state!" << std::endl;
    }
}

void AppStateManager::callback()
{
    std::cout << "Activated callback..." << std::endl;
};

IAppState* AppStateManager::getActiveAppState()
{
    return ActiveAppState;
}
