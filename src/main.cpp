#include "CApp.h"
#include <iostream>

int main(int argc, char *argv[]) {
    std::cout << "Starting main SDL2 first test..." << std::endl;
    CApp theApp;

    if(theApp.onInit() == false) {
        return EXIT_FAILURE;
    }

    SDL_Event Event;

    // Main loop
    bool isRunning = true;
    while(isRunning) {
        while(SDL_PollEvent(&Event)) {
            theApp.onEvent(&Event);
        }

        isRunning = theApp.onLoop();
        theApp.onRender();
    }

    theApp.onCleanup();

    return EXIT_SUCCESS;
}