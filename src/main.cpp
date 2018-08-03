#include "CApp.h"
#include <iostream>

int main(int argc, char* argv[])
{
    std::cout << "Starting main loop..." << std::endl;
    CApp theApp;

    if (theApp.onInit() == false)
    {
        return EXIT_FAILURE;
    }

    SDL_Event event;

    // Main loop
    bool isRunning = true;
    while (isRunning)
    {
        while (SDL_PollEvent(&event))
        {
            theApp.onEvent(&event);
        }

        isRunning = theApp.onLoop();
        theApp.onRender();
    }

    return EXIT_SUCCESS;
}