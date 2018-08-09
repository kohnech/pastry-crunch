#pragma once

#include <SDL.h>
#include "Define.h"
#include <string>
#include "CEntity.h"

class CGrid {
public:
    static CGrid instance;

    /*!
     * Construct a grid with left upper corner at (x,y)
     * @param x x position upper left corner
     * @param y y position upper left corner
     */
    CGrid(int x, int y);

    /*!
     * Construct a grid with left upper corner at (0, 0)
     */
    CGrid();

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
     * Sets grid brick size
     * @param w
     * @param h
     */
    void setBrickSize(int w, int h);

    /*!
     * Loads grid assets
     * @param assets Vector with the icon assets
     * @return
     */
    bool load(std::vector <std::string> assets);

    void render(SDL_Surface *Surf_Display);

    void cleanup();


    int getRandomInt();


private:
    /*!
    * Creates a starting point with bricks laid our randomly with max
    * 2 of the same in a set.
    */
    void initGrid();


    std::vector<std::string> mAssets;
    CEntity *mGrid[GRID_WIDTH][GRID_HEIGHT];
    std::string mImagePath;
    int mX, mY;
    int mBrickWidth, mBrickHeight;
};
