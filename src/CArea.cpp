#include "CArea.h"
#include "CSurface.h"
#include "Define.h"

CArea CArea::AreaControl;

CArea::CArea() {
    AreaSize = 0;
}

CArea::~CArea() {
}

bool CArea::OnLoad(char* File) {
    printf("CArea::OnLoad... with File: %s\n", File);
    MapList.clear();

    FILE* FileHandle = fopen(File, "r");

    if(FileHandle == NULL) {
        return false;
    }

    char TilesetFile[255];

    fscanf(FileHandle, "%s\n", TilesetFile);
    printf("TilesetFile: %s\n", TilesetFile); // DEBUG

    if((Surf_Tileset = CSurface::OnLoad(TilesetFile)) == false) {
        fclose(FileHandle);

        return false;
    }

    char ch = fgetc(FileHandle);
    int test = (int)ch - 48; // convert ascii to int
    AreaSize = test;


    for (int X = 0; X < AreaSize; X++)
    {
        for (int Y = 0; Y < AreaSize; Y++)
        {
            char MapFile[255];

            fscanf(FileHandle, "%s ", MapFile);
            printf("MapFile: %s\n", MapFile);

            CMap tempMap;
            if (tempMap.OnLoad(MapFile) == false)
            {
                printf("Error CMAp.OnLoad...\n");
                fclose(FileHandle);

                return false;
            }

            tempMap.Surf_Tileset = Surf_Tileset;

            MapList.push_back(tempMap);
        }
        fscanf(FileHandle, "\n");
    }

    fclose(FileHandle);

    return true;
}

void CArea::OnRender(SDL_Surface* Surf_Display, int CameraX, int CameraY) {
    int MapWidth  = MAP_WIDTH * TILE_SIZE;
    int MapHeight = MAP_HEIGHT * TILE_SIZE;

    int FirstID = -CameraX / MapWidth;
    FirstID = FirstID + ((-CameraY / MapHeight) * AreaSize);

    for(int i = 0;i < 4;i++) {
        unsigned int ID = FirstID + ((i / 2) * AreaSize) + (i % 2);

        if(ID < 0 || ID >= MapList.size()) continue;

        int X = ((ID % AreaSize) * MapWidth) + CameraX;
        int Y = ((ID / AreaSize) * MapHeight) + CameraY;

        MapList[ID].OnRender(Surf_Display, X, Y);
    }
}

void CArea::OnCleanup() {
    if(Surf_Tileset) {
        SDL_FreeSurface(Surf_Tileset);
    }

    MapList.clear();
}
