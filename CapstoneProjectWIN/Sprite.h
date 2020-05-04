#pragma once
#include "Entity.h"

//sprites will inherit from entities, and the new image class
class Sprite : public Entity, public Image {
private:
	int x, y; //the position data of the sprite
	int w, h; //the width and height of the sprite
	unsigned int framesW, framesH; //the number of horizontal and vertical frames

	bool HFlip, VFlip; //booleans to determine the horizontal and vertical flipping

	int frame; //the frame the sprite is drawn at

	int rotation; //the rotation of the sprite

	static void defaultBehavior(Entity*); //the default behavior of the sprite

public:

	void setPosition(int, int); //set the position of the sprite
	void setSize(int, int); //set the size of the sprite
	void setFrameCount(unsigned int, unsigned int); //set the number of horizontal and vertical frames
	void setFrame(int); //set the current frame

	//Getters
	int getPosX() { return this->x; };
	int getPosY() { return this->y; };
	int getPosW() { return this->w; };
	int getPosH() { return this->h; };

	//flip functions
	void activateVerticalFlip() { this->VFlip = true; }; //force the vertical flip true
	void activateHorizontalFlip() { this->HFlip = true; }; //force the horizontal flip true
	void deactivateVerticalFlip() { this->VFlip = false; }; //force the vertical flip false
	void deactivateHorizontalFlip() { this->HFlip = false; }; //force the horizontal flip false
	void toggleVerticalFlip(); //toggle between true/false vertical flips
	void toggleHorizontalFlip(); //toggle between true/false horizontal flips

	void setRotation(int); //set the rotation angle of the sprite

	//collision functions
	bool collideAgainst(Sprite*); //check if a collision occured with another sprite
	bool collideAgainst(int, int); //check to see if a point is colliding with this sprite
	bool collideAgainst(int, int, int, int); //check to see if a box-like entity is colliding with this sprite

	void draw(); //the draw function for the sprite

	void execute(); //execute the sprite's stored behavior

	Sprite();
	virtual ~Sprite();
};
