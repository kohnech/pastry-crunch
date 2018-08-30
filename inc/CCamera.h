#pragma once

#include <SDL.h>

#include "Define.h"

enum class TARGET_MODE
{
    NORMAL = 0,
    CENTER
};

class CCamera
{
public:
    static CCamera CameraControl;

private:
    int X;
    int Y;

    int* TargetX;
    int* TargetY;

public:
    int TargetMode;

public:
    CCamera();

public:
    void OnMove(int MoveX, int MoveY);

public:
    int GetX() const;
    int GetY() const;

public:
    void SetPos(int X, int Y);

    void SetTarget(int* X, int* Y);
};
