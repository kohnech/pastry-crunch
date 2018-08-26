#include "AppStateManager.h"


AppStateManager AppStateManager::instance;

IAppState* AppStateManager::ActiveAppState = 0;

AppStateManager::AppStateManager()
{
    mIntro = make_unique<AppStateIntro>();
    mGame = make_unique<AppStateGame>();
}

void AppStateManager::onEvent(SDL_Event* EventHolder) {
    if(ActiveAppState) ActiveAppState->onEvent(EventHolder);
}

void AppStateManager::loop() {
    if(ActiveAppState) ActiveAppState->loop();
}

void AppStateManager::render(SDL_Surface* Surf_Display) {
    if(ActiveAppState) ActiveAppState->render(Surf_Display);
}

void AppStateManager::setActiveAppState(int AppStateID) {
    if(ActiveAppState) ActiveAppState->deactivate();

    // Also, add your App State Here so that the Manager can switch to it
    if(AppStateID == APPSTATE_NONE)        ActiveAppState = NULL;
    if(AppStateID == APPSTATE_INTRO)       ActiveAppState = mIntro.get();
    if(AppStateID == APPSTATE_GAME)        ActiveAppState = mGame.get();

    if(ActiveAppState) ActiveAppState->activate();
}

IAppState* AppStateManager::getActiveAppState() {
    return ActiveAppState;
}
