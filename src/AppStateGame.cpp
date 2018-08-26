#include "AppStateGame.h"

#include "Sounds.h"

#include <iostream>


AppStateGame::AppStateGame()
: mIsGameOver{ false }
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


bool AppStateGame::activate() {
/// Settings & assets
    Assets assets;

#ifdef _DEBUG
    assets.loadFile("../../../assets/assets.json");
#else
    assets.loadFile("./assets/assets.json");
#endif

    Background_Surf = Surface::loadImage(assets.getBackgroundPath());
    GameOver_Surf = Surface::loadImage(assets.getGameOverAsset());


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

    mMuteButton = Button(800, 0, "Mute");
    mMuteButton.load(assets);
    mMuteButton.addClickedCallback([&] { Sounds::instance.toggleMute(); });

    // Add music
    Sounds::instance.play("mining");

    mCountDown.load(assets);
    mCountDown.setPosition(100, 100);
    mCountDown.addTimedOutCallback([&] {
        mIsGameOver = true;
        gameOver();
    });

    std::cout << "finished AppStateGame OnActivate()..." << std::endl;

    return true;
}

void AppStateGame::deactivate() {
    SDL_FreeSurface(Background_Surf);
    SDL_FreeSurface(GameOver_Surf);
    EntityList.clear();
}

void AppStateGame::loop()
{
}

void AppStateGame::render(SDL_Surface* Surf_Display)
{
    Surface::OnDraw(Surf_Display, Background_Surf, 0, 0);

    if (!mIsGameOver)
    {
        mGrid.render(Surf_Display);

        mCountDown.render(Surf_Display);
        mMuteButton.render(Surf_Display);
    }
    else
    {
        Surface::OnDraw(Surf_Display, GameOver_Surf, 0, 0);
    }
}

void AppStateGame::onEvent(SDL_Event* event)
{
    mMuteButton.onEvent(event);
    mGrid.onEvent(event);
}

void AppStateGame::gameOver()
{
    Sounds::instance.stop();
    Sounds::instance.toggleMute();
}