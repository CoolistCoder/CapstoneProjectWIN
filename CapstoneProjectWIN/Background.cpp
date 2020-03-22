#include "Background.h"

void Background::defaultBehavior(Entity* e)
{
	static_cast<Background*>(e)->draw();
}

void Background::draw() {

	glMatrixMode(GL_TEXTURE); //the texture matrix will be the matrix we will perform our operations on
	glLoadIdentity(); //load the identity matrix

	//adjust the matrix to the size of our image
	glScaled(1.0 / this->storedSource->w, 1.0 / this->storedSource->h, 1.0); //the scale will be derived from the image dimensions

	//now use modelview for drawing the image
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//set up the parameters for drawing the image so it uses the pixels
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//bind this texture to our image
	glBindTexture(GL_TEXTURE_2D, this->image);

	//enable texture drawing
	glEnable(GL_TEXTURE_2D);

	if (flagX) {
		glBegin(GL_QUADS);
			glTexCoord2i(this->storedSource->w, 0);				//top left of texture
			glVertex2i(0, 0);	//top left of background

			glTexCoord2i(0, 0);				//top right of texture
			glVertex2i(this->knownEngine->getResW(), 0);	//top right of background

			glTexCoord2i(0, this->storedSource->h);				//bottom right of texture
			glVertex2i(this->knownEngine->getResW(), this->knownEngine->getResH());	//bottom right of background

			glTexCoord2i(this->storedSource->w, this->storedSource->h);				//bottom left of texture
			glVertex2i(0, this->knownEngine->getResH());	//bottom left of background
		glEnd();
	}
	else if (flagY) {
		glBegin(GL_QUADS);
			glTexCoord2i(0, this->storedSource->h);				//top left of texture
			glVertex2i(0, 0);	//top left of background

			glTexCoord2i(this->storedSource->w, this->storedSource->h);				//top right of texture
			glVertex2i(this->knownEngine->getResW(), 0);	//top right of background

			glTexCoord2i(this->storedSource->w, 0);				//bottom right of texture
			glVertex2i(this->knownEngine->getResW(), this->knownEngine->getResH());	//bottom right of background

			glTexCoord2i(0, 0);				//bottom left of texture
			glVertex2i(0, this->knownEngine->getResH());	//bottom left of background
		glEnd();
	}
	else if (flagX && flagY) {
		glBegin(GL_QUADS);
			glTexCoord2i(this->storedSource->w, this->storedSource->h);				//top left of texture
			glVertex2i(0, 0);	//top left of background

			glTexCoord2i(0, this->storedSource->h);				//top right of texture
			glVertex2i(this->knownEngine->getResW(), 0);	//top right of background

			glTexCoord2i(0, 0);				//bottom right of texture
			glVertex2i(this->knownEngine->getResW(), this->knownEngine->getResH());	//bottom right of background

			glTexCoord2i(this->storedSource->w, 0);				//bottom left of texture
			glVertex2i(0, this->knownEngine->getResH());	//bottom left of background
		glEnd();
	}
	else {
		glBegin(GL_QUADS);
			glTexCoord2i(0, 0);				//top left of texture
			glVertex2i(0, 0);	//top left of background

			glTexCoord2i(this->storedSource->w, 0);				//top right of texture
			glVertex2i(this->knownEngine->getResW(), 0);	//top right of background

			glTexCoord2i(this->storedSource->w, this->storedSource->h);				//bottom right of texture
			glVertex2i(this->knownEngine->getResW(), this->knownEngine->getResH());	//bottom right of background

			glTexCoord2i(0, this->storedSource->h);				//bottom left of texture
			glVertex2i(0, this->knownEngine->getResH());	//bottom left of background
		glEnd();
	}

	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();

	//must disable textures to prevent OpenGL mixing up the textures as we go
	glDisable(GL_TEXTURE_2D);
}

void Background::flipX() {
	if (this->flagX == false)
		this->flagX = true;
	else this->flagX = false;
}

void Background::flipY() {
	if (this->flagY == false)
		this->flagY = true;
	else this->flagY = false;
}

//void Background::rotate(int angle) {
//	//translate so center is at (0,0,0)
//	glTranslatef(-this->centerX, -this->centerY, 0);
//
//	//rotate the background a specified angle around the z-axis (2-D rotation)
//	glRotatef(angle, 0.0, 0.0, 1.0);
//
//	//translate back to original position
//	glTranslatef(this->centerX, this->centerY, 0);
//
//}

void Background::setPosition(int x, int y) {
	//set the x and y position of the background
	this->x = x;
	this->y = y;
}

void Background::setSize(unsigned int w, unsigned int h) {
	//set the width and height of background
	this->w = w;
	this->h = h;
}

void Background::execute() {
	this->storedBehavior(this);
}

Background::Background() {
	this->x = 0;
	this->y = 0;
	this->w = 1;
	this->h = 1;

	//this->centerX = (this->knownEngine->getResW() / 2);
	//this->centerY = (this->knownEngine->getResH() / 2);

	this->flagX = false;
	this->flagY = false;

	this->visible = true;

	this->setBehavior(Background::defaultBehavior);
}

Background::~Background() {

}