#pragma once

#include <SDL2/SDL.h>

#include <string>

class CSurface
{
public:
    CSurface();

public:
    static SDL_Texture* loadTexture(SDL_Renderer* renderer, std::string path);

    static SDL_Surface* loadSurface(std::string path);

    /*!
     * Load an image bmp to a surface
     * @param File The image to load relative to exe or absolute path
     * @return True if successful
     */
    static SDL_Surface* OnLoad(const char* File);

    /*!
     * Draw an image on source
     * @param Surf_Dest The destination surface
     * @param Surf_Src The source surface
     * @param x Destination x position
     * @param y Destination y position
     * @return True if successful
     */
    static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int x, int y);

    /*!
     * Draw a partial image on source
     * @param Surf_Dest The destination surface
     * @param Surf_Src The source surface
     * @param x Destination x position
     * @param y Destination y position
     * @param x2 Source partial start x position
     * @param y2 Source partial start y position
     * @param w Width of source image
     * @param h Height of source image
     * @return True if successful
     */
    static bool
    OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int x, int y, int x2, int y2, int w, int h);

    static bool Transparent(SDL_Surface* texture, int r, int g, int b);
};