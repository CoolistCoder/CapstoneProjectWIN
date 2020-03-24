#pragma once

#include "Entity.h"

class Camera : public Entity {
protected:
	int x, y; //the x and y position of the camera
	int w, h; //the widthe and height of the camera's area

	static void defaultBehavior(Entity* e); //the default behavior of the camera

public:
	void focusTo(int, int); //changes the position of the camera
	void sizeToRenderer(); //sets the size of the camera to the engine's renderer
	int getX() { return this->x; }; //return the camera's x position
	int getY() { return this->y; }; //return the camera's y position
	int getW() { return this->w; }; //return the camera's width
	int getH() { return this->h; }; //return the camera's height

	void execute(); //camera's custom execute function

	Camera();
	virtual ~Camera();
};