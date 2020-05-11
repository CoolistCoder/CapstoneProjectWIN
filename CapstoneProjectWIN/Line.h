#pragma once
#include "Entity.h"
#include <math.h> //the math library is necessary in this object

class Line : public Entity {
protected:
	int startX, startY; //the starting point of the line
	int endX, endY; //the ending point of the line

	Uint8 r, g, b, a;

	static void defaultBehavior(Entity*); //the default behavior of the line

public:


	//getters and setters for the line
	int getStartX() { return this->startX; }; //get the x starting position
	int getStartY() { return this->startY; }; //get the y starting position
	int getEndX() { return this->endX; }; //get the x end position
	int getEndY() { return this->endY; }; //get the y end position
	void setStartX(int newPosition) { this->startX = newPosition; }; //set the start position of X
	void setStartY(int newPosition) { this->startY = newPosition; }; //set the start position of Y
	void setEndX(int newPosition) { this->endX = newPosition; }; //set the end position of X
	void setEndY(int newPosition) { this->endY = newPosition; }; //set the end position of Y
	void setLinePosition(int, int, int, int); //set the line's start and end
	void modifyColor(Uint8, Uint8, Uint8);
	void modifyAlpha(Uint8);

	void draw(); //draw the line

	void execute(); //the code to execute the object's stored function

	Line();
	virtual ~Line();
};