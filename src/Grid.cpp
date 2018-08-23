#include "Grid.h"
#include "Sounds.h"
#include "Surface.h"


#include "SDL_image.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <random>
#include <stdlib.h>


Grid Grid::instance;

Grid::Grid(int x, int y)
: mGrid{ nullptr }
, mImagePath{ "" }
, mTileWidth{ ICON_WIDTH }
, mTileHeight{ ICON_HEIGHT }
, mPrevClickedIndexes{ 0, 0 }
, mMinimumScore{ 10 }
, mScore{ 0 }
, mMinimumMatches{ 0 }
, mIsRunning{ true }
{
    mX = x;
    mY = y;
}


Grid::~Grid()
{
	join();
    cleanup();
}


void Grid::setPosition(int x, int y)
{
    mX = x;
    mY = y;
}


bool Grid::load(Assets& assets)
{
    assets.printAssets();
    mAssets = assets.getGridAssets();
    std::pair<int, int> gridAssetSize = assets.getGridAssetSize();
    mTileWidth = gridAssetSize.first;
    mTileHeight = gridAssetSize.second;

    std::pair<int, int> gridPosition = assets.getGridPosition();
    mX = gridPosition.first;
    mY = gridPosition.second;

    std::pair<int, int> gridSize = assets.getGridSize();
    mGridRowSize = gridSize.first;     // x-axis
    mGridColumnSize = gridSize.second; // y-axis

    std::cout << "Grid size: " << mGridRowSize << " x " << mGridColumnSize << std::endl;

    mMinimumScore = assets.getMinimumScores();
    mMinimumMatches = assets.getMinimumMatches();

    // Allocate on heap the grid
    mGrid = new Entity**[mGridRowSize];
    for (int i = 0; i < mGridRowSize; i++)
    {
        mGrid[i] = new Entity*[mGridColumnSize];
    }

    mScoreText.load(assets);
    mScoreText.setPosition(824, 100);
    std::string str;
    str = "Score: " + std::to_string(mScore);
    mScoreText.setText(str);

    Board::load(assets);

    initGrid();

	// Start thread
	start();

    return true;
}


void Grid::render(SDL_Surface* Surf_Display)
{
    Board::render(Surf_Display);
    for (int x = 0; x < mGridRowSize; ++x)
    {
        for (int y = 0; y < mGridColumnSize; ++y)
        {
            int xPos = x * mTileWidth;
            int yPos = y * mTileHeight;

            Entity* entity = mGrid[x][y];

            if (entity == nullptr)
            {
                // rendering a void is rendering of nothing...
            }
            else
            {
                if (entity->animate)
                {
                    entity->setPosition(mX + xPos, mY + yPos);
                    entity->renderAnimation(Surf_Display);
                }
                else
                {
                    entity->setPosition(mX + xPos, mY + yPos);
                    entity->render(Surf_Display);
                }
            }

            mScoreText.render(Surf_Display);
        }
    }
}

void Grid::cleanup()
{
    if (mGrid == nullptr)
    {
        std::cout << "ERROR: You must initialize the grid with load()!" << std::endl;
        return;
    }
    for (int x = 0; x < mGridRowSize; ++x)
    {
        for (int y = 0; y < mGridColumnSize; ++y)
        {
            if (mGrid[x][y])
            {
                delete mGrid[x][y];
                mGrid[x][y] = nullptr;
            }
        }
    }
}


int Grid::getRandomInt()
{
    // Seed with a real random value, if available
    std::random_device r;

    // Choose a random mean between 0 and number of unique assets/icon
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(0, mAssets.size() - 1);
    int mean = uniform_dist(e1);
    return mean;
}


/*!
 * Populate a Grid randomly without any matches.
 */
void Grid::initGrid()
{
    // initScore();

    // if (mGrid != null)
    //    destroyAllEntities();

    for (int row = 0; row < mGridRowSize; row++)
    {
        for (int column = 0; column < mGridColumnSize; column++)
        {

            int newId = getRandomInt();

            // check if two previous horizontal are of the same type
            while (column >= 2 && (mGrid[row][column - 1]->id == newId) && mGrid[row][column - 2]->id == newId)
            {
                newId = getRandomInt();
            }

            // check if two previous vertical are of the same type
            while (row >= 2 && (mGrid[row - 1][column]->id == newId) && mGrid[row - 2][column]->id == newId)
            {
                newId = getRandomInt();
            }

            loadEntity(row, column, newId, false);
        }
    }
}

