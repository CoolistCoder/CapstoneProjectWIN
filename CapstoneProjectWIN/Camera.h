#pragma once
#include "Entity.h"

class Camera : public Entity {
protected:
	int x, y; //the x and y position of the camera
	int w, h; //the widthe and height of the camera's area
	bool isToRenderer; //this determines whether or not the width and height of the camera is to the renderer or not

	int viewareaX, viewareaY, viewareaW, viewareaH; //this is the area the camera will allow entities to render within (context to renderer)

	static void defaultBehavior(Entity* e); //the default behavior of the camera

public:
	void focusTo(int, int); //changes the position of the camera
	void sizeToRenderer(); //sets the size of the camera to the engine's renderer
	int getX() { return this->x; }; //return the camera's x position
	int getY() { return this->y; }; //return the camera's y position
	int getW() { return this->w; }; //return the camera's width
	int getH() { return this->h; }; //return the camera's height
	void toCustomSize(int, int); //makes the camera's render zone a custom size
	bool getMode() { return this->isToRenderer; }; //returns the isToRenderer variable
	void setViewArea(int, int, int, int); //set the view area information
	int getviewX() { return this->viewareaX; }; //get the x view
	int getviewY() { return this->viewareaY; };//get the y view
	int getviewW() { return this->viewareaW; };//get the w view
	int getviewH() { return this->viewareaH; };//get the h view

	void execute(); //camera's custom execute function

	Camera();
	virtual ~Camera();
};