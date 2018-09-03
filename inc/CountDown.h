#pragma once

#include "IUiComponent.h"
#include "Text.h"

#include <SDL.h>
#include "IThread.h"

class CountDown : public IUiComponent
{
public:
    typedef std::function<void()> TimedOutCallback;

    explicit CountDown(int seconds = 60);
    ~CountDown();

    // Disable operators
    CountDown(const CountDown&) = delete;
    const CountDown operator=(const CountDown&) = delete;
    CountDown & operator= (CountDown &&) = delete;
    CountDown(CountDown &&) = delete;

    bool load(Assets& assets) override;
    void cleanup() override;
    void render(SDL_Surface* Surf_Display) override;
    void addTimedOutCallback(TimedOutCallback cb);

private:
   void update();

    Sint32 mTimeRemaining;
    Uint32 mCurrentTimeStamp;
    Uint32 mLastTimeStamp;
    Text mText;
    TimedOutCallback mTimedOutCallback;
};
