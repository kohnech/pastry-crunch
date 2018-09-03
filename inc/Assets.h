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
    explicit Assets();
    ~Assets() = default;
    void loadFile(std::string);
    void loadJson(json js);
    std::string getBackgroundPath() const;
    std::pair<int, int> getScreenSize() const;
    std::vector<std::string> getGridAssets() const;
    std::pair<int, int> getGridAssetSize() const;
    std::pair<int, int> getGridSize() const;
    std::pair<int, int> getGridPosition() const;
    std::string getTitle() const;
    std::string getTileAsset() const;
    std::pair<int, int> getTileSize() const;
    std::string getHighlightAsset() const;
    std::string getFont() const;
    int getFontSize() const;
    void printAssets() const;
    int getMinimumScores() const;
    int getMinimumMatches() const;
    std::map<std::string, std::string> getSounds() const;
    std::string getButtonAsset() const;
    std::pair<int, int> getButtonSize() const;
    std::string getGameOverAsset() const;


private:
    json mJ;
    std::string mRelativePath;
};
