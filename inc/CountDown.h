#pragma once

#include "IUiComponent.h"
#include "Text.h"

#include <SDL.h>

class CountDown : public IUiComponent
{
public:
	typedef std::function<void()> TimedOutCallback;

	CountDown();
	~CountDown();

	bool load(Assets& assets);
	void cleanup();
	void render(SDL_Surface* Surf_Display);

	void addTimedOutCallback(TimedOutCallback cb);

private:
	void update();

	Sint32 mTimeRemaining;
	Uint32 mCurrentTimeStamp;
	Uint32 mLastTimeStamp;
	Text mText;
	TimedOutCallback mTimedOutCallback;
};