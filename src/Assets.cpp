#include "Assets.h"

#include "json.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using json = nlohmann::json;

Assets::Assets()
: mRelativePath{ "" }
{
}

void Assets::loadFile(std::string file)
{
    try
    {
        std::ifstream ifs(file);
        ifs >> mJ;
    }
    catch (std::exception& e)
    {
        std::cerr << "Could not load asset file: " << file << ", with exception: " << e.what() << std::endl;
    }

    try
    {
#ifdef _DEBUG
        mRelativePath = "../../../";
#else
        mRelativePath = "./";
#endif
    }
    catch (std::exception& e)
    {
        std::cerr << "Got exception: " << e.what() << std::endl;
    }
}

void Assets::loadJson(json js)
{
    mJ = js;
}


std::string Assets::getBackgroundPath() const
{
    std::string str = mJ["background"]["asset"];
    return mRelativePath + str;
}

std::pair<int, int> Assets::getScreenSize() const
{
    std::pair<int, int> size;
    size.first = mJ["settings"]["screen"]["width"];
    size.second = mJ["settings"]["screen"]["height"];
    return size;
};

std::vector<std::string> Assets::getGridAssets() const
{
    std::vector<std::string> vec;
    json data = mJ["grid"]["assets"]["icons"];

    for (auto it = data.begin(); it != data.end(); ++it)
    {
        std::string str = *it;
        vec.push_back(mRelativePath + str);
    }

    return vec;
};

std::pair<int, int> Assets::getGridAssetSize() const
{
    std::pair<int, int> size;
    size.first = mJ["grid"]["assets"]["width"];
    size.second = mJ["grid"]["assets"]["height"];
    return size;
}

std::pair<int, int> Assets::getGridSize() const
{
    std::pair<int, int> size;
    size.first = mJ["grid"]["width"];
    size.second = mJ["grid"]["height"];
    return size;
}

std::pair<int, int> Assets::getGridPosition() const
{
    std::pair<int, int> position;
    position.first = mJ["grid"]["xpos"];
    position.second = mJ["grid"]["ypos"];
    return position;
}

std::string Assets::getTitle() const
{
    return mJ["settings"]["title"];
}

std::string Assets::getTileAsset() const
{
    std::string str = mJ["tile"]["asset"];
    return mRelativePath + str;
}

std::pair<int, int> Assets::getTileSize() const
{
    std::pair<int, int> size;
    size.first = mJ["tile"]["width"];
    size.second = mJ["tile"]["height"];
    return size;
};

std::string Assets::getHighlightAsset() const
{
    std::string str = mJ["tile"]["highlight"];
    return mRelativePath + str;
}

std::string Assets::getFont() const
{
    std::string str = mJ["settings"]["font"];
    return mRelativePath + str;
}

int Assets::getFontSize() const
{
    return mJ["settings"]["fontSize"];
}

void Assets::printAssets() const
{
    std::cout << mJ.dump() << std::endl;
}

int Assets::getMinimumScores() const
{
    return mJ["settings"]["minimumScores"];
}

int Assets::getMinimumMatches() const
{
    return mJ["settings"]["minimumMatches"];
}

std::map<std::string, std::string> Assets::getSounds() const
{
    // create and print a JSON from the map
    json j = mJ["sounds"];
    std::cout << j << std::endl;

    // get the map out of JSON
    std::map<std::string, std::string> m2 = j;

    for (auto& sound : m2)
    {
        sound.second = mRelativePath + sound.second;
    }

    return m2;
}

std::string Assets::getButtonAsset() const
{
    std::string str = mJ["button"]["asset"];
    return mRelativePath + str;
}

std::pair<int, int> Assets::getButtonSize() const
{
    std::pair<int, int> size;
    size.first = mJ["button"]["width"];
    size.second = mJ["button"]["height"];
    return size;
}

std::string Assets::getGameOverAsset() const
{
    std::string str = mJ["gameover"]["asset"];
    return mRelativePath + str;
}
