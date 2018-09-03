#include "CCamera.h"

CCamera CCamera::CameraControl;

CCamera::CCamera()
{
    X = Y = 0;

    TargetX = TargetY = nullptr;

    TargetMode = static_cast<int>(TARGET_MODE::NORMAL);
}

void CCamera::OnMove(int MoveX, int MoveY)
{
    X += MoveX;
    Y += MoveY;
}

int CCamera::GetX() const
{
    if (TargetX != nullptr)
    {
        if (TargetMode == static_cast<int>(TARGET_MODE::CENTER))
        {
            return *TargetX - (SCREEN_WIDTH / 2);
        }

        return *TargetX;
    }

    return X;
}

int CCamera::GetY() const
{
    if (TargetY != nullptr)
    {
        if (TargetMode == static_cast<int>(TARGET_MODE::CENTER))
        {
            return *TargetY - (SCREEN_HEIGHT / 2);
        }

        return *TargetY;
    }

    return Y;
}

void CCamera::SetPos(int X, int Y)
{
    this->X = X;
    this->Y = Y;
}

void CCamera::SetTarget(int* X, int* Y)
{
    TargetX = X;
    TargetY = Y;
}
