#include "Scene.h"

void Scene::giveEngine(Engine* newEngine) {
	if (newEngine) {
		this->knownEngine = newEngine;
	}
}

void Scene::setBehavior(void newBehavior(Scene* ns)) {
	if (newBehavior) {
		this->storedBehavior = newBehavior;
	}
}

void Scene::execute() {
	this->knownEngine->clearScreen();

	this->storedBehavior(this);

	this->knownEngine->drawScreen();
}

Scene::Scene(Engine* newEngine) {
	//TODO 
	//This object NEEDS to know what an engine is. If it doesn't, itdefeats the point
	this->giveEngine(newEngine);
}

Scene::~Scene() {

}