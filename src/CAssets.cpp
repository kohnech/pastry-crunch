#include "CAssets.h"

#include "json.hpp"

#include <fstream>
#include <iostream>
#include <utility>
#include <vector>
#include <string>

//  using nlohmann::json;
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

std::pair<int,int> CAssets::getScreenSize()
{
    std::pair <int, int> size;
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
    std::pair <int, int> size;
    size.first = mJ["grid"]["assets"]["width"];
    size.second = mJ["grid"]["assets"]["height"];
    return size;
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
    std::pair <int, int> size;
    size.first = mJ["tile"]["width"];
    size.second = mJ["tile"]["height"];
    return size;
};