Entity* Grid::loadEntity(int row, int column, int id, bool animate)
{
    // TODO delete previous entity if not NULL???
    std::string asset = mAssets[id];
    Entity* entity = new Entity(id);
    entity->load(asset.c_str(), mTileWidth, mTileHeight);
    entity->animate = animate;
    mGrid[row][column] = entity;
    return entity;
}

void Grid::onLButtonDown(int x, int y)
{
    std::cout << "onLButtonDown: (" << x << "," << y << ")" << std::endl;

    Index index = getIndexesFromPosition(x, y);
    if (index == Index(-1, -1))
    {
        std::cout << "Out of boundary" << std::endl;
        return;
    }
    setHighlightPosition(index);

    update(index);
}

void Grid::onKeyDown(SDL_Keycode sym, Uint16 mod, SDL_Scancode unicode)
{
    std::cout << "Key pressed: " << unicode << std::endl;
    std::cout << "mX:" << mX << "mY: " << mY << std::endl;
}

Index Grid::getIndexesFromPosition(int x, int y)
{
    if (mWidth == 0 || mWidth == 0)
    {
        return { 0, 0 };
    }

    /// Check board boundaries
    if (x < mX || x >= (mWidth * mGridRowSize + mX) || y < mY || y >= (mHeight * mGridColumnSize + mY))
    {
        return { -1, -1 };
    }

    /// Calculate board coordinate
    int row = (x - mX) / mWidth;
    int column = (y - mY) / mHeight;
    std::cout << "Pressed coordinate: (" << row << ", " << column << ")" << std::endl;

    if (row < 0 || column < 0)
    {
        return { -1, -1 };
    }

    Index index(row, column);
    return index;
};


void Grid::update(const Index& pos)
{
    if (isAdjacent(pos))
    {
        std::cout << "Found adjacent cookies!!!" << std::endl;
        swapEntity(mPrevClickedIndexes, pos);

        std::vector<Index> matches = findMatches(pos);

        for (auto ind : matches)
        {
            std::cout << "match: (" << ind.row << ", " << ind.column << ")" << std::endl;
        }


        if (matches.size() < mMinimumMatches)
        {
            // play sound
            Sounds::instance.play("error");
            swapEntity(pos, mPrevClickedIndexes); // Undo swap
            mPrevClickedIndexes = pos;
            return;
        }


        if (matches.size() >= mMinimumMatches)
        {
            // play sound
            Sounds::instance.play("kaChing");

            // Update score
            mScore += matches.size() * mMinimumScore;
            updateScore();

            // Now we need collapse the matches
            removeMatches(matches);


            // TODO This should be a while loop if more matches occurs while refiling the grid...
            // TODO create new thread...

            std::vector<int> rows = getDistinctRows(matches);

            collapse(rows);

            createNewEntitiesInRows(rows);

            mNewMatches.clear();
            mNewMatches = findNewMatches();
        }
    }
    else
    {
        std::cout << "No adjacent neighbour found!!!" << std::endl;
    }

    mPrevClickedIndexes = pos;
}

bool Grid::isAdjacent(const Index& ind)
{
    return (ind.column == mPrevClickedIndexes.column || ind.row == mPrevClickedIndexes.row) &&
           abs(ind.column - mPrevClickedIndexes.column) <= 1 && abs(ind.row - mPrevClickedIndexes.row) <= 1;
}

void Grid::swapEntity(Index from, Index to)
{
    // First make boundary checks
    if (from.row < 0 || from.column < 0 || to.row < 0 || to.column < 0)
    {
        std::cout << "Try a better index!" << std::endl;
        return;
    }
    Index max = getMaximumGridIndex();

    if (from.row > max.row || from.column > max.column || to.row > max.row || to.column > max.column)
    {
        std::cout << "Try a better index!" << std::endl;
        return;
    }

    // swap entities by swapping them in the grid matrix
    Entity* fromEnt = mGrid[from.row][from.column];
    Entity* toEnt = mGrid[to.row][to.column];
    mGrid[from.row][from.column] = toEnt;
    mGrid[to.row][to.column] = fromEnt;

    int xFromPos = from.row * mTileWidth;
    int yFromPos = from.column * mTileHeight;
    int xToPos = to.row * mTileWidth;
    int yToPos = to.column * mTileHeight;

    std::cout << "swaping from: " << from.row << ", " << from.column << ", to: " << to.row << ", "
              << to.column << std::endl;

    fromEnt->fromX = xFromPos + mX;
    fromEnt->fromY = yFromPos + mY;
    toEnt->fromX = xToPos + mX;
    toEnt->fromY = yToPos + mY;
    fromEnt->animate = true;
    toEnt->animate = true;
}

