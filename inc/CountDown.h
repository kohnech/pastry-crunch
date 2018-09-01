#pragma once

#include "IUiComponent.h"
#include "Text.h"

#include <SDL.h>
#include "IThread.h"

class CountDown : public IUiComponent, public IThread
{
public:
    typedef std::function<void()> TimedOutCallback;

    CountDown();
    ~CountDown();

    bool load(Assets& assets) override;
    void cleanup() override;
    void render(SDL_Surface* Surf_Display) override;
	//void render(SDL_Surface* Surf_Display) override;

    void addTimedOutCallback(TimedOutCallback cb);

    void init();

	bool ThreadMethod() override;

private:
    void update();

    Sint32 mTimeRemaining;
    Uint32 mCurrentTimeStamp;
    Uint32 mLastTimeStamp;
    Text mText;
    TimedOutCallback mTimedOutCallback;

	SDL_Surface* mSurface;
};
