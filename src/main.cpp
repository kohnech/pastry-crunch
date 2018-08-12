#include "App.h"
#include <iostream>

int main(int argc, char* argv[])
{
    try
    {
        std::cout << "Starting main loop..." << std::endl;
        App theApp;

        if (theApp.onInit() == false)
        {
            return EXIT_FAILURE;
        }
        theApp.start();
        theApp.join();
    }
    catch (std::exception& e)
    {
        std::cout << "Got exception: " << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}
