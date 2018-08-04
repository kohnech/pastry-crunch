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

    std::string img = "yoshi.bmp";

    if((Surf_Test = CSurface::OnLoad(img)) == NULL) {
        printf("Loading Image failed: %s\n", SDL_GetError());
        return false;
    }


    Anim_Yoshi.MaxFrames = 8;
    //Anim_Yoshi.Oscillate = true;

    if(Entity1.OnLoad(img, 64, 64, 8) == false) {
        return false;
    }

    if(Entity2.OnLoad(img, 64, 64, 8) == false) {
        return false;
    }

    Entity2.X = 100;
    Entity2.Y = 100;

    CEntity::EntityList.push_back(&Entity1);
    CEntity::EntityList.push_back(&Entity2);

    return true;
}

void CApp::onEvent(SDL_Event* event)
{
    CEvent::onEvent(event);
}

bool CApp::onLoop()
{
    Anim_Yoshi.OnAnimate();


    for(auto entity : CEntity::EntityList)
    {
        if(!entity) {
            continue;
        }

        entity->OnLoop();
    }

    return mIsRunning;
}

void CApp::onRender()
{
    CSurface::OnDraw(Surf_Display, Surf_Test, 290, 220, 0, Anim_Yoshi.GetCurrentFrame() * 64, 64, 64);

    for(auto entity : CEntity::EntityList)
    {
        if(!entity) {
            continue;
        }

        entity->OnRender(Surf_Display);
    }


    SDL_UpdateWindowSurface(mWindow);
}

void CApp::onCleanup()
{
    SDL_FreeSurface(Surf_Test);
    SDL_FreeSurface(Surf_Display);
    SDL_DestroyWindow(mWindow);

    for(auto entity : CEntity::EntityList)
    {
        if(!entity) {
            continue;
        }

        entity->OnCleanup();
    }

    CEntity::EntityList.clear();


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
