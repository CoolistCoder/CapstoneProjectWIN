#include "Box.h"

void Box::defaultBehavior(Entity* e) {
	//the bare minimum behavior of a box is to draw
	static_cast<Box*>(e)->draw();
}

void Box::draw() {
	//create a surrogate variable to check and see if we need to make this independent from the camera or not
	int camx, camy;
	if (!this->independent) {
		camx = this->modposX;
		camy = this->modposY;
	}
	else {
		camx = 0;
		camy = 0;
	}


	//we only want to use our box drawing function if the visible value is true
	if (this->visible) {
		//we can largely copy the code we've used previously for the draw function
		glMatrixMode(GL_MODELVIEW); //change the matrix to the modelview matrix to modify objects drawn to the screen
		glLoadIdentity();	//change the active identity to the modelview matrix
		glBegin(GL_QUADS);	//draw quads
				glColor4ub(this->r, this->g, this->b, this->a); //adjust the color values of the box beforehand
				glVertex2i(this->x + camx, this->y + camy);	//top left
				glVertex2i(this->x + this->w + camx, this->y + camy);	//bottom left
				glVertex2i(this->x + this->w + camx, this->y + this->h + camy);	//bottom right
				glVertex2i(this->x + camx, this->y + this->h + camy);	//top right
		glEnd();	//stop drawing
		//TODO remove this for efficiency
		glColor4ub(255, 255, 255, 255);
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

void Box::modifyColor(Uint8 r, Uint8 g, Uint8 b) {
	//set the values
	this->r = r; //red
	this->g = g; //green
	this->b = b; //blue
}

void Box::modifyAlpha(Uint8 a) {
	//set the alpha value
	this->a = a;
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

	//by default, the square is white
	this->r = 255;
	this->g = 255;
	this->b = 255;
	this->a = 255;

	//by default the square is visible
	this->visible = true;

	//give the box a default behavior
	this->setBehavior(Box::defaultBehavior);
}

Box::~Box() {
	//TODO Auto-Generated Destructor Stub
}