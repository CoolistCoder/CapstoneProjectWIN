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

//set the behaviors for non-game-specific objects
void titleCameraBehavior(Entity*);
void musicBehavior(Entity*);

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
	titleScene->addEntity(testtext1); //add the text to the title

	//set the attributes for both text objects
	testtext1->setString("Press ENTER to start"); //set text 1's string
	testtext1->setSize(10, 10); //set text 1's size
	testtext1->setPosition(55, 20); //set text 1's position

	//create our sprite and add it to the title sequence
	Player* playerone = new Player;
	gameScene->addEntity(playerone);
	playerone->setPriority(3);

	//create a scoreboard for the player
	Score* playerScore = new Score;
	gameScene->addEntity(playerScore);
	playerScore->setPosition(0, 15);
	playerScore->setSize(16, 16);
	playerScore->setPriority(0);
	playerScore->givePlayer(playerone); //give the score a player to track


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

	//create the tiles that the player will need to avoid
	Tilemap* walltiles = new Tilemap; //instantiate the walls
	gameScene->addEntity(walltiles); //add the walls to the engine
	walltiles->loadImage("setpieces.png"); //load an image for the walls
	walltiles->createMap(walls, 20 * 16); //generate the map we need for the tiles
	walltiles->setSize(20, 16); //set the size of the map
	walltiles->frameCount(4, 1); //the map uses a tileset that is 1 down and 4 across
	walltiles->tileSize(24, 16); //the tiles on the map are 24 pixels across and 16 pixels down
	walltiles->setPriority(2);

	//give the player the walls
	playerone->wallIs(walltiles);

	//create an enemy
	Enemy* mainEnemy = new Enemy;
	mainEnemy->givePlayer(playerone);
	gameScene->addEntity(mainEnemy);
	mainEnemy->setPriority(4);

	//create a camera for the title sequence
	Camera* titlecamera = new Camera;
	titleScene->addEntity(titlecamera); //add the camera to the title
	titleScene->setActiveCamera(titlecamera);
	titlecamera->sizeToRenderer(); //set the camera's size to the render area
	titlecamera->setBehavior(titleCameraBehavior);

	//create the background for the title screen
	Background* title = new Background;
	titleScene->addEntity(title); //add the title graphic to the title sequence
	title->loadImage("LaserAvenger.jpg"); //load the title graphic
	title->setPosition(320, 0); //set the background far to the right
	title->setSize(320, 240); //make the size of the background equal to the size of the graphic
	title->setPriority(1);

	//create the music for the game sequence
	Sound* gameMusic = new Sound;
	gameScene->addEntity(gameMusic);
	gameMusic->loadMusic("robomb.wav");
	gameMusic->setVolume(40);
	gameMusic->setBehavior(musicBehavior);

	//create a wide box to hide the bottom of the screen
	Box* hidebox = new Box;
	gameScene->addEntity(hidebox);
	hidebox->setPosition(0, 255);
	hidebox->setSize(600, 16);


	//set up the loops

	//the title loop:
	//while the return key is not pressed or the engine is still active
	while (gameEngine->getRunning() && !Engine::getKey(SDL_SCANCODE_RETURN)) {
		//run the title sequence
		//if any of these are broken, we progress to the game screen
		titleScene->execute(); //we execute the title sequence
	}
	delete titleScene; //delete the title
	//once the title sequence has been completed, we go into the actual game
	while (gameEngine->getRunning()) {
		//run the game sequence
		gameScene->execute();
	}


	delete gameScene;


	delete gameEngine; //delete the game engine

	return 0;
}

void titleCameraBehavior(Entity* c) {
	//first, cast the entity to a camera object
	Camera* temp = static_cast<Camera*>(c);
	//now, make the camera move left a few steps

	static int waitx = 0;
	const int waitlimit = 320;

	if (waitx < waitlimit) {
		waitx++;
	}
	temp->focusTo(waitx, 0); //make the camera move to the side

}

void musicBehavior(Entity* m) {
	Sound* temp = static_cast<Sound*>(m);
	temp->play();
}

