#include "Line.h"

static void Line::defaultBehavior(Entity* e) {
	//simply draw
	static_cast<Line*>(e)->draw();
}

void Line::setLinePosition(int startX, int startY, int endX, int endY) {
	//simply set the start and end position of the line in a single function
	this->startX = startX;
	this->startY = startY;
	this->endX = endX;
	this->endY = endY;
}

void Line::draw() {
	//This function's drawing algorithm is based on the Bresenham Line Algorithm
	//We need to save the veariables stored for the start and end points of the line
	int savedStartX = this->startX, savedStartY = this->startY;
	int savedEndX = this->endX, savedEndY = this->endY;

	//We need variables to draw between the start and end points
	int drawPositionX, drawCorrectX;
	int drawPositionY, drawCorrectY;
	//we also need variables to check to see if an error has been made
	int errorCheck, errorCorrection;

	//we need to set our variables appropriately
	//We need drawCorrectX/Y to check to see if the line needs to be corrected back
	drawCorrectX = abs(this->endX - this->startX);
	drawCorrectY = abs(this->endY - this->startY);

	//We need drawPositionX/Y to adjust how the line is drawn when the start is drawn further than the end
	if (this->startX < this->endX) {
		drawPositionX = 1; //do not alter the adjustment if the end comes after the start
	}
	else {
		drawPositionX = -1; //if the end of the line comes before the start, adjust it to be negative
	}
	//do the same for Y
	if (this->startY < this->endY) {
		drawPositionY = 1; //do not alter the adjustment if the end comes after the start
	}
	else {
		drawPositionY = -1; //if the end of the line comes before the start, adjust it to be negative
	}

	//we need errorcheck to correct the drawing properly based on where the line positions are
	if (drawCorrectX > drawCorrectY) { //if the line is wider than it is tall
		errorCheck = drawCorrectX / 2; //adjust the line based on the x value
	}
	else { //if the line is taller than it is wide
		errorCheck = -drawCorrectY / 2; //adjust the line based on the y value
	}

	//this is where the line must be drawn
	while (true) { //because of this formula, we break when the condition is met within the loop
		//perform a typical draw here, but use quads to simulate pixels
		//TODO: REMOVE AND REPLACE WITH VERTEX MODE
		glMatrixMode(GL_MODELVIEW); //change the matrix to the modelview matrix to modify objects drawn to the screen
		glLoadIdentity();	//change the active identity to the modelview matrix
		glBegin(GL_QUADS);	//draw quads
		glVertex2i(savedStartX, savedStartY);	//top left
		glVertex2i(savedStartX+1, savedStartY);	//bottom left
		glVertex2i(savedStartX+1, savedStartY+1);	//bottom right
		glVertex2i(savedStartX, savedStartY+1);	//top right
		glEnd();

		//if the position of the startX and StartY are equal to the end, a break will occur
		if (savedStartX == savedEndX && savedStartY == savedEndY) {
			break;
		}
		//save the errorcheck into the errorcorrect variable
		errorCorrection = errorCheck;

		//we need to adjust how the line is drawn
		if (errorCorrection > -drawCorrectX) { //if the line is going to draw outside of the calculation
			errorCheck -= drawCorrectY; //push it up
			savedStartX += drawPositionX; //increment the line by 1 or -1 depending on which direction the line is pointing
		}
		if (errorCorrection > -drawCorrectY) { //same with Y
			errorCheck -= drawCorrectY; //push it right
			savedStartX += drawPositionX; //increment the line by 1 or -1 depending on which direction the line is pointing
		}
	}
}

void Line::execute() {
	this->storedBehavior(this);
}

Line::Line() {
	//TODO Auto-Generated Constructor Stub
	//set all to 0 except the end variables
	this->startX = 0;
	this->startY = 0;
	this->endX = 1;
	this->endY = 1;

	//feed the setBehavior function the line's default behavior
	this->setBehavior(Line::defaultBehavior);
}

Line::~Line() {
	//TODO Auto-Geberated Destructor Stub
}