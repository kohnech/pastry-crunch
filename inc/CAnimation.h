#pragma once
#include <SDL_hints.h>


class CAnimation
{
public:
	int MaxFrames;

    bool Oscillate;

    CAnimation();

    void OnAnimate();

    void SetFrameRate(int Rate);

    void SetCurrentFrame(int Frame);

    int GetCurrentFrame();

private:
	int CurrentFrame;

	int FrameInc;

    int FrameRate; // Milliseconds

	int OldTime;
};
