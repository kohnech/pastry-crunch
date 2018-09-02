#include "AppStateGame.h"
#include "AppStateManager.h"
#include "CCamera.h"
#include "Sounds.h"


#include <iostream>


AppStateGame::AppStateGame()
: mCountDown { 60 }
{
}

AppStateGame::~AppStateGame()
{
}


void AppStateGame::onKeyDown(SDL_Keycode sym, Uint16 mod, SDL_Scancode unicode)
{
    std::cout << "Key pressed: " << unicode << std::endl;
    switch (sym)
    {
    case SDLK_UP:
        CCamera::CameraControl.OnMove(0, -5);
        break;
    case SDLK_DOWN:
        CCamera::CameraControl.OnMove(0, 5);
        break;
    case SDLK_LEFT:
        CCamera::CameraControl.OnMove(-5, 0);
        break;
    case SDLK_RIGHT:
        CCamera::CameraControl.OnMove(5, 0);
        break;
    case SDLK_1:
        Sounds::instance.play("drip");
        break;
    case SDLK_2:
        Sounds::instance.play("kaChing");
        break;
    case SDLK_3:
        Sounds::instance.play("mining");
        break;
    case SDLK_4:
        Sounds::instance.play("scrape");
        break;
    case SDLK_5:
        Sounds::instance.play("comp");
        break;
    case SDLK_6:
        Sounds::instance.toggleMute();
        break;
    case SDLK_9:
        Sounds::instance.stop();
        break;

    default:
    {
    }
    }
}


bool AppStateGame::activate()
{
    mBackground = nullptr;
    mMuteButton = new Button(800, 0, "Mute");

    std::cout << "AppStateGame activate()" << std::endl;

    /// Settings & assets
    Assets assets;

#ifdef _DEBUG
    assets.loadFile("../../../assets/assets.json");
#else
    assets.loadFile("./assets/assets.json");
#endif

    mBackground = Surface::loadImage(assets.getBackgroundPath());

    /// Create game grid
    if (!mGrid.load(assets))
    {
        std::cout << "Could not load Grid" << std::endl;
        return false;
    }

    /// init sounds
    if (!Sounds::instance.load(assets))
    {
        return false;
    }

    mMuteButton->load(assets);
    mMuteButton->addClickedCallback([&] { Sounds::instance.toggleMute(); });

    // Add music
    Sounds::instance.play("mining");

    mCountDown.load(assets);
    mCountDown.setPosition(100, 100);
    mCountDown.addTimedOutCallback(&callback);

    std::cout << "finished AppStateGame OnActivate()..." << std::endl;

    mActivatedCallback();

    return true;
}

void AppStateGame::callback()
{
	std::cout << "mCountDown timer callback..." << std::endl;
	AppStateManager::instance.setActiveAppState(APPSTATE_GAMEOVER);
}

void AppStateGame::deactivate()
{
    std::cout << "AppStateGame deactivate()" << std::endl;
    Sounds::stop();
    mIsDeactivated = true;
    mCountDown.mIsRendering = false;
    cleanup();
}

void AppStateGame::loop()
{
}

void AppStateGame::render(SDL_Surface* Surf_Display)
{
    if (mIsDeactivated)
        return;

    Surface::OnDraw(Surf_Display, mBackground, 0, 0);

    mGrid.render(Surf_Display);
    if (!mIsDeactivated)
        mCountDown.render(Surf_Display);
    if (mMuteButton != nullptr && !mIsDeactivated)
        mMuteButton->render(Surf_Display);
}

void AppStateGame::onEvent(SDL_Event* event)
{
    mMuteButton->onEvent(event);
    mGrid.onEvent(event);
}

void AppStateGame::cleanup()
{
    if (mBackground != nullptr)
        SDL_FreeSurface(mBackground);

    delete mMuteButton;
    mMuteButton = nullptr;
}