#pragma once

#include "Entity.h"
#include "Image.h"

class Background : public Entity , public Image {
private:
	int x, y; //the x and y positions of the background (should be the same as renderer)
	unsigned int w, h; //the width and height of the background
	int centerX, centerY;
	bool visible; //to toggle visibility of background
	bool flagX, flagY;

	//int subX, subY;
	//unsigned int subW, subH;


	static void defaultBehavior(Entity* e); //the default behavior of the background

public:
	void draw(); //draw the background
	void flipX();
	void flipY();
	//void rotate(int);

	void setPosition(int, int); //set position of the background
	int getX() { return this->x; }; //return the x position of the background
	int getY() { return this->y; }; //return the y position of the background

	void setSize(unsigned int, unsigned int);  //set the size of the background
	unsigned int getW() { return this->w; }; //return the width of the background
	unsigned int hetH() { return this->h; }; //retuen the height of the background
	void hide() { this->visible = false; } //hides the background
	void show() { this->visible = true; } //shows the background


	void execute(); //execute the background's stored behavior

	Background();
	virtual ~Background();
};