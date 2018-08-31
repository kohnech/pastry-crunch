#include "CountDown.h"
#include "Assets.h"

#include <iostream>

CountDown::CountDown()
: mTimeRemaining{ 1000 * 10 } // ms
, mCurrentTimeStamp{ 0 }
, mLastTimeStamp{ 0 }
{
}

CountDown::~CountDown()
{
    cleanup();
}

bool CountDown::load(Assets& assets)
{
    mText.load(assets);
    mText.setPosition(mX, mY);
    mText.setText("CountDown");

    return true;
}

void CountDown::cleanup()
{
}

void CountDown::render(SDL_Surface* Surf_Display)
{
    update();
    mText.render(Surf_Display);
}

void CountDown::update()
{
    mText.setPosition(mX, mY);
    if (mLastTimeStamp == 0) {
        mLastTimeStamp = SDL_GetTicks();
        return;
    }
    mCurrentTimeStamp = SDL_GetTicks();

    if (mCurrentTimeStamp > mLastTimeStamp)
    {
        Uint32 diff = mCurrentTimeStamp - mLastTimeStamp;
        mTimeRemaining = mTimeRemaining - diff;
        mLastTimeStamp = mCurrentTimeStamp;
    }

    std::string str;
    str = "Time: " + std::to_string(mTimeRemaining / 1000);
    mText.setText(str);

    if (mTimeRemaining <= 0)
        mTimedOutCallback();
}

void CountDown::addTimedOutCallback(TimedOutCallback cb)
{
    if (cb == nullptr) {
        std::cerr << "Trying to register nullptr as callback!" << std::endl;
    }
    mTimedOutCallback = cb;
}
