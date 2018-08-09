#include "CApp.h"
#include "CSurface.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL_image.h>
#include "Define.h"
#include "CGrid.h"
#include "CAssets.h"

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
    assets.load();

    std::pair <int, int> size = assets.getScreenSize();
    mWidth = size.first;
    mHeight = size.second;

    if (mWidth <= 0) {
        mWidth = SCREEN_WIDTH;
    }
    if (mHeight <= 0) {
        mHeight = SCREEN_HEIGHT;
    }

    std::cout << assets.getBackgroundPath() << std::endl;
    Background_Surf = CSurface::loadImage(assets.getBackgroundPath());
    std::vector<std::string> icons = assets.getGridAssets();
    for (auto asset : icons)
    {
        std::cout << "assets:" << asset << std::endl;
    }
    std::string windowTitle = assets.getTitle();

    std::pair <int, int> gridAssetSize = assets.getGridAssetSize();

    /// Create main application window
    mWindow = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                               mWidth, mHeight, SDL_WINDOW_RESIZABLE);

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



    /// Create game board
    CGrid::instance.setPosition(100, 100);
    CGrid::instance.setBrickSize(gridAssetSize.first, gridAssetSize.second);
    if(CGrid::instance.load(icons) == false) {
        return false;
    }


    std::cout << "finished CApp OnInit()..."<< std::endl;

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
    CSurface::OnDraw(Surf_Display, Background_Surf, 0, 0);

    int i = 1;
    for(auto entity : EntityList)
    {
        if(!entity) {
            continue;
        }

        entity->OnRender(Surf_Display, CCamera::CameraControl.GetX() * i, CCamera::CameraControl.GetY());
        i++;
    }

    CGrid::instance.render(Surf_Display);


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
