#pragma once

#include "Entity.h"
#include "Image.h"

class Background : public Entity , public Image {
protected:
	int x, y; //the x and y positions of the background (should be the same as renderer)
	unsigned int w, h; //the width and height of the background
	int centerX, centerY; //center of the renderer
	unsigned int framesW, framesH; //the number of horizontal and vertical frames

	int textureX, textureY, textureW, textureH; //these are the subimage variables!

	int rotation; //the angle by which the background is rotated

	bool visible; //to toggle visibility of background
	bool toggleFlipX, toggleFlipY; //flags indicate whether or not to perform a flip
	bool toRenderer;
	bool directTexture; //boolean determining if the texture should stretch directly to the edges of the object
	bool independentFromCamera; //determines if the background scrolls with the camera

	int frame; //the frame the background is drawn at


	static void defaultBehavior(Entity* e); //the default behavior of the background

public:
	void draw(); //draw the background

	void flipX(); //flip the background over the horizontal axis
	void flipY(); //flip the background over the vertical axis
	void setRotation(int);  //rotate the image by a specified angle

	void setToRenderSize();
	void detachFromRenderer(); //detaches the object from the renderer

	void useImage() { this->directTexture = true; }; //this lets us use our image values
	void useSubimage() { this->directTexture = false; }; //this lets us use our subimage values

	void setPosition(int, int); //set position of the background
	int getX() { return this->x; }; //return the x position of the background
	int getY() { return this->y; }; //return the y position of the background

	void setSubimage(int,int,int,int);

	//camera functions
	void hasCamera() { this->independentFromCamera = false; }; //attaches the object to the active camera
	void noCamera() { this->independentFromCamera = true; }; //detaches the object from the active camera

	//other stuff
	void setSize(unsigned int, unsigned int);  //set the size of the background
	unsigned int getW() { return this->w; }; //return the width of the background
	unsigned int hetH() { return this->h; }; //retuen the height of the background

	void hide() { this->visible = false; } //hides the background
	void show() { this->visible = true; } //shows the background


	void execute(); //execute the background's stored behavior

	Background();
	virtual ~Background();
};