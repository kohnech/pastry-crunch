#pragma once

#include "CAssets.h"
#include "Define.h"
#include "Entity.h"
#include "Board.h"
#include "IUiComponent.h"

#include <SDL.h>

#include <string>

class CGrid : public Board
{
public:
    static CGrid instance;

    /*!
     * Construct a grid with left upper corner at (x,y)
     * @param x x position upper left corner
     * @param y y position upper left corner
     */
    CGrid(int x = 0, int y = 0);


    /*!
     * Unload resources
     */
    ~CGrid();

    /*!
     * Set grid upper left corner at position (x, y)
     * @param xpos
     * @param ypos
     */
    void setPosition(int x, int y);

    /*!
     * Loads grid assets
     * @param assets The asset manager to extract assets
     * @return
     */
    bool load(CAssets& assets);

    void render(SDL_Surface* Surf_Display);

    void cleanup();


    int getRandomInt();

    /*!
     * Creates a starting point with bricks laid our randomly with max
     * 2 of the same in a set.
     */
    void initGrid();

    void loadEntity(int x, int y, int id);

private:
    std::vector<std::string> mAssets;
    Entity* mGrid[GRID_WIDTH][GRID_HEIGHT];
    std::string mImagePath;

    int mBrickWidth, mBrickHeight;
};
