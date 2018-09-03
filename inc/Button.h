#pragma once

#include "Event.h"
#include "IUiComponent.h"
#include "Text.h"


class Button : public IUiComponent, public Event
{
public:
    typedef std::function<void()> ClickedCallback;

    explicit Button(int x = 0, int y = 0, std::string text = "Button");

    ~Button();

    bool load(Assets& assets) override;

    void render(SDL_Surface* Surf_Display) override;

    void cleanup() override;

    void onLButtonDown(int x, int y) override;

    // Signal when clicked

    void addClickedCallback(ClickedCallback cb);

    void onClicked() const;

private:
    Text mText;
    std::string mStr;
    ClickedCallback mClickedCallback;
};
