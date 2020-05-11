/*
 * Capstone Engine developed by Alec Roberts and Steven Cole.
 * Started Jan 22 2020
 */
#include <random>
#include <iostream>
using namespace std;

//we only need to include the Engine.h file
#include "CapstoneProjectWIN.h"
#include "LaserAvenger.h"

//Define commandline parameters for SDL2
int main(int, char**) {
	//create the game engine and set the values we want for the game engine
	Engine* gameEngine = new Engine(); //instantiate the game engine
	gameEngine->makeWindow(1920 / 2, 1080 / 2, "Laser Avenger"); //create our window
	gameEngine->setResolution(1920 / 4, 1080 / 4); //set our resolution

	//instantiate a joystick so we can use at least 1
	Joystick* mainJoystick = new Joystick();
	//give the game engine the joystick
	gameEngine->addJoystick(mainJoystick);

	//we have two scenes: the title, and the gameplay scenes
	Scene* titleScene = new Scene(gameEngine);
	Scene* gameScene = new Scene(gameEngine);

	//use some text to see if the program works
	Text* testtext1 = new Text;
	Text* testtext2 = new Text;

	titleScene->addEntity(testtext1); //add the text to the title
	gameScene->addEntity(testtext2); //add the text to the game

	//set the attributes for both text objects
	testtext1->setString("This is the title screen"); //set text 1's string
	testtext1->setSize(10, 10); //set text 1's size
	testtext1->setPosition(0, 0); //set text 1's position
	testtext2->setString("This is the game screen"); //set text 2's string
	testtext2->setSize(10, 10); //set text 2's size
	testtext2->setPosition(0, 0); //set text 2's position

	//create our sprite and add it to the title sequence
	Player* playerone = new Player;
	gameScene->addEntity(playerone);

	//create the walls needed for the game
	int walls[] = {
			1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, //x20
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 //x16
	};

	Tilemap* walltiles = new Tilemap;
	gameScene->addEntity(walltiles);
	walltiles->loadImage("setpieces.png");
	walltiles->createMap(walls, 20 * 16);
	walltiles->setSize(20, 16);
	walltiles->frameCount(4, 1);
	walltiles->tileSize(24, 16);

	//give the player the walls
	playerone->wallIs(walltiles);

	//create an enemy
	Enemy* mainEnemy = new Enemy;
	mainEnemy->givePlayer(playerone);
	gameScene->addEntity(mainEnemy);

	//set up the loops

	//the title loop:
	//while the return key is not pressed or the engine is still active
	while (gameEngine->getRunning() && !Engine::getKey(SDL_SCANCODE_RETURN)) {
		//run the title sequence
		//if any of these are broken, we progress to the game screen
		titleScene->execute(); //we execute the title sequence
	}

	//once the title sequence has been completed, we go into the actual game
	while (gameEngine->getRunning()) {
		//run the game sequence
		gameScene->execute();
	}


	//delete the scenes in reverse order from which they appeared
	delete gameScene;
	delete titleScene;

	delete gameEngine; //delete the game engine

	return 0;
}

