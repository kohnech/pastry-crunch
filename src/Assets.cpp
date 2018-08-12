#include "Assets.h"

#include "json.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using json = nlohmann::json;

Assets::Assets()
{
}

void Assets::load(std::string settingsFile)
{
    std::ifstream ifs(settingsFile);
    ifs >> mJ;
}


std::string Assets::getBackgroundPath()
{
    return mJ["background"]["asset"];
}

std::pair<int, int> Assets::getScreenSize()
{
    std::pair<int, int> size;
    size.first = mJ["settings"]["screen"]["width"];
    size.second = mJ["settings"]["screen"]["height"];
    return size;
};

std::vector<std::string> Assets::getGridAssets()
{
    std::vector<std::string> vec;
    json data = mJ["grid"]["assets"]["icons"];

    for (auto it = data.begin(); it != data.end(); ++it)
    {
        vec.push_back(*it);
    }

    return vec;
};

std::pair<int, int> Assets::getGridAssetSize()
{
    std::pair<int, int> size;
    size.first = mJ["grid"]["assets"]["width"];
    size.second = mJ["grid"]["assets"]["height"];
    return size;
}

std::pair<int, int> Assets::getGridSize()
{
    std::pair<int, int> size;
    size.first = mJ["grid"]["width"];
    size.second = mJ["grid"]["height"];
    return size;
}

std::pair<int, int> Assets::getGridPosition()
{
    std::pair<int, int> position;
    position.first = mJ["grid"]["xpos"];
    position.second = mJ["grid"]["ypos"];
    return position;
}

std::string Assets::getTitle()
{
    return mJ["settings"]["title"];
}

std::string Assets::getTileAsset()
{
    return mJ["tile"]["asset"];
}

std::pair<int, int> Assets::getTileSize()
{
    std::pair<int, int> size;
    size.first = mJ["tile"]["width"];
    size.second = mJ["tile"]["height"];
    return size;
};

std::string Assets::getHighlightAsset()
{
    return mJ["tile"]["highlight"];
}

std::string Assets::getFont()
{
    return mJ["settings"]["font"];
}

int Assets::getFontSize()
{
    return mJ["settings"]["fontSize"];
}
