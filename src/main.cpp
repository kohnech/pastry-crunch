#include "CApp.h"
#include <iostream>

int main(int argc, char *argv[]) {
    std::cout << "Starting main SDL2 first test..." << std::endl;
    CApp theApp;

    return theApp.onExecute();
}