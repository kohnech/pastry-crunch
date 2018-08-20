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

class Assets
{
public:
    Assets();
    void loadFile(std::string);
    void loadJson(json js);
    std::string getBackgroundPath();
    std::pair<int, int> getScreenSize();
    std::vector<std::string> getGridAssets();
    std::pair<int, int> getGridAssetSize();
    std::pair<int, int> getGridSize();
    std::pair<int, int> getGridPosition();
    std::string getTitle();
    std::string getTileAsset();
    std::pair<int, int> getTileSize();
    std::string getHighlightAsset();
    std::string getFont();
    int getFontSize();
    void printAssets();
    int getMinimumScores();
    int getMinimumMatches();
    std::map<std::string, std::string> getSounds();
    std::string getButtonAsset();
    std::pair<int, int> getButtonSize();


private:
    json mJ;
	std::string mRelativePath;
};
