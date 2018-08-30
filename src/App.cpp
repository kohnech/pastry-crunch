#include "App.h"
#include "Assets.h"
#include "Define.h"
#include "Grid.h"
#include "Sounds.h"
#include "Surface.h"

#include <SDL_events.h>


#include <iostream>
#include <utility>


App::App()
: mWindow{ nullptr }
, Surf_Display{ nullptr }
, Yoshi_Surf{ nullptr }
, mEnableYoshi{ false }
, mIsGameOver{ false }
{
    mIsRunning = true;
}

App::~App()
{
    cleanup();
}

#include <string>

bool App::init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return false;
    }

    /// Settings & assets
    Assets assets;

#ifdef _DEBUG
    assets.loadFile("../../../assets/assets.json");
#else
    assets.loadFile("./assets/assets.json");
#endif

    std::pair<int, int> size = assets.getScreenSize();
    mWidth = size.first;
    mHeight = size.second;

    if (mWidth <= 0)
    {
        mWidth = SCREEN_WIDTH;
    }
    if (mHeight <= 0)
    {
        mHeight = SCREEN_HEIGHT;
    }

    Background_Surf = Surface::loadImage(assets.getBackgroundPath());
    GameOver_Surf = Surface::loadImage(assets.getGameOverAsset());
    std::string windowTitle = assets.getTitle();


    /// Create main application window
    mWindow = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, mWidth, mHeight, SDL_WINDOW_RESIZABLE);

    if (mWindow == nullptr)
    {
        std::cout << "SDL_CreateWindow got NULL!" << SDL_GetError() << std::endl;
        return false;
    }

    Surf_Display = SDL_GetWindowSurface(mWindow);

#ifdef _DEBUG
    std::string img = "../../../assets/bakery/yoshi.png";
#else
    std::string img = "./assets/bakery/yoshi.png";
#endif


    if ((Yoshi_Surf = Surface::loadImage(img)) == nullptr)
    {
        printf("Loading Image failed: %s\n", SDL_GetError());
        return false;
    }


    Anim_Yoshi.MaxFrames = 8;
    Surface::Transparent(Yoshi_Surf, 255, 0, 255);
    /*
    if (Entity1.load(img, 64, 64) == false)
    {
        return false;
    }

    if (Entity2.load(img, 64, 64) == false)
    {
        return false;
    }

    EntityList.push_back(&Entity1);
    EntityList.push_back(&Entity2);*/


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

    std::cout << "finished App OnInit()..." << std::endl;

    return true;
}

void App::onEvent(SDL_Event* event)
{
    Event::onEvent(event);
    mGrid.onEvent(event);
    mMuteButton.onEvent(event);
}

bool App::loop()
{
    Anim_Yoshi.OnAnimate();
    return mIsRunning;
}

void App::render()
{

    Surface::OnDraw(Surf_Display, Background_Surf, 0, 0);

    /*  int i = 1;
      for (auto entity : EntityList)
      {
          if (!entity)
          {
              continue;
          }

          entity->setPosition(CCamera::CameraControl.GetX() * i, CCamera::CameraControl.GetY());
          entity->render(Surf_Display);
          i++;
      }*/

    if (!mIsGameOver)
    {
        mGrid.render(Surf_Display);

        if (mEnableYoshi)
        {
            Surface::OnDraw(Surf_Display, Yoshi_Surf, 290, 220, 0, Anim_Yoshi.GetCurrentFrame() * 64, 64, 64);
        }


        mCountDown.render(Surf_Display);
        mMuteButton.render(Surf_Display);
    }
    else
    {
        Surface::OnDraw(Surf_Display, GameOver_Surf, 0, 0);
    }

    SDL_UpdateWindowSurface(mWindow);
}

void App::cleanup()
{
    SDL_FreeSurface(Yoshi_Surf);
    SDL_FreeSurface(Surf_Display);
    SDL_FreeSurface(Background_Surf);
    SDL_FreeSurface(GameOver_Surf);
    SDL_DestroyWindow(mWindow);

    EntityList.clear();

    SDL_Quit();
    std::cout << "Quitting..." << std::endl;
}

void App::onExit()
{
    std::cout << "Quiting... bye!" << std::endl;
    mIsRunning = false;
}

void App::onResize(int w, int h)
{
    std::cout << "Window resized width: " << w << ", height: " << h << std::endl;
}

void App::onKeyDown(SDL_Keycode sym, Uint16 mod, SDL_Scancode unicode)
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
    case SDLK_F10:
        mEnableYoshi = !mEnableYoshi;
        break;

    default:
    {
    }
    }
}

bool App::ThreadMethod()
{
    std::cout << "ThreadMethod()" << std::endl;

    SDL_Event event;

    while (mIsRunning)
    {
        while (SDL_PollEvent(&event)) // TODO move out to own thread and use SDL_WaitEvent
        {
            onEvent(&event);
        }

        loop();
        render();
        sleep(33); // ms, 30 fps
    }

    return true;
};

void App::gameOver()
{
    Sounds::instance.stop();
    Sounds::instance.toggleMute();
}
