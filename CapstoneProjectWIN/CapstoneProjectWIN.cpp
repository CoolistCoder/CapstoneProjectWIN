/*
 * Capstone Engine developed by Alec Roberts and Steven Cole.
 * Started Jan 22 2020
 */
#include <random>
#include <iostream>
using namespace std;

//we only need to include the Engine.h file
#include "CapstoneProjectWIN.h"


//Define commandline parameters for SDL2
int main(int, char**) {
	//create the game engine and set the values we want for the game engine
	Engine* gameEngine = new Engine(); //instantiate the game engine
	gameEngine->makeWindow(1920 / 2, 1080 / 2, "Game"); //create our window
	gameEngine->setResolution(1920 / 4, 1080 / 4); //set our resolution

	//instantiate a joystick so we can use at least 1
	Joystick* mainJoystick = new Joystick();
	//give the game engine the joystick
	gameEngine->addJoystick(mainJoystick);

	//code goes here!


	delete gameEngine; //delete the game engine
	return 0;
}