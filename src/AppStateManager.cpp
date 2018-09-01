#include "AppStateManager.h"

#include "AppStateGame.h"
#include "AppStateIntro.h"
#include "AppStateGameOver.h"

#include <iostream>

static bool gIsActivated = false;

AppStateManager AppStateManager::instance;

IAppState* AppStateManager::ActiveAppState = 0;

AppStateManager::AppStateManager()
//: mIsActivated{ false }
 : mState{ APPSTATE_NONE }
{
    gIsActivated = false;
}

void AppStateManager::onEvent(SDL_Event* EventHolder)
{
    if (ActiveAppState != nullptr  && gIsActivated)
        ActiveAppState->onEvent(EventHolder);
}

void AppStateManager::loop()
{
    if (ActiveAppState != nullptr  && gIsActivated)
        ActiveAppState->loop();
}

void AppStateManager::render(SDL_Surface* Surf_Display)
{
    if ((ActiveAppState != nullptr)  && gIsActivated && (mState != APPSTATE_NONE))
        ActiveAppState->render(Surf_Display);
}

void AppStateManager::setActiveAppState(int AppStateID)
{
    std::cout << "AppStateManager setActiveAppState: " << ToString(AppStateID) << std::endl;

    if (ActiveAppState) {
        ActiveAppState->deactivate();
        delete ActiveAppState;
        gIsActivated = false;
		mState = APPSTATE_NONE;
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
		success =ActiveAppState->activate(); // TODO check return value
	std::cout << "activate result: " << success << std::endl;
    if (!success)
    {
		std::cerr << "Could not activate app state!" << std::endl;
    }

	gIsActivated = true;
	mState = AppStateID;
}

void AppStateManager::callback()
{
    std::cout << "Activated callback..." << std::endl;
    gIsActivated = false;
};

IAppState* AppStateManager::getActiveAppState()
{
    return ActiveAppState;
}