std::vector<Index> Grid::findVerticalMatches(const Index& ind)
{
    std::vector<Index> matches;

    matches.push_back(ind);
    Entity* entity = mGrid[ind.row][ind.column];

    if (entity == nullptr)
    {
        matches.clear();
        return matches;
    }

    // check left
    if (ind.column != 0)
        for (int column = ind.column - 1; column >= 0; column--)
        {
            if (mGrid[ind.row][column] != nullptr && mGrid[ind.row][column]->id == entity->id)
            {
                Index tmp(ind.row, column);
                matches.push_back(tmp);
            }
            else
                break;
        }

    // check right
    if (ind.column != mGridRowSize - 1)
        for (int column = ind.column + 1; column < mGridColumnSize; column++)
        {
            if (mGrid[ind.row][column] != nullptr && mGrid[ind.row][column]->id == entity->id)
            {
                Index tmp(ind.row, column);
                matches.push_back(tmp);
            }
            else
                break;
        }

    // we are only interested in a set of more than mMinimumMatches connected entities
    if (matches.size() < mMinimumMatches)
        matches.clear();

    return matches;
}

std::vector<Index> Grid::findHorizontalMatches(const Index& ind)
{
    std::vector<Index> matches;
    matches.push_back(ind);
    Entity* entity = mGrid[ind.row][ind.column];

    if (entity == nullptr)
    {
        matches.clear();
        return matches;
    }

    // check bottom
    if (ind.row != 0)
        for (int row = ind.row - 1; row >= 0; row--)
        {
            if (mGrid[row][ind.column] != nullptr && mGrid[row][ind.column]->id == entity->id)
            {
                Index tmp(row, ind.column);
                matches.push_back(tmp);
            }
            else
                break;
        }

    // check top
    if (ind.row != mGridRowSize - 1)
        for (int row = ind.row + 1; row < mGridRowSize; row++)
        {
            if (mGrid[row][ind.column] != nullptr && mGrid[row][ind.column]->id == entity->id)
            {
                Index tmp(row, ind.column);
                matches.push_back(tmp);
            }
            else
                break;
        }

    if (matches.size() < mMinimumMatches)
        matches.clear();

    return matches;
}


std::vector<std::string> Grid::getAssets()
{
    return mAssets;
}

Entity* Grid::getEntity(Index ind)
{
    // First make boundary checks
    if (ind.row < 0 || ind.column < 0)
    {
        // std::cout << "Try a better index, return minimum entity at index (0,0)!" << std::endl;
        return mGrid[0][0];
    }

    Index max = getMaximumGridIndex();

    if (ind.row > max.row || ind.column > max.column)
    {
        // std::cout << "Try a better index, return maximum entity!" << std::endl;
        return mGrid[max.row][max.column];
    }

    return mGrid[ind.row][ind.column];
}


void Grid::setHighlightPosition(const Index& index)
{
    mHighlightX = index.row;
    mHighlightY = index.column;
}

Index Grid::getMaximumGridIndex()
{
    // Simple math here...
    int row = mGridRowSize - 1;
    int column = mGridColumnSize - 1;
    Index ind(row, column);
    return ind;
}

void Grid::removeMatches(const std::vector<Index>& matches)
{
    for (Index ind : matches)
    {
        delete mGrid[ind.row][ind.column];
        mGrid[ind.row][ind.column] = nullptr;
    }
}


void Grid::printGrid()
{
    for (int column = 0; column < mGridColumnSize; column++)
    {
        for (int row = 0; row < mGridRowSize; row++)
        {
            if (mGrid[row][column] == nullptr)
            {
                std::cout << 0;
            }
            else
            {
                std::cout << 1;
            }
        }
        std::cout << std::endl;
    }
}

std::vector<int> Grid::getDistinctRows(const std::vector<Index>& matches)
{
    std::vector<int> rows;
    for (Index ind : matches)
    {
        rows.push_back(ind.row);
    }
    std::sort(rows.begin(), rows.end());
    auto last = std::unique(rows.begin(), rows.end());
    rows.erase(last, rows.end());
    return rows;
}

