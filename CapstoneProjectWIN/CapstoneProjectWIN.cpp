/*
Capstone Engine created by Alec Roberts and Steven Cole (team Alpha Sapphire)
*/
#include <iostream>
using namespace std;

//We only need to include the Engine.h file.
//All other header files are contained therein.
#include "Engine.h"

//Add command line parameters to allow SDL2 to recognize main
int main(int, char**)
{
    Engine* mainEng = new Engine(); //create the engine dynamically
    mainEng->makeWindow(640, 480, "Hello, World!"); //create the window with initial width, height, title
    mainEng->setSize(1920 / 2, 1080 / 2); //testing the setsize function
    
    //setting the resolution to a smaller area within the window
    mainEng->setResolution(1920 / 4, 1080 / 4); 

    //variables to be used for input
    int x = 0, y = 0;

    //adding a joystick to the engine.
    //if no joystick detected, this function should just exit with no problems
    Joystick testjoy;
    mainEng->addJoystick(&testjoy);

    //make the window full screen
    //mainEng->fullscreenWindow();

    //AUDIO TESTING
    Mix_Music* musicdata = nullptr; //this pointer will soon point to the music file
    musicdata = Mix_LoadMUS("robomb.wav"); //load in the music(WAV file created by Alec)
    if (!musicdata) {      //error message for if the music is not found
        cout << "could not find music" << endl;
    }
    Mix_VolumeMusic(50); //setting volume to 50%

    //This is the while loop for the game logic
    while (mainEng->getRunning()) { //loop will continue to run and update screen until 
                                    //end condition met, such as when the X is clicked

        mainEng->clearScreen(); //clear the screen to draw next frame

        //get joystick input to move the square on the screen
        //the values of 100 and -100 mean that's the range of the deadzone.
        if (testjoy.getRightStickY() > 100 || mainEng->getKey(SDL_SCANCODE_DOWN))
            y++;
        if (testjoy.getRightStickY() < -100 || mainEng->getKey(SDL_SCANCODE_UP))
            y--;
        if (testjoy.getRightStickX() < -100 || mainEng->getKey(SDL_SCANCODE_LEFT))
            x--;
        if (testjoy.getRightStickX() > 100 || mainEng->getKey(SDL_SCANCODE_RIGHT))
            x++;

        //setting up escape key as an exit option
        if (mainEng->getKey(SDL_SCANCODE_ESCAPE)) {
            mainEng->stop();
        }

        //We might wanna play the music here
        if (!Mix_PlayingMusic())    //this will loop the music when the track ends
            Mix_PlayMusic(musicdata, 0);

        //
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glBegin(GL_QUADS);
            glVertex2i(x, y);
            glVertex2i(x+10, y);
            glVertex2i(x+10, y+10);
            glVertex2i(x, y+10);
        glEnd();

        mainEng->drawScreen();
    }

    if (musicdata) {
        Mix_FreeMusic(musicdata);
    }

    delete mainEng;

    return 0;   
}
