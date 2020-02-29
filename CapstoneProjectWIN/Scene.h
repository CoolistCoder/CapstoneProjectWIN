#pragma once
#include "Engine.h"
#include <functional>

class Scene
{
private:
	std::function<void(Scene*)> storedBehavior; //allows us to store a function within a variable
	Engine* knownEngine; //this gives our scene the current active engine

public:
	void giveEngine(Engine*); //simply gives an engine to the scene
	void setBehavior(void newBehavior(Scene* ns));
	void execute();

	Scene(Engine*);
	virtual ~Scene();
};

