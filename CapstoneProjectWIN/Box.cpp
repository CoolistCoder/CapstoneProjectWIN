#include "Box.h"

void Box::defaultBehavior(Entity* e) {
	//the bare minimum behavior of a box is to draw
	static_cast<Box*>(e)->draw();
}

void Box::draw() {
	//TODO replace directdraw mode with vertex mode
	//we only want to use our box drawing function if the visible value is true
	if (this->visible) {
		//we can largely copy the code we've used previously for the draw function
		glMatrixMode(GL_MODELVIEW); //change the matrix to the modelview matrix to modify objects drawn to the screen
		glLoadIdentity();	//change the active identity to the modelview matrix
		glBegin(GL_QUADS);	//draw quads
				glVertex2i(this->x, this->y);	//top left
				glVertex2i(this->x+this->w, this->y);	//bottom left
				glVertex2i(this->x + this->w, this->y+this->h);	//bottom right
				glVertex2i(this->x, this->y + this->h);	//top right
		glEnd();	//stop drawing
		//this will draw our box
	}
}

void Box::setPosition(int x, int y) {
	//no matter wgar, the position of the box will be valid
	this->x = x;
	this->y = y;
}

void Box::setSize(unsigned int w, unsigned int h) {
	//the width and height are only valid if unsigned
	this->w = w;
	this->h = h;
}

void Box::execute() {
	//just execute the stored code
	this->storedBehavior(this);
}

Box::Box() {
	//TODO Auto-Generated Constructor Stub
	//use default values to define the size of the box
	this->w = 1;
	this->h = 1;
	this->x = 0;
	this->y = 0;

	//by default the square is visible
	this->visible = true;

	//give the box a default behavior
	this->setBehavior(Box::defaultBehavior);
}

Box::~Box() {
	//TODO Auto-Generated Destructor Stub
}