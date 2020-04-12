#pragma once
#include "Sprite.h" //include the sprite so we can use it for collisions

//The tile is a sprite that does not move freely, nor rotates
//it is confined to a gridlike pattern based on its size

class Tile : public Entity, public Image
{
protected:
	int x, y; //the position data of the tile
	int w, h; //the width and height of the tile
	unsigned int framesW, framesH; //the number of horizontal and vertical frames

	bool HFlip, VFlip; //booleans to determine the horizontal and vertical flipping

	int frame; //the frame the tile is drawn at

	static void defaultBehavior(Entity*); //the default behavior of the tile
public:
    //todo modify the draw function to draw the tile based on its position * its width (or height)
    //todo modify the draw function to remove its rotation
    //todo modify the draw to ONLY draw if the tile is within the rendering area

	void setPosition(int, int); //set the position of the tile
	void setSize(int, int); //set the size of the tile
	void setFrameCount(unsigned int, unsigned int); //set the number of horizontal and vertical frames
	void setFrame(int); //set the current frame

	//flip functions
	void activateVerticalFlip() { this->VFlip = true; }; //force the vertical flip true
	void activateHorizontalFlip() { this->HFlip = true; }; //force the horizontal flip true
	void deactivateVerticalFlip() { this->VFlip = false; }; //force the vertical flip false
	void deactivateHorizontalFlip() { this->HFlip = false; }; //force the horizontal flip false
	void toggleVerticalFlip(); //toggle between true/false vertical flips
	void toggleHorizontalFlip(); //toggle between true/false horizontal flips

	//collision functions
	//bool collideAgainst(Sprite*); //check if a collision occured with a sprite
	bool collideAgainst(int, int); //check to see if a point is colliding with this tile
	bool collideAgainst(int, int, int, int); //check to see if a box-like entity is colliding with this tile
	bool rendererCollision(); //check to see if tile is within renderer

	void draw(); //the draw function for the tile

	void execute(); //execute the tile's stored behavior

	Tile();
	virtual ~Tile();
};

