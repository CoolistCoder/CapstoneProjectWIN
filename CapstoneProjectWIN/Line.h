#pragma once
#include "Entity.h"
#include <math.h> //the math library is necessary for this object

class Line : public Entity {
private:
	int startX, startY; //the starting point of the line
	int endX, endY; //the ending point of the line

	Uint8 r, g, b, a; //the rgba values of the line

	static void defaultBehavior(Entity*); //the default behavior of the line

public:

	//getters and setters for the line
	int getStartX() { return this->startX; }; //get the x starting point for the line
	int getStartY() { return this->startY; }; //get the y starting point for the line
	int getEndX() { return this->endX; }; //get the x ending point for the line
	int getEndY() { return this->endY; }; //get the y ending point for the line
	void setStartX(int newPosition) { this->startX = newPosition; }; //set the start positon of x
	void setStartY(int newPosition) { this->startY = newPosition; }; //set the start positon of y
	void setEndX(int newPosition) { this->endX = newPosition; }; //set the end positon of x
	void setEndY(int newPosition) { this->endY = newPosition; }; //set the end positon of y
	void setLinePosition(int, int, int, int); //set the line's start and end position

	void modifyColor(Uint8, Uint8, Uint8); //sets the color of the line
	void modifyAlpha(Uint8); //sets the transparency of the line

	void draw(); //draw the line

	void execute(); //the code to execute the object's stored function

	Line();
	virtual ~Line();
};