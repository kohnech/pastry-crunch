#pragma once

#include "Event.h"
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
    int mWidth;
    int mHeight;
};
