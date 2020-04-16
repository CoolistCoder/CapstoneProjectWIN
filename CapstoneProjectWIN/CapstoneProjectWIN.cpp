/*
Capstone Engine created by Alec Roberts and Steven Cole (team Alpha Sapphire)
*/
#include <iostream>
using namespace std;

//We only need to include the Engine.h file.
//All other header files are contained therein.
#include "Engine.h"
#include "Scene.h"

void sceneBehavior(Scene*);
void boxBehavior(Entity*);
void backgroundBehavior(Entity*);
void tileBehavior(Entity*);
void cameraBehavior(Entity*);

//Add command line parameters to allow SDL2 to recognize main
int main(int, char**)
{
    Engine* mainEng = new Engine(); //create the engine dynamically
    mainEng->makeWindow(640, 480, "Hello, World!"); //create the window with initial width, height, title
    mainEng->setSize(1920 / 2, 1080 / 2); //testing the setsize function
    
    //setting the resolution to a smaller area within the window
    mainEng->setResolution(1920 / 4, 1080 / 4); 

    //slow down the frame rate
    mainEng->setFPS(60);

    //adding a joystick to the engine.
    //if no joystick detected, this function should just exit with no problems
    Joystick testjoy;
    mainEng->addJoystick(&testjoy);

    //create a scene instance
    Scene* scene1 = new Scene(mainEng);
    scene1->setBehavior(sceneBehavior);

    //create an entity
    //Entity* newbox = new Box;
    Tile* newTile = new Tile;

    newTile->loadImage("North_Star_background.png");
    newTile->setFrameCount(2,2);
    

    //give the entity something to do
   // newbox->setBehavior(boxBehavior);

    //give the box to the scene
    //scene1->addEntity(newbox);
    scene1->addEntity(newTile);

    //make the window full screen
    //mainEng->fullscreenWindow();

    //AUDIO TESTING
    /*
    Mix_Music* musicdata = nullptr; //this pointer will soon point to the music file
    musicdata = Mix_LoadMUS("robomb.wav"); //load in the music(WAV file created by Alec)
    if (!musicdata) {      //error message for if the music is not found
        cout << "could not find music" << endl;
    }
    Mix_VolumeMusic(50); //setting volume to 50%
    */

    //static_cast<Background*>(newBackground)->flipY();
    //static_cast<Background*>(newBackground)->flipX();

    newTile->setSize(100,150);
    newTile->setBehavior(tileBehavior);
    

    //create a new camera to demonstrate the camera moving the entities
    Camera* newcamera = new Camera();
    newcamera->attachEntity(newTile); //give our camera the tile
    newcamera->setBehavior(cameraBehavior);
    scene1->addEntity(newcamera); //add the camera to the scene
    scene1->setActiveCamera(newcamera);
    newTile->setPriority(1);
    //newcamera->sizeToRenderer();
    newcamera->modifyOffset(0,0);
    newcamera->toCustomSize(320,240);
    newcamera->setViewArea(200,200,20,20);

    //create a box to check for the bounds of the camera
    Box* tempbox = new Box();
    tempbox->setSize(newcamera->getviewW(), newcamera->getviewH());
    tempbox->setPosition(newcamera->getviewX(), newcamera->getviewY());
    tempbox->setColor(255, 0, 0);
    tempbox->setTransparency(100);
    scene1->addEntity(tempbox);
    tempbox->independentFromCamera();

    cout << newcamera->getW() << ", " << newcamera->getH() << endl;

    //This is the while loop for the game logic
    while (mainEng->getRunning()) { //loop will continue to run and update screen until 
                                    //end condition met, such as when the X is clicked
        
        scene1->execute();

    }

    /*if (musicdata) {
        Mix_FreeMusic(musicdata);
    }*/

    //delete all scenes
    delete scene1;

    //clean up engine(this will clean it up on its own)
    delete mainEng;

    return 0;   
}


void sceneBehavior(Scene* ns) {
    /*Not necessary anymore!!!
    //This is a demo function that takes the 
    static int x, y;

    //get joystick input to move the square on the screen
    //the values of 100 and -100 mean that's the range of the deadzone.
    if (Engine::getKey(SDL_SCANCODE_DOWN))
        y++;
    if (Engine::getKey(SDL_SCANCODE_UP))
        y--;
    if (Engine::getKey(SDL_SCANCODE_LEFT))
        x--;
    if (Engine::getKey(SDL_SCANCODE_RIGHT))
        x++;

    //setting up escape key as an exit option
    if (Engine::getKey(SDL_SCANCODE_ESCAPE)) {
        mainEng->stop();
    }

    //We might wanna play the music here
    if (!Mix_PlayingMusic())    //this will loop the music when the track ends
        Mix_PlayMusic(musicdata, 0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glBegin(GL_QUADS);
    glVertex2i(x, y);
    glVertex2i(x + 10, y);
    glVertex2i(x + 10, y + 10);
    glVertex2i(x, y + 10);
    glEnd();
    */
}

void boxBehavior(Entity* b) {
    Box* temp = static_cast<Box*>(b);

    //save position of the square into variables
    int x = temp->getX(), y = temp->getY();

    //allow us to modify those variables with the keyboard
    if (Engine::getKey(SDL_SCANCODE_DOWN))
        y++;
    if (Engine::getKey(SDL_SCANCODE_UP))
        y--;
    if (Engine::getKey(SDL_SCANCODE_LEFT))
        x--;
    if (Engine::getKey(SDL_SCANCODE_RIGHT))
        x++;

    //put those modified variables into the box
    temp->setPosition(x, y);

    //draw the box
    temp->draw();
}

void backgroundBehavior(Entity* b) {
    Background* temp = static_cast<Background*>(b);
    //static int rotation = 0;

    //rotation++;

    //temp->setRotation(rotation);

    temp->draw();
}

void tileBehavior(Entity* t) {
    Tile* temp = static_cast<Tile*>(t);
   /*
    static int x = 0;
    static int y = 0;
    static int pause = 0;
    pause++;
    if (pause == 10) {
        pause = 0;
        if (x < 4)
            x++;
        if (y < 1)
            y++;
    }
    temp->setPosition(x, y);
    */
    temp->setPosition(0,0);
    temp->draw();
}

void cameraBehavior(Entity* c) {
    Camera* temp = static_cast<Camera*>(c);
    Tile* at = static_cast<Tile*>(temp->getAttachedEntity(0));
    //temp->sizeToRenderer();

    static int x = 0, y = 0;

    y--;

    temp->focusTo(x, y);

    /*
    temp->focusTo(
        (at->getPosX()* at->getPosW()) + at->getPosW() / 2 - (temp->getEngine()->getResW()/2), 
        (at->getPosY()* at->getPosH()) + at->getPosH() / 2 - (temp->getEngine()->getResH() /2)
   );
    */
}