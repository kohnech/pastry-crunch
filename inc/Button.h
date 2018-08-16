#pragma once

#include "IUiComponent.h"
#include "Event.h"
#include "Text.h"


class Button : public IUiComponent, public Event
{
public:
    Button(int x = 0, int y = 0, std::string text = "Button");

    ~Button();

    virtual bool load(Assets& assets);

    virtual void render(SDL_Surface* Surf_Display);
    virtual void cleanup();

    virtual void onLButtonDown(int x, int y);

    // Signal when clicked
    void onClicked();

private:
    Text mText;
    std::string mStr;
};