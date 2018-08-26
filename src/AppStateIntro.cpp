#include "AppStateIntro.h"

#include "AppStateManager.h"

AppStateIntro::AppStateIntro() {
    Surf_Logo = NULL;
}

bool AppStateIntro::OnActivate() {
    // Load Simple Logo
    Surf_Logo = Surface::loadImage("assets/github-octocat.png");

    StartTime = SDL_GetTicks();

    return true;
}

void AppStateIntro::OnDeactivate() {
    if(Surf_Logo) {
        SDL_FreeSurface(Surf_Logo);
        Surf_Logo = NULL;
    }
}

void AppStateIntro::OnLoop() {
    if(StartTime + 3000 < SDL_GetTicks()) {
        AppStateManager::instance.SetActiveAppState(APPSTATE_GAME);
    }
}

void AppStateIntro::OnRender(SDL_Surface* Surf_Display) {
    if(Surf_Logo) {
        Surface::OnDraw(Surf_Display, Surf_Logo, 0, 0);
    }
}
