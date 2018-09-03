#pragma once

#include "IAppState.h"
#include "Surface.h"

class AppStateIntro : public IAppState
{
public:
    explicit AppStateIntro();

    ~AppStateIntro() = default;

    bool activate();

    void deactivate();

    void loop();

    void render(SDL_Surface* Surf_Display);

    void cleanup();

private:
    SDL_Surface* mSplash;

    unsigned int StartTime;
};
