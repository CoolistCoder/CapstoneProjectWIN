/*
Capstone Engine created by Alec Roberts and Steven Cole (team Alpha Sapphire)
*/

//All of the files needed to create a functional engine
#include <Windows.h>
#include <SDL.h>
#include <gl/GL.h>

//Quality of life files that make coding easier.
#include <iostream>
using namespace std;

//Add command line parameters to allow SDL2 to recognize main
int main(int, char**)
{
    //Produce an error message if the initialization process fails
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        //This will show a message upon failure to initialize
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", "Unable to init SDL2", nullptr);
        return 0;    //TODO remove the early return upon failure
    };

    //This is the part where we make a window!
    SDL_Window* window; //Create our window pointer
    //Create a window designed for opengl that we can scale
    window = SDL_CreateWindow("Hello, World!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    SDL_Delay(3000);    //Wait for 3 seconds so we can see the window
    SDL_DestroyWindow(window);  //Delete the window from memory
    SDL_Quit(); //properly and cleanly close SDL

    return 0;   
}
