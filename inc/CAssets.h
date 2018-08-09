#pragma once

/*!
 * This file loads the assets in particular 5 colors and background
 * skins. It is of course configurable from the json file.
 */
#include "json.hpp"
#include <utility>
#include <vector>
#include <string>

using json = nlohmann::json;

class CAssets
{
public:
    CAssets();
    void load();
    std::string getBackgroundPath();
    std::pair<int,int> getScreenSize();
    std::vector<std::string> getGridAssets();

private:
    json mJ;

};
