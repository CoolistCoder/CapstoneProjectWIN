/*
Capstone Engine created by Alec Roberts and Steven Cole (team Alpha Sapphire)
*/
#include <iostream>
using namespace std;

#include "Engine.h"

//Add command line parameters to allow SDL2 to recognize main
int main(int, char**)
{
    Engine* mainEng = new Engine();
    mainEng->makeWindow(640, 480, "Hello, World!");
    mainEng->setSize(1920 / 2, 1080 / 2);

    mainEng->setResolution(1920 / 4, 1080 / 4);

    int x = 0, y = 0;

    Joystick testjoy;
    mainEng->addJoystick(&testjoy);

    mainEng->fullscreenWindow();

    Mix_Music* musicdata = nullptr;
    musicdata = Mix_LoadMUS("robomb.wav");
    if (!musicdata) {
        cout << "could not find music" << endl;
    }
    Mix_VolumeMusic(50);


    while (mainEng->getRunning()) {

        mainEng->clearScreen();

        if (testjoy.getRightStickY() > 100 || mainEng->getKey(SDL_SCANCODE_DOWN))
            y++;
        if (testjoy.getRightStickY() < -100 || mainEng->getKey(SDL_SCANCODE_UP))
            y--;
        if (testjoy.getRightStickX() < -100 || mainEng->getKey(SDL_SCANCODE_LEFT))
            x--;
        if (testjoy.getRightStickX() > 100 || mainEng->getKey(SDL_SCANCODE_RIGHT))
            x++;

        if (mainEng->getKey(SDL_SCANCODE_ESCAPE)) {
            mainEng->stop();
        }

        if (!Mix_PlayingMusic())
            Mix_PlayMusic(musicdata, 0);

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
