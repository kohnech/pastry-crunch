#pragma once

#include "Button.h"
#include "CAnimation.h"
#include "CountDown.h"
#include "Entity.h"
#include "Event.h"
#include "Grid.h"
#include "IThread.h"

#include <SDL.h>

class App : public Event, public IThread
{
public:
    App();
    ~App();

    bool init();

    bool loop();

    void render();

    void cleanup();

    /// Events
	void onEvent(SDL_Event* event) override;

    void onExit() override;

    void onResize(int w, int h) override;

    void onKeyDown(SDL_Keycode sym, Uint16 mod, SDL_Scancode unicode) override;

    virtual bool ThreadMethod() override;

private:
	static void gameOver();

    bool mIsRunning;
    SDL_Window* mWindow;
    SDL_Surface* Surf_Display;
    SDL_Surface* Yoshi_Surf;
    CAnimation Anim_Yoshi;
    Entity Entity1;
    Entity Entity2;
    SDL_Surface* Background_Surf;
    SDL_Surface* GameOver_Surf;
    std::vector<Entity*> EntityList;
    int mWidth;
    int mHeight;
    Button mMuteButton;
    bool mEnableYoshi;
    CountDown mCountDown;
    bool mIsGameOver;
    Grid mGrid;
};
