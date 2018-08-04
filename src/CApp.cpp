#include "CApp.h"
#include "CSurface.h"


#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL_image.h>

#include <iostream>


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

    mWindow = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                               SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);

    if (mWindow == NULL)
    {
        std::cout << "SDL_CreateWindow got NULL!" << std::endl;
        return false;
    }

    Surf_Display = SDL_GetWindowSurface(mWindow);

    std::string img = "tomato.bmp";

    if((Surf_Test = CSurface::OnLoad(img.c_str())) == NULL) {
        printf("Loading Image failed: %s\n", SDL_GetError());
        return false;
    }


    Anim_Yoshi.MaxFrames = 8;
    Anim_Yoshi.Oscillate = true;

    return true;
}

void CApp::onEvent(SDL_Event* event)
{
    CEvent::onEvent(event);
}

bool CApp::onLoop()
{
    Anim_Yoshi.OnAnimate();
    return mIsRunning;
}

void CApp::onRender()
{
    //CSurface::OnDraw(Surf_Display, Surf_Test, 290, 220, 0, Anim_Yoshi.GetCurrentFrame() * 64, 64, 64);
    CSurface::OnDraw(Surf_Display, Surf_Test, 0, 0);

    SDL_UpdateWindowSurface(mWindow);

    SDL_Delay(1000 / FRAMES_PER_SECOND);
}

void CApp::onCleanup()
{
    SDL_FreeSurface(Surf_Test);
    SDL_FreeSurface(Surf_Display);
    SDL_DestroyWindow(mWindow);


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
}
