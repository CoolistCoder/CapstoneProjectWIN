#include "Scene.h"

//there are always 0 scenes at the start
unsigned int Scene::numscenes = 0;
std::vector<Scene*> Scene::allScenes;

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
		this->entitiesInScene.push_back(newEntity); //give us the new entity
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
			if (this->entitiesInScene.at(i)->getPriority() < this->entitiesInScene.at(i + 1)->getPriority()) {
				//the swap is not complete, therefore the finished variable is false
				finished = false;
				//perform a swap
				Entity* temp = this->entitiesInScene.at(i);
				this->entitiesInScene.at(i) = this->entitiesInScene.at(i + 1);
				this->entitiesInScene.at(i + 1) = temp;
			}
		}
	}
	//now execute each entity
	for (unsigned int i = 0; i < this->entitiesInScene.size(); i++) {
		this->entitiesInScene.at(i)->execute();
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
	//This object NEEDS to know what an engine is. If it doesn't, itdefeats the point
	this->giveEngine(newEngine);
	Scene::numscenes++; //increment the number of scenes
}

Scene::~Scene() {
	//TODO Auto-Generated Destructor Stub

	//clean up entities loaded into the scene
	for(unsigned int i=0; i < this->entitiesInScene.size(); i++){
		delete this->entitiesInScene.at(i);
	}
	Scene::numscenes--; //decrement the number of scenes
}