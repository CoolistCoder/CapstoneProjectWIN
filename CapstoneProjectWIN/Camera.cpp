#include "Camera.h"

void Camera::defaultBehavior(Entity* e) {
	//set the camera's size to the renderer
	static_cast<Camera*>(e)->sizeToRenderer();
}

void Camera::focusTo(int x, int y) {
	//focus the camera to a new position
	//because of the way the camera works, it is opposite to whatever is on the screen
	//therefore, everything is inverse
	this->x = -x;
	this->y = -y;
}

void Camera::sizeToRenderer() {
	//By default, the camera just needs the renderer's size
	//So we will simply give it the renderer's size for later
	//make sure we have an engine to get this information from
	if (this->getEngine()) {
		//niw we need to get the inverse of the width and the height, as per how the camera works
		this->isToRenderer = true; //this is now to the renderer so this becomes true
		this->w = this->getEngine()->getResW();
		this->h = this->getEngine()->getResH();
		this->setViewArea(this->x, this->y, this->w, this->h);
	}
}

void Camera::toCustomSize(int w, int h) {
	//first, change the bool
	this->isToRenderer = false;
	this->w = w;
	this->h = h;

	if (this->getEngine()) { //if the engine is recognized, center the view
		this->setViewArea(
			(this->getEngine()->getResW() / 2) - (this->w / 2),
			(this->getEngine()->getResH() / 2) - (this->h / 2),
			this->w,
			this->h);
	}
	else { //if the engine isn't recognized, just leave it up in the top left corner
		this->setViewArea(this->x, this->y, this->w, this->h);
	}
}

void Camera::setViewArea(int x, int y, int w, int h) {
	//this will set the view area of the camera
	if (x >= this->x && y >= this->y && w <= this->w && h <= this->h) {
		this->viewareaX = x; //the only things that will be drawn on the screen
		this->viewareaY = y; //will be anything within these parameters
		this->viewareaW = w; //therefore, if the position of the object is within
		this->viewareaH = h; //these parameters, it will draw just fine
	}
}

void Camera::execute() {
	//simply run the default behavior
	this->storedBehavior(this);
}

Camera::Camera() {
	// TODO Auto-generated constructor stub
	//everything may default to zero
	this->x = 0;
	this->y = 0;
	this->w = 0;
	this->h = 0;

	this->isToRenderer = true; //by default, the camera is simply to the same size as the renderer

	this->setViewArea(0, 0, 0, 0); //keep the view area defaulted until the camera is added to the list of scenes

	//set the camera default behavior
	this->setBehavior(Camera::defaultBehavior);
}

Camera::~Camera() {
	// TODO Auto-generated destructor stub
}