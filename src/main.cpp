#include "App.h"
#include <iostream>

int main(int argc, char* argv[])
{
    try
    {
        std::cout << "Starting main loop..." << std::endl;
        App theApp;

        if (theApp.init() == false)
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

            isRunning = theApp.loop();
            theApp.render();
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Got exception: " << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}
