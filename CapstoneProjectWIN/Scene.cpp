#include "Scene.h"

//there are always 0 scenes at the start
unsigned int Scene::numscenes = 0;
std::vector<Scene*> Scene::allScenes;

void Scene::defaultBehavior(Scene* defaultScene) {
	//by default, the engine will die down when the escape key is hit
	if (Engine::getKey(SDL_SCANCODE_ESCAPE)) {
		defaultScene->stop();
	}
}

void Scene::giveEngine(Engine* newEngine) {
	if (newEngine) { //we only want to set this if the engine isn't null
		this->knownEngine = newEngine; //if the engine isn't null, simply put it in there
	}
}

void Scene::setBehavior(void newBehavior(Scene* ns)) {
	if (newBehavior) { //if the address location of the function is valid
		this->storedBehavior = newBehavior; //store the address of the function
	}
}

void Scene::addEntity(Entity* newEntity) {
	//only add entity if the entity isn't null
	if (newEntity) {
		newEntity->setEngine(this->knownEngine); //give the entity access to this engine
		this->entitiesInScene.push_back(newEntity); //give us the new entity
	}
}

void Scene::stop() {
	//kill the engine
	this->knownEngine->stop();
}

Joystick* Scene::getJoystick(unsigned int index) {
	//handle returning the joystick like the engine
	return this->knownEngine->getJoystick(index);
}

void Scene::setActiveCamera(Camera* c) {
	//as long as we have a camera, we can make it active
	if (c) {
		this->activeCamera = c;
	}
}

void Scene::execute() {
	//the execute function works like a normal loop
	//executed within the main loop

	//clear the screen
	this->knownEngine->clearScreen();

	//perform any behavior that is stored
	this->storedBehavior(this);

	//handle all of the entities here
	//first, sort based on priority
	//TODO: USE A FASTER SORTING ALGORITHM
	bool finished = false; //before we start, we need our condition
	while (!finished) {
		//set condition to true
		finished = true; //this will cause a break if a sort isn't performed
		for (unsigned int i = 0; i < this->entitiesInScene.size() - 1; i++) {
			//we need to perform a comparison with each member
			if (this->entitiesInScene[i]->getPriority() < this->entitiesInScene[i + 1]->getPriority()) {
				//the swap is not complete, therefore the finished variable is false
				finished = false;
				//perform a swap
				Entity* temp = this->entitiesInScene[i];
				this->entitiesInScene[i] = this->entitiesInScene[i + 1];
				this->entitiesInScene[i + 1] = temp;
			}
		}
	}

	//we need the camera to modify the offset of all entities
	if (this->activeCamera) {
		//if the camera exists, proceed to loop through all the entities and modify their positions
		for (int i = 0; i < this->entitiesInScene.size(); i++) {
			this->entitiesInScene[i]->modifyOffset(this->activeCamera->getX(), this->activeCamera->getY());
			this->entitiesInScene[i]->modifyRenderArea(this->activeCamera->getW(), this->activeCamera->getH());
			this->entitiesInScene[i]->setViewData(
				this->activeCamera->getviewX(),
				this->activeCamera->getviewY(),
				this->activeCamera->getviewW(),
				this->activeCamera->getviewH()
			);
			this->entitiesInScene[i]->assigned(); //now we have a camera, so we can say the entity has been assigned
		}
	}

	//now execute each entity
	for (unsigned int i = 0; i < this->entitiesInScene.size(); i++) {
		this->entitiesInScene[i]->execute();
	}

	//draw the screen
	this->knownEngine->drawScreen();
}

//Not Operational
/*void Scene::cleanup() {
	//go through each instance of scene and delete it from memory
	for (unsigned int i = 0; i < Scene::allScenes.size(); i++) {
		delete Scene::allScenes.at(i);
	}
}*/

Scene::Scene(Engine* newEngine) {
	//TODO Auto-Generated constructor stub
	//This object NEEDS to know what an engine is. If it doesn't, it defeats the point of having a scene object
	this->giveEngine(newEngine);
	this->setBehavior(Scene::defaultBehavior);
	this->activeCamera = nullptr; //set up with a null camera
	Scene::numscenes++; //increment the number of scenes
}

Scene::~Scene() {
	//TODO Auto-Generated Destructor Stub

	//clean up entities loaded into the scene
	for(unsigned int i=0; i < this->entitiesInScene.size(); i++){
		delete this->entitiesInScene[i];
	}
	Scene::numscenes--; //decrement the number of scenes
}