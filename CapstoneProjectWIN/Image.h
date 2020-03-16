#pragma once
//Image loading library for creating objects that require images

#include <Windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <GL/GL.h>
#include <GL/GLU.h>

class Image {
protected:
	SDL_Surface* storedSource; //The source image, stored into the image object
	GLuint image; //the image that will be drawn
	unsigned int imageWidth, imageHeight; //the width and height of the image

public:
	void loadImage(const char*); //loads an image from a source file
	bool empty();

	Image();
	virtual ~Image();
};