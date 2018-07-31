#include "CSurface.h"

#include <iostream>

#include <SDL_image.h>

CSurface::CSurface() {
}

SDL_Texture* CSurface::loadTexture(SDL_Renderer* renderer, std::string path )
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}


SDL_Surface* CSurface::OnLoad(const char* File) {
    SDL_Surface* Surf_Temp = NULL;
    SDL_Surface* Surf_Return = NULL;

    if((Surf_Temp = IMG_Load(File)) == NULL) {
        std::cout << "Could not open file: " << File << std::endl;
        std::cout << "Make sure it exist first." << std::endl;
        return NULL;
    }

    //Surf_Return = SDL_ConvertSurfaceFormat(Surf_Temp,
    //                                       SDL_PIXELFORMAT_UNKNOWN,
    //                                       0);
    //Surf_Return = SDL_DisplayFormatAlpha(Surf_Temp);
    Surf_Return = Surf_Temp;


    if (Surf_Return == NULL) {
        std::cout << "Could not convert surface format" << std::endl;
    }

    SDL_FreeSurface(Surf_Temp);

    return Surf_Return;
}

bool CSurface::OnDraw(SDL_Renderer* renderer, SDL_Texture* Surf_Src, int X, int Y) {
    std::cout << "OnDraw" << std::endl;
    if(Surf_Src == NULL) {
        return false;
    }

    SDL_Rect DestR;

    DestR.x = X;
    DestR.y = Y;

    SDL_RenderCopy(renderer, Surf_Src, NULL, &DestR);

    return true;
}