#pragma once

#include <SDL2/SDL.h>

#include <string>

namespace Surface
{

SDL_Surface* OnLoad(std::string File);

SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& path);

/*!
 * Load PNG image with SDL2_image
 * @param path Path to image to laod
 * @return True if successful
 */
SDL_Surface* loadImage(const std::string path);

/*!
 * Load an BMP image to a surface
 * @param File The image to load relative to exe or absolute path
 * @return True if successful
 */
SDL_Surface* loadBmp(const std::string File);

/*!
 * Draw an image on source
 * @param Surf_Dest The destination surface
 * @param Surf_Src The source surface
 * @param x Destination x position
 * @param y Destination y position
 * @return True if successful
 */
bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int x, int y);

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
bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int x, int y, int x2, int y2, int w, int h);

bool Transparent(SDL_Surface* texture, int r, int g, int b);
}