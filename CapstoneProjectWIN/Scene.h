#pragma once
#include "Engine.h"
#include "Entity.h"
#include "Box.h"
#include "Line.h"
#include "Sprite.h"
#include "Camera.h"
#include "Sound.h"
#include "Tile.h"
#include "Tilemap.h"
#include "Text.h"
#include <functional>
#include <vector>

class Scene {
private:
	std::function<void(Scene*)> storedBehavior; //allows us to store a function within a variable
	Engine* knownEngine; //this gives our scene the current active engine
	static std::vector<Scene*> allScenes; //all of the scenes loaded into memory
	static unsigned int numscenes; //this is the total number of scenes instanciated
	std::vector<Entity*> entitiesInScene; //all of the entities within the scene instance

	Camera* activeCamera; //the active camera of the scene

	static void defaultBehavior(Scene*); //the default behavior of the scene

public:
	void giveEngine(Engine*); //gives an engine to the Scene
	void setBehavior(void newBehavior(Scene* ns)); //set the behavior of the scene
	void addEntity(Entity*); //add an entity to the entity vector
	void stop(); //stop the engine stored within the scene
	Joystick* getJoystick(unsigned int); //get the joystick stored in the engine

	void setActiveCamera(Camera*); //set which camera is the main camera

	void execute(); //execute the scene's stored script

	//not operational
	//static void cleanup();	//deletes all instances of Scenes

	Scene(Engine*);
	virtual ~Scene();
};
