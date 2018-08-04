#pragma once


class CAnimation
{
private:
    int CurrentFrame;

    int FrameInc;

private:
    int FrameRate; //Milliseconds

    long OldTime;

public:
    int MaxFrames;

    bool Oscillate;

public:
    CAnimation();

    void OnAnimate();

public:
    void SetFrameRate(int Rate);

    void SetCurrentFrame(int Frame);

    int GetCurrentFrame();
};