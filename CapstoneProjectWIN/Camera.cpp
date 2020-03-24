#include "Camera.h"

void Camera::defaultBehavior(Entity* e) {
	//the camera doesn't need to do anything by default
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
		this->w = -(signed)this->getEngine()->getResW();
		this->h = -(signed)this->getEngine()->getResH();
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

	//set the camera default behavior
	this->setBehavior(Camera::defaultBehavior);
}

Camera::~Camera() {
	// TODO Auto-generated destructor stub
}