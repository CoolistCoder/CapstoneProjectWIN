#include "Image.h"

void Image::loadImage(const char* imageName) {
	//This function simply loads an image
	//before we begin, we want to see if the image is empty
	if (!this->empty()) {
		//if it isn't, we can delete the information stored within
		//first, delete the image we will draw
		glDeleteTextures(1, &this->image);
		//then, delete the source image stored in the memory
		SDL_FreeSurface(this->storedSource);
		//now set both to nullptr
		this->image = 0;
		this->storedSource = nullptr;
	}
	//once this check has been performed, we move onto the load function
	this->storedSource = IMG_Load(imageName);
	//this will load the image into the storedSource variable
	//we want to store some information in a few variables as well
	this->imageWidth = this->storedSource->w; //width and height will be stored
	this->imageHeight = this->storedSource->h;

	//now we want to test to see if the surface was loaded properly
	if (this->storedSource) { //to do this, just check and see if it's not nullptr
		int colormode; //this is how we determine whether an image is alpha or not
		//now test for this
		if (this->storedSource->format->BytesPerPixel == 4) {
			//if this image has an alpha layer, we set the colormode to rgba
			colormode = GL_RGBA;
		}
		else {
			//set the colormode to RGB if there is no alpha layer
			colormode = GL_RGB;
		}
		//now that the image knows how to draw transparent and nontransparent images,
		//we need to generate the proper texture
		glGenTextures(1, &this->image); //we want to create a single texture and load it to this->image
		glBindTexture(GL_TEXTURE_2D, this->image); //now we want to tell OpenGL we want to use this image as a texture

		//this determines texture smoothing, but we just want to create a simple pixellated image
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		//now we need to load the texture into openGL in order to turn it into a proper texture
		glTexImage2D
		(
			GL_TEXTURE_2D, //the image we are loading will be implemented in a 2D texture
			0,				//the image's detail level will be the same as the source
			colormode,		//this will determine if it is handled as an alpha image or not
			this->imageWidth, //the width of the source
			this->imageHeight, //the height of the source
			0,					//THIS MUST BE ZERO
			colormode,			//the colormode will not change
			GL_UNSIGNED_BYTE,	//this is what the data will be read as
			this->storedSource->pixels //read the data
		);
		this->imagename = imageName;
	}
	else {
		//if the source image wasn't found, just toss everything
		this->image = 0;
	}
}

bool Image::empty() {
	//Check to see if the source failed to load
	//if the source fails, just return true
	if (!this->storedSource) {
		return true;
	}
	//check to see if the image drawn isn't there
	//if the drawn image returns 0, return true
	if (!this->image) {
		return true;
	}

	//return false if the other returns don't trigger
	return false;
}

void Image::shareImage(Image* img) {
	this->storedSource = img->storedSource; //copy the source pointer
	this->image = img->image; //copy the data
}

Image::Image() {
	this->storedSource = nullptr; //this is a pointer, init to nullptr
	this->image = 0; //because this is an integer at heart, we can initialize it to 0
	this->imageWidth = 0;
	this->imageHeight = 0;
}

Image::~Image() {
	//automatically clean up the image
	if (!this->empty()) {
		//if the image isn't empty, delete everything
		if (this->image) { //if there is data in the image variable
			//first, delete the image we wanted to draw
			glDeleteTextures(1, &this->imageHeight);
			//now set both to nullptr
			this->image = 0;
		}
		if (this->storedSource) { //if there is data in the source image variable
			//then, delete the source image stored in the memory
			SDL_FreeSurface(this->storedSource);
			this->storedSource = nullptr;
		}



	}
}