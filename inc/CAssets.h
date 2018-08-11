#pragma once

/*!
 * This file loads the assets in particular 5 colors and background
 * skins. It is of course configurable from the json file.
 */
#include "json.hpp"
#include <string>
#include <utility>
#include <vector>

using json = nlohmann::json;

class CAssets
{
public:
    CAssets();
    void load(std::string);
    std::string getBackgroundPath();
    std::pair<int, int> getScreenSize();
    std::vector<std::string> getGridAssets();
    std::pair<int, int> getGridAssetSize();
    std::pair<int, int> getGridPosition();
    std::string getTitle();
    std::string getTileAsset();
    std::pair<int, int> getTileSize();

private:
    json mJ;
};
