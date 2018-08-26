#include "AppStateGameOver.h"
#include "AppStateManager.h"
#include "Assets.h"

#include <iostream>

AppStateGameOver::AppStateGameOver()
{
    Background_Surf = NULL;
}

bool AppStateGameOver::activate()
{
    std::cout << "AppStateGameOver activate()" << std::endl;

    /// Settings & assets
    Assets assets;

#ifdef _DEBUG
    assets.loadFile("../../../assets/assets.json");
#else
    assets.loadFile("./assets/assets.json");
#endif

    Background_Surf = Surface::loadImage(assets.getBackgroundPath());
    GameOver_Surf = Surface::loadImage(assets.getGameOverAsset());

    StartTime = SDL_GetTicks();

    return true;
}

void AppStateGameOver::deactivate()
{
    std::cout << "AppStateGameOver deactivate()" << std::endl;
    if (Background_Surf)
    {
        SDL_FreeSurface(Background_Surf);
        Background_Surf = NULL;
    }
    SDL_FreeSurface(GameOver_Surf);
}

void AppStateGameOver::loop()
{
    if (StartTime + 3000 < SDL_GetTicks())
    {
        AppStateManager::instance.setActiveAppState(APPSTATE_GAME);
    }
}

void AppStateGameOver::render(SDL_Surface* Surf_Display)
{
    if (Background_Surf)
    {
        Surface::OnDraw(Surf_Display, Background_Surf, 0, 0);
    }
    Surface::OnDraw(Surf_Display, GameOver_Surf, 0, 0);
}