int Grid::collapse(std::vector<int> rows)
{
    int numCollapses = 0;
    /// search in every row
    for (int row : rows)
    {
        // begin from last column
        for (int y = mGridColumnSize - 1; y > 0; y--)
        {
            // if you find a null item
            if (mGrid[row][y] == nullptr)
            {
                numCollapses++;
                // start searching for the first non-null from one top above of the current index
                for (int y2 = y - 1; y2 >= 0; y2--)
                {
                    // if you find one, bring it down (i.e. replace it with the null you found)
                    if (mGrid[row][y2] != nullptr)
                    {
                        mGrid[row][y] = mGrid[row][y2];
                        mGrid[row][y2] = nullptr;
                        break;
                    }
                }
            }
        }
    }
    // return collapseInfo;
    return numCollapses;
}

void Grid::createNewEntitiesInRows(std::vector<int> rows)
{
    // AlteredCandyInfo newCandyInfo = new AlteredCandyInfo();

    // find how many null values the column has
    for (int row : rows)
    {
        std::vector<Index> emptyItems = getEmptyItemsOnRow(row);
        for (auto index : emptyItems)
        {
            std::cout << "emptyItems: " << index.row << ", " << index.column << std::endl;
            int go = getRandomInt();

            Entity* entity = loadEntity(index.row, index.column, go, true);

            // Set animation
            entity->animate = true;

            int xFromPos = index.row * mTileWidth;
            int yFromPos = 0; // We refill from top...

            entity->fromX = xFromPos + mX; // Remember add grid offset...
            entity->fromY = yFromPos + mY;
        }
    }
}


std::vector<Index> Grid::getEmptyItemsOnRow(int row)
{
    std::vector<Index> voids;
    if (row >= mGridRowSize)
    {
        return voids;
    }

    for (int column = 0; column < mGridColumnSize; column++)
    {
        if (mGrid[row][column] == nullptr)
            voids.push_back(Index(row, column));
    }
    return voids;
}

void Grid::setVoid(const Index& index)
{
    mGrid[index.row][index.column] = nullptr;
}

void Grid::updateScore()
{
    std::string str;
    str = "Score: " + std::to_string(mScore);
    mScoreText.setText(str);
}

std::vector<Index> Grid::findMatches(Index pos)
{
    std::vector<Index> matches;
    matches = findVerticalMatches(pos);
    std::vector<Index> matchesHor = findHorizontalMatches(pos);
    // Get total matches
    matches.insert(matches.end(), matchesHor.begin(), matchesHor.end());
    return matches;
}

std::vector<Index> Grid::findNewMatches()
{
    std::vector<Index> matches;
    for (int row = 0; row < mGridRowSize; row++)
    {
        for (int column = 0; column < mGridColumnSize; column++)
        {
            // Find vertically
            std::vector<Index> newMatches;
            newMatches = findVerticalMatches(Index(row, column));
            matches.insert(matches.end(), newMatches.begin(), newMatches.end());

            newMatches.clear();
            newMatches = findHorizontalMatches(Index(row, column));
            matches.insert(matches.end(), newMatches.begin(), newMatches.end());
        }
    }

    // Filter out only unique matches
    try
    {
        std::sort(matches.begin(), matches.end());
        auto last = std::unique(matches.begin(), matches.end());
        matches.erase(last, matches.end());
    }
    catch (std::exception& e)
    {
        std::cout << "Got exception e: " << e.what() << std::endl;
    }

    for (auto match : matches)
    {
        std::cout << "find new match: " << match.row << ", " << match.column << std::endl;
    }
    return matches;
}

void Grid::updateGrid()
{
    if (mNewMatches.size() >= mMinimumMatches)
    {
        // play sound
        Sounds::instance.play("kaChing");

        // Update score
        mScore += mNewMatches.size() * mMinimumScore;
        updateScore();

        // Now we need collapse the matches
        removeMatches(mNewMatches);


        // TODO This should be a while loop if more matches occurs while refiling the grid...
        // TODO move out to outer function
        printGrid();

        std::vector<int> rows = getDistinctRows(mNewMatches);

        collapse(rows);

        createNewEntitiesInRows(rows);

        mNewMatches.clear();
        mNewMatches = findNewMatches();
    }
}

bool Grid::ThreadMethod()
{
	while (mIsRunning)
	{
		updateGrid();
		sleep(2000); // To get time to run animations & rendering...
	}
	return true;
}

void Grid::stop()
{
	mIsRunning = false;
}