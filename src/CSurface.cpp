#include "CSurface.h"

#include <iostream>

#include <SDL_image.h>


SDL_Surface* Surface::OnLoad(std::string File)
{
    return loadImage(File);
}
/*
SDL_Texture* Surface::loadTexture(SDL_Renderer* renderer, std::string path)
{
    // The final texture
    SDL_Texture* newTexture = NULL;

    // Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        // Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(),
SDL_GetError());
        }

        // Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}*/
SDL_Texture* Surface::loadTexture(SDL_Renderer* renderer, const std::string& str)
{
    // Load image as SDL_Surface

    SDL_Texture* texture = IMG_LoadTexture(renderer, str.c_str());
    if (texture == nullptr)
    {
        std::cout << "Failed to load texture " << str << " error : " << SDL_GetError() << std::endl;
        return nullptr;
    }

    return texture;
}

SDL_Surface* Surface::loadImage(const std::string path)
{
    printf("Surface::loadImage... %s\n", path.c_str());
    // Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }

    return loadedSurface;
}

SDL_Surface* Surface::loadBmp(const std::string File)
{
    SDL_Surface* Surf_Temp;

    Surf_Temp = SDL_LoadBMP(File.c_str());
    if (Surf_Temp == NULL)
    {
        printf("Loading BMP Failed: %s\n", SDL_GetError());
        return NULL;
    }

    return Surf_Temp;
}

bool Surface::OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int x, int y)
{
    if (Surf_Dest == NULL || Surf_Src == NULL)
    {
        printf("Surface Drawing failed: %s\n", SDL_GetError());
        return false;
    }

    SDL_Rect DestR;
    DestR.x = x;
    DestR.y = y;

    SDL_BlitSurface(Surf_Src, NULL, Surf_Dest, &DestR);

    return true;
}

bool Surface::OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int x, int y, int x2, int y2, int w, int h)
{
    if (Surf_Dest == NULL || Surf_Src == NULL)
    {
        printf("Surface Drawing failed: %s\n", SDL_GetError());
        return false;
    }

    SDL_Rect DestR;
    DestR.x = x;
    DestR.y = y;

    SDL_Rect SrcR;
    SrcR.x = x2;
    SrcR.y = y2;
    SrcR.w = w;
    SrcR.h = h;

    SDL_BlitSurface(Surf_Src, &SrcR, Surf_Dest, &DestR);

    return true;
}

bool Surface::Transparent(SDL_Surface* Surf_Dest, int r, int g, int b)
{
    if (Surf_Dest == NULL)
    {
        return false;
    }

    SDL_SetColorKey(Surf_Dest, SDL_TRUE, SDL_MapRGB(Surf_Dest->format, r, g, b));

    return true;
}
