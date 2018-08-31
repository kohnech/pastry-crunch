#include "AppStateIntro.h"

#include "AppStateManager.h"

AppStateIntro::AppStateIntro()
: mSplash{ nullptr }
{
}

AppStateIntro::~AppStateIntro()
{
    cleanup();
}

bool AppStateIntro::activate()
{
    // Load Simple Logo
    mSplash = Surface::loadImage("assets/github-octocat.png");

    StartTime = SDL_GetTicks();

    mActivatedCallback();

    return true;
}

void AppStateIntro::deactivate()
{
}

void AppStateIntro::loop()
{
    if (StartTime + 3000 < SDL_GetTicks())
    {
        AppStateManager::instance.setActiveAppState(APPSTATE_GAME);
    }
}

void AppStateIntro::render(SDL_Surface* Surf_Display)
{
    if (mSplash)
    {
        Surface::OnDraw(Surf_Display, mSplash, 0, 0);
    }
}

void AppStateIntro::cleanup()
{
    if (mSplash)
    {
        SDL_FreeSurface(mSplash);
        mSplash = nullptr;
    }
}
