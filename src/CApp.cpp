#include "CApp.h"
#include "CSurface.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL_image.h>
#include "Define.h"
#include "CGrid.h"

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

    std::string img = "yoshi.png";

    if((Surf_Test = CSurface::OnLoad(img)) == NULL) {
        printf("Loading Image failed: %s\n", SDL_GetError());
        return false;
    }


    Anim_Yoshi.MaxFrames = 8;
    //Anim_Yoshi.Oscillate = true;

    if(Entity1.OnLoad(img, 64, 64) == false) {
        return false;
    }

    if(Entity2.OnLoad(img, 64, 64) == false) {
        return false;
    }


    EntityList.push_back(&Entity1);
    EntityList.push_back(&Entity2);

//    char tmp[] = "./maps/1.area";
    std::string mImagePath = "./assets/bakery/pastry_donut.png";
    std::cout << "finifhed CApp OnInit()"<< std::endl;

    if(CGrid::GridInstance.load(mImagePath) == false) {
        return false;
    }

    return true;
}

void CApp::onEvent(SDL_Event* event)
{
    CEvent::onEvent(event);
}

bool CApp::onLoop()
{
    Anim_Yoshi.OnAnimate();


    for(auto entity : EntityList)
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

    int i = 1;
    for(auto entity : EntityList)
    {
        if(!entity) {
            continue;
        }

        entity->OnRender(Surf_Display, CCamera::CameraControl.GetX() * i, CCamera::CameraControl.GetY());
        i++;
    }

    CGrid::GridInstance.render(Surf_Display, 100, 0);


    SDL_UpdateWindowSurface(mWindow);
}

void CApp::onCleanup()
{
    SDL_FreeSurface(Surf_Test);
    SDL_FreeSurface(Surf_Display);
    SDL_DestroyWindow(mWindow);

    for(auto entity : EntityList)
    {
        if(!entity) {
            continue;
        }

        entity->OnCleanup();
    }
    CGrid::GridInstance.cleanup();

    EntityList.clear();


    SDL_Quit();
    CArea::AreaControl.OnCleanup();
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
    switch(sym) {
        case SDLK_UP:      CCamera::CameraControl.OnMove( 0, -5); break;
        case SDLK_DOWN:  CCamera::CameraControl.OnMove(0, 5); break;
        case SDLK_LEFT:  CCamera::CameraControl.OnMove(-5, 0); break;
        case SDLK_RIGHT: CCamera::CameraControl.OnMove(5,  0); break;

        default: {
        }
    }
}
