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
	}
}

void Camera::toCustomSize(int w, int h) {
	//TODO implement this later
	//first, change the bool
	this->isToRenderer = false;
	this->w = w;
	this->h = h;
}

void Camera::setViewArea(int x, int y, int w, int h){
	if (x >= this->x && y >= this->y && w <= this->w && h <= this->h) {
		this->viewareaX = x;
		this->viewareaY = y;
		this->viewareaW = w;
		this->viewareaH = h;
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

	//set the camera default behavior
	this->setBehavior(Camera::defaultBehavior);
}

Camera::~Camera() {
	// TODO Auto-generated destructor stub
}