#pragma once

#include "Assets.h"
#include "Board.h"
#include "Define.h"
#include "Entity.h"
#include "IThread.h"
#include "Event.h"
#include "Text.h"

#include <SDL.h>

#include <mutex>
#include <string>

/*!
 * Helper struct to represent (row, column)
 *
 *  We use same coordinate system for indexes as for mouse SDL mouse positions:
 *
 *            ------------------> x-axis = row
 *            |
 *            |
 *            |
 *            |
 *            |
 *           \/
 *           y-axis = column
 *
 *           Hint: Don't think MS excel here...
 *           Reason: Much better to align 2 coordinate systems than creating
 *           an inversion that needs remap/conversion all the time...
 *
 */
struct Index
{
    Index(int r = 0, int c = 0)
    {
        row = r;
        column = c;
    }
    int row, column; // row is x-axis, column y-axis aligned with SDL coordinate system

    bool operator==(const Index& rhs)
    {
        return (row == rhs.row && column == rhs.column);
    }

    bool operator<(const Index& rhs)
    {
        return (row < rhs.row && column < rhs.column);
    }

    void set(int r, int c)
    {
        row = r;
        column = c;
    }
};

class Grid : public Board, public Event, public IThread
{
public:
    /*!
     * Construct a grid with left upper corner at (x,y)
     * @param x x position upper left corner
     * @param y y position upper left corner
     */
    Grid(int x = 0, int y = 0);

    /*!
     * Unload resources
     */
    ~Grid();

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
    bool load(Assets& assets);

    void render(SDL_Surface* Surf_Display);

    void cleanup();

    /*!
     * Creates a new random integer for randomizing the grid...
     * @return a random int
     */
    int getRandomInt();

    /*!
     * Creates a starting point with bricks laid our randomly with max
     * 2 of the same in a set.
     */
    void initGrid();

    /*!
     * Creates a new entity in the big grid. This is where the bricks are created
     * with id that has been randomly generated according to many rules...
     * @param row
     * @param column
     * @param id
     */
    Entity* loadEntity(int row, int column, int id, bool animate);

    //// Events

    /*!
     * Mouse click event for Left button lcicked
     * @param x Clicked x-position
     * @param y Clicked y-position
     */
    virtual void onLButtonDown(int x, int y);

    // TODO use for dragging
    // virtual void onLButtonUp(int mX, int mY);

    /*!
     * Keyboard pressed event of any key
     * @param sym
     * @param mod
     * @param unicode
     */
    virtual void onKeyDown(SDL_Keycode sym, Uint16 mod, SDL_Scancode unicode);

    /*!
     * Calculates the grid indexes from mouse clicked positions
     * @param x
     * @param y
     * @return
     */
    Index getIndexesFromPosition(int x, int y);

    /*!
     * Update game based on new interaction from user
     * @param ind
     */
    void update(const Index& ind);

    /*!
     * Check if this index is neighbour with previous clicked position
     * @param ind
     * @return
     */
    bool isAdjacent(const Index& ind);

    /*!
     * Swap grid entities and undo if no match
     * @param from
     * @param to
     */
    void swapEntity(Index from, Index to);

    /*!
     * Searches for vertical matches and return
     * index set with connected entities
     * @param ind
     * @return
     */
    std::vector<Index> findVerticalMatches(const Index& ind);

    /*!
     * Find matches horizontally
     * @param ind
     * @return
     */
    std::vector<Index> findHorizontalMatches(const Index& ind);

    /*!
     * Return my icon asset list
     * @return
     */
    std::vector<std::string> getAssets();

    /*!
     * Get entity at index for unit test purpose
     */
    Entity* getEntity(Index ind);

    /*!
     * Sets void @ index. This is useful to simulate voids
     * in the grid for unit-testing
     * @param index void to set
     */
    void setVoid(const Index& index);

    /*!
     * Removes clicked matches.
     * @param matches
     */
    void removeMatches(const std::vector<Index>& matches);

    /*!
     * Prints the grid for debug purpose
     */
    void printGrid();

    /*!
     * Returns a vector with the columns containing matches
     * @param matches
     * @return
     */
    std::vector<int> getDistinctRows(const std::vector<Index>& matches);

    /*!
     * Collapses the voids from bottom to top and move them at
     * the uppermost part of the grid so a refill of new entities can be done
     * @param columns The list of columns to collapse
     */
    int collapse(std::vector<int> columns);

    /*!
     * Creates new entities to play with in collapsed rows
     * @param rows
     */
    void createNewEntitiesInRows(std::vector<int> rows);

    /*!
     * Returns which indexes containing voids in a particular row
     * @param row
     * @return
     */
    std::vector<Index> getEmptyItemsOnRow(int row);

    /*!
     * Moves current highlight position to new index
     * @param index new index to highlight
     */
    void setHighlightPosition(const Index& index);

    /*!
     * Returns the maximum Grid index
     * @return maximum grid index which naturally is the width & height
     * of the grid...
     */
    Index getMaximumGridIndex();

    /*!
     * Updates the new score on next rendering cycle
     */
    void updateScore();

    /*!
     * Get both horizontal & vertical matches for one index
     * @param pos
     * @return
     */
    std::vector<Index> findMatches(Index pos);

    /*!
     * Linear search to find new matches in grid.
     * @return the new matches found after user input.
     */
    std::vector<Index> findNewMatches();

    /*!
     * We need run game logic in its own thread to find new matches since
     * its much slower than the rendering running in the main thread.
     */
    virtual bool ThreadMethod();

    /*! Stop the thread */
    void stop();

private:
    /*!
     * Update grid in separate thread
     */
    void updateGrid();


    std::vector<std::string> mAssets;
    Entity*** mGrid;
    std::string mImagePath;

    int mTileWidth, mTileHeight;
    Index mPrevClickedIndexes;
    int mMinimumScore;
    int mScore;
    Text mScoreText;
    size_t mMinimumMatches;
    std::vector<Index> mNewMatches;
    bool mIsRunning;
    std::mutex mLock;
};
