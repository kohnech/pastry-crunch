#include "CApp.h"
#include "Surface.h"
#include "CAssets.h"
#include "Grid.h"
#include "Board.h"
#include "Define.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL_image.h>

#include <iostream>
#include <utility>


CApp::CApp()
: mWindow{ NULL }
, Surf_Display{ NULL }
, Surf_Test{ NULL }
{
    mIsRunning = true;
}

CApp::~CApp()
{
    onCleanup();
}


bool CApp::onInit()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return false;
    }

    /// Settings & assets
    CAssets assets;
    assets.load("./assets/assets.json");

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

    std::cout << assets.getBackgroundPath() << std::endl;
    Background_Surf = Surface::loadImage(assets.getBackgroundPath());
    std::string windowTitle = assets.getTitle();


    /// Create main application window
    mWindow = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, mWidth, mHeight, SDL_WINDOW_RESIZABLE);

    if (mWindow == NULL)
    {
        std::cout << "SDL_CreateWindow got NULL!" << std::endl;
        return false;
    }

    Surf_Display = SDL_GetWindowSurface(mWindow);

    std::string img = "yoshi.png";

    if ((Surf_Test = Surface::OnLoad(img)) == NULL)
    {
        printf("Loading Image failed: %s\n", SDL_GetError());
        return false;
    }


    Anim_Yoshi.MaxFrames = 8;
    // Anim_Yoshi.Oscillate = true;

    if (Entity1.load(img, 64, 64) == false)
    {
        return false;
    }

    if (Entity2.load(img, 64, 64) == false)
    {
        return false;
    }


    EntityList.push_back(&Entity1);
    EntityList.push_back(&Entity2);


    /// Create game grid
    // Grid::instance.setPosition(100, 100);
    if (Grid::instance.load(assets) == false)
    {
        return false;
    }


    std::cout << "finished CApp OnInit()..." << std::endl;

    mScore.load(assets);

    return true;
}

void CApp::onEvent(SDL_Event* event)
{
    Event::onEvent(event);
    Grid::instance.onEvent(event);
}

void CApp::onLoop()
{
    Anim_Yoshi.OnAnimate();
}

void CApp::onRender()
{

    Surface::OnDraw(Surf_Display, Background_Surf, 0, 0);

    int i = 1;
    for (auto entity : EntityList)
    {
        if (!entity)
        {
            continue;
        }

        entity->render(Surf_Display, CCamera::CameraControl.GetX() * i, CCamera::CameraControl.GetY());
        i++;
    }

    Grid::instance.render(Surf_Display);

    mScore.setText("Score: 100", 100, 100);
    mScore.render(Surf_Display);
    Surface::OnDraw(Surf_Display, Surf_Test, 290, 220, 0, Anim_Yoshi.GetCurrentFrame() * 64, 64, 64);

    SDL_UpdateWindowSurface(mWindow);
}

void CApp::onCleanup()
{
    SDL_FreeSurface(Surf_Test);
    SDL_FreeSurface(Surf_Display);
    SDL_DestroyWindow(mWindow);

    EntityList.clear();

    SDL_Quit();
    std::cout << "Quitting..." << std::endl;
}

void CApp::onExit()
{
    std::cout << "Quiting... bye!" << std::endl;
    mIsRunning = false;
}

void CApp::onResize(int w, int h)
{
    std::cout << "Window resized width: " << w << ", height: " << h << std::endl;
}

void CApp::onKeyDown(SDL_Keycode sym, Uint16 mod, SDL_Scancode unicode)
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

    default:
    {
    }
    }
}

bool CApp::ThreadMethod()
{
    std::cout << "ThreadMethod()" << std::endl;

    SDL_Event event;

    while (mIsRunning)
    {
        while (SDL_PollEvent(&event)) // TODO move out to own thread and use SDL_WaitEvent
        {
            onEvent(&event);
        }

        onLoop();
        onRender();
        sleep(33); // ms, 30 fps
    }

    return true;
};
