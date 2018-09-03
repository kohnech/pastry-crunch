#include "App.h"
#include "AppStateManager.h"
#include "Assets.h"
#include "Define.h"
#include "Grid.h"
#include "Sounds.h"

#include <SDL_events.h>

#include <iostream>
#include <utility>


App::App()
: mIsRunning { true }
, mWindow{ nullptr }
, Surf_Display{ nullptr }
{
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

    std::string windowTitle = assets.getTitle();
    /// Create main application window
    mWindow = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, mWidth, mHeight, SDL_WINDOW_RESIZABLE);

    if (mWindow == nullptr)
    {
        std::cerr << "ERROR: SDL_CreateWindow got NULL!" << SDL_GetError() << std::endl;
        return false;
    }

    Surf_Display = SDL_GetWindowSurface(mWindow);

    std::cout << "finished App OnInit()..." << std::endl;

    AppStateManager::instance.setActiveAppState(APPSTATE_INTRO);

    return true;
}

void App::onEvent(SDL_Event* event)
{
    Event::onEvent(event);

    AppStateManager::instance.onEvent(event);
}

bool App::loop()
{

    AppStateManager::instance.loop();
    return mIsRunning;
}

void App::render()
{
    AppStateManager::instance.render(Surf_Display);

    SDL_UpdateWindowSurface(mWindow);
}

void App::cleanup()
{
    AppStateManager::instance.setActiveAppState(APPSTATE_NONE);

    SDL_FreeSurface(Surf_Display);
    SDL_DestroyWindow(mWindow);

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
