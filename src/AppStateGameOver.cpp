#include "AppStateGameOver.h"
#include "AppStateManager.h"
#include "Assets.h"

#include <iostream>

AppStateGameOver::AppStateGameOver()
: mBackground{ nullptr }
, mRestartBtn{ new Button(430, 500, "Restart Game") }
//, mExitBtn{ new Button(400, 500, "Quit") }
{
}

AppStateGameOver::~AppStateGameOver()
{
    cleanup();
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

    mBackground = Surface::loadImage(assets.getBackgroundPath());
    GameOver_Surf = Surface::loadImage(assets.getGameOverAsset());

    //mRestartBtn->load(assets);
    //mRestartBtn->addClickedCallback([&] { AppStateManager::instance.setActiveAppState(APPSTATE_GAME); });

    //mExitBtn->load(assets);
    //mExitBtn->addClickedCallback([&] { AppStateManager::instance.setActiveAppState(APPSTATE_GAME); });

    mActivatedCallback();

    return true;
}

void AppStateGameOver::deactivate()
{
    std::cout << "AppStateGameOver deactivate()" << std::endl;
}

void AppStateGameOver::loop()
{
}

void AppStateGameOver::render(SDL_Surface* Surf_Display)
{
    if (mBackground)
    {
        Surface::OnDraw(Surf_Display, mBackground, 0, 0);
    }
    Surface::OnDraw(Surf_Display, GameOver_Surf, 0, 0);
    //mRestartBtn->render(Surf_Display);
}

void AppStateGameOver::cleanup()
{
    if (mBackground)
    {
        SDL_FreeSurface(mBackground);
        mBackground = nullptr;
    }
    if (GameOver_Surf)
    {
        SDL_FreeSurface(GameOver_Surf);
        GameOver_Surf = nullptr;
    }
    //delete mRestartBtn;
    //mRestartBtn = nullptr;
}

void AppStateGameOver::onEvent(SDL_Event* event)
{
    //mRestartBtn->onEvent(event);
}
