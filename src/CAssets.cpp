#include "CAssets.h"

#include "json.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using json = nlohmann::json;

CAssets::CAssets()
{
}

void CAssets::load(std::string settingsFile)
{
    std::ifstream ifs(settingsFile);
    ifs >> mJ;
}


std::string CAssets::getBackgroundPath()
{
    return mJ["background"]["asset"];
}

std::pair<int, int> CAssets::getScreenSize()
{
    std::pair<int, int> size;
    size.first = mJ["settings"]["screen"]["width"];
    size.second = mJ["settings"]["screen"]["height"];
    return size;
};

std::vector<std::string> CAssets::getGridAssets()
{
    std::vector<std::string> vec;
    json data = mJ["grid"]["assets"]["icons"];

    for (auto it = data.begin(); it != data.end(); ++it)
    {
        vec.push_back(*it);
    }

    return vec;
};

std::pair<int, int> CAssets::getGridAssetSize()
{
    std::pair<int, int> size;
    size.first = mJ["grid"]["assets"]["width"];
    size.second = mJ["grid"]["assets"]["height"];
    return size;
}

std::pair<int, int> CAssets::getGridSize()
{
    std::pair<int, int> size;
    size.first = mJ["grid"]["width"];
    size.second = mJ["grid"]["height"];
    return size;
}

std::pair<int, int> CAssets::getGridPosition()
{
    std::pair<int, int> position;
    position.first = mJ["grid"]["xpos"];
    position.second = mJ["grid"]["ypos"];
    return position;
}

std::string CAssets::getTitle()
{
    return mJ["settings"]["title"];
}

std::string CAssets::getTileAsset()
{
    return mJ["tile"]["asset"];
}

std::pair<int, int> CAssets::getTileSize()
{
    std::pair<int, int> size;
    size.first = mJ["tile"]["width"];
    size.second = mJ["tile"]["height"];
    return size;
};

std::string CAssets::getHighlightAsset()
{
    return mJ["tile"]["highlight"];
}

std::string CAssets::getFont()
{
    return mJ["settings"]["font"];
}

int CAssets::getFontSize()
{
    return mJ["settings"]["fontSize"];
}
