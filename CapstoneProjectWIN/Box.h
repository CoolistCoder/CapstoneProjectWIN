#pragma once
#include "Entity.h"

class Box : public Entity {
private:
	int x, y; //the x and y positions of the box
	unsigned w, h; //the width and height of the box
	bool visible;
	bool independent;

	Uint8 r, g, b, a; //the rgba values of the box

	static void defaultBehavior(Entity* e); //the default behavior of the box

public:
	void draw(); //draw the box
	void setPosition(int, int); //set position of the box
	int getX() { return this->x; }; //return the x position of the box
	int getY() { return this->y; }; //return the y position of the box

	void setSize(unsigned int, unsigned int);  //set the size of the box
	unsigned int getW() { return this->w; }; //return the width of the box
	unsigned int getH() { return this->h; }; //retuen the height of the box
	void hide() { this->visible = false; } //hides the box
	void show() { this->visible = true; } //shows the box

	void modifyColor(Uint8, Uint8, Uint8); //sets the color of the box
	void modifyAlpha(Uint8); //sets the transparency of the box

	void independentFromCamera() { this->independent = true; };
	void dependentOnCamera() { this->independent = false; };

	void execute(); //execute the box's stored behavior

	Box();
	virtual ~Box();
};