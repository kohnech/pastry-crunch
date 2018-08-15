#include "Sounds.h"
#include <iostream>

Sounds Sounds::instance;

Sounds::Sounds()
{
}

Sounds::~Sounds()
{
    cleanup();
}


bool Sounds::load(Assets& assets)
{
    // Load SDL2_mixer lib
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
    {
        std::cout << "Could not open Mix_OpenAudio: " << Mix_GetError() << std::endl;
        return false;
    }

    // Load sound assets
    std::map<std::string, std::string> soundMap = assets.getSounds();

    for (auto asset: soundMap)
    {
        Mix_Chunk* TempSound = NULL;

        if((TempSound = Mix_LoadWAV(asset.second.c_str())) == NULL) {
            std::cout << "Error loading sound file: " << asset.second << Mix_GetError() << std::endl;
        }

        mSounds[asset.first] = TempSound;
    }
    return true;

}

void Sounds::cleanup()
{
    for (auto sound : mSounds)
    {
        Mix_FreeChunk(sound.second);
    }

    mSounds.clear();
    Mix_CloseAudio();
}

void Sounds::play(std::string ID)
{
    if(mSounds[ID] == NULL) return;

    Mix_PlayChannel(-1, mSounds[ID], 0);
}

void Sounds::stop()
{
    Mix_HaltChannel(-1); // Stop all channels
}
