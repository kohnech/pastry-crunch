#pragma once

#include "Event.h"
#include "IUiComponent.h"
#include "Text.h"


class Button : public IUiComponent, public Event
{
public:
    typedef std::function<void()> ClickedCallback;

    Button(int x = 0, int y = 0, std::string text = "Button");

    ~Button();

    virtual bool load(Assets& assets);

    virtual void render(SDL_Surface* Surf_Display);
    virtual void cleanup();

    virtual void onLButtonDown(int x, int y);

    // Signal when clicked

    void addClickedCallback(ClickedCallback cb);

    void onClicked();

private:
    Text mText;
    std::string mStr;
    ClickedCallback mClickedCallback;
};
