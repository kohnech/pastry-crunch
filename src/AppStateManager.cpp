#include "AppStateManager.h"

// Refer to your Other App States Here
//#include "CAppStateIntro.h"
//#include "CAppStateGame.h"

AppStateManager AppStateManager::instance;

IAppState* AppStateManager::ActiveAppState = 0;

void AppStateManager::OnEvent(SDL_Event* EventHolder) {
    if(ActiveAppState) ActiveAppState->onEvent(EventHolder);
}

void AppStateManager::OnLoop() {
    if(ActiveAppState) ActiveAppState->OnLoop();
}

void AppStateManager::OnRender(SDL_Surface* Surf_Display) {
    if(ActiveAppState) ActiveAppState->OnRender(Surf_Display);
}

void AppStateManager::SetActiveAppState(int AppStateID) {
    if(ActiveAppState) ActiveAppState->OnDeactivate();

    // Also, add your App State Here so that the Manager can switch to it
    if(AppStateID == APPSTATE_NONE)        ActiveAppState = NULL;
    if(AppStateID == APPSTATE_INTRO)       ActiveAppState = &mIntro;
    if(AppStateID == APPSTATE_GAME)        ActiveAppState = &mGame;

    if(ActiveAppState) ActiveAppState->OnActivate();
}

IAppState* AppStateManager::GetActiveAppState() {
    return ActiveAppState;
}
