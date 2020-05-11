#pragma once
#include <Windows.h>
#include <SDL.h>
#include <SDL_image.h> //image library
#include <GL/gl.h> //the library that stores the image
#include <iostream>

class Image {
protected:
	SDL_Surface* storedSource; //The source image, stored into the image object
	GLuint image; //the image that will be drawn
	unsigned int imageWidth, imageHeight; //the width and height of the image
	std::string imagename; //this is where the image's name is stored for assignment
	Uint8 r, g, b; //mod colors
	Uint8 a; //alpha mod color

public:
	void loadImage(const char*); //loads an image from a source file
	bool empty(); //retrieve if the image is empty or not
	void shareImage(Image*); //takes an image and copies its info with this image
	void nullify(); //nullifies an image to prevent issues regarding deletion
	void modifyColor(Uint8, Uint8, Uint8); //modify the image's color
	void modifyAlpha(Uint8); //modify the image's transparency

	Image();
	virtual ~Image();
};