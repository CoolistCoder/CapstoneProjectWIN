#include "Tile.h"

void Tile::defaultBehavior(Entity* e) {
	static_cast<Tile*>(e)->draw();
}

void Tile::setPosition(int x, int y) {
	this->x = x;
	this->y = y;
}

void Tile::setSize(int w, int h) {
	if (w > 0) {
		this->w = w;
	}
	if (h > 0) {
		this->h = h;
	}
}

void Tile::setFrameCount(unsigned int across, unsigned int down) {
	//subdivide the image into subimages. Be careful when using this!
	this->framesW = across;
	this->framesH = down;
}

void Tile::setFrame(int currentFrame) {
	//set the current frame we are working with based on integer index
	if (currentFrame >= 0) {//make sure it's a valid frame
		this->frame = currentFrame;
	}
}

void Tile::toggleVerticalFlip() {
	if (VFlip == false)
		this->VFlip = true;
	else this->VFlip = false;
}

void Tile::toggleHorizontalFlip() {
	if (HFlip == false)
		this->HFlip = true;
	else this->HFlip = false;
}

//bool Tile::collideAgainst(Sprite* spr) {
//	//like the collideAgainst code with the individual points, but for a sprite
//	if (spr) {
//		//we need to compare the values given with the sprite
//		if ((this->y + this->h) < spr->y)
//			//return false if the sprite is too far up
//			return false;
//		if (this->y > (spr->y + spr->h))
//			//return false if the sprite is too far down
//			return false;
//		if ((this->x + this->w) < spr->x)
//			//return false if the sprite is too far left
//			return false;
//		if (this->x > (spr->x + spr->w))
//			//return false if the sprite is too far right
//			return false;
//		//return true if the values overlap
//		return true;
//	}
//	return false;
//}

bool Tile::collideAgainst(int x, int y) {
	//simply check to see if these values are within the box
	if ((x >= this->x && x <= this->x + this->w) && (y >= this->y && y <= this->y + this->h)) {
		//The X of the point must be greater than or equal to the X of the tile
		//The X of the point must also be less than or equal to the relative width of the tile
		//the Y of the point must be greater than or equal to the Y of the tile
		//The Y of the point must also be less than or equal to the relative height of the tile
		return true; //if these conditions are met, return true
	}
	return false; //otherwise, return false
}

bool Tile::collideAgainst(int x, int y, int w, int h) {
	//compare the values of the box's width and height to that of the tile
	if ((this->y + this->h) < y)
		return false;	//tile is too far up
	if ((this->x + this->w) < x)
		return false;	//tile is too far left
	if (this->y > (y + h))
		return false;	//tile is too far down
	if (this->x > (x + w))
		return false;	//tile is too far right

	//return true if values overlap
	return true;
}

bool Tile::rendererCollision() {

	/*
	if (this->getEngine()) {//if we have an engine

	}
	//return true if the tile is within the rendering space
	return true;
	*/
	//first, check and see if an engine is present
	std::cout << this->modposY << ", " << this->viewary + this->viewarh << std::endl;

	if (this->getEngine()) {
		//derender if the tile surpasses h
		if ((this->modposY + (this->y * this->h)) > this->viewary + this->viewarh) {
			std::cout << "1 overlap" << std::endl;
			return false;	//tile is too far up
		}
		//derender if the tile surpasses w	
		if ((this->modposX + (this->x * this->w)) > this->viewarx + this->viewarw) {
			std::cout << "2 overlap" << std::endl;
			return false;	//tile is too far left
		}
		
		//TODO make this work now
		/*
		if ((this->y - this->modposY) < this->viewary + this->viewarh) {
			std::cout << "3 overlap" << std::endl;
			return false;	//tile is too far down
		}
			
		if ((this->x - this->modposX) < this->viewarx + this->viewarw) {
			std::cout << "4 overlap" << std::endl;
			return false;	//tile is too far right
		}
		*/
			
		return true;

	}
	return false; //do not draw if no engine is present!!!!
}

void Tile::draw() {
	//we only want to implement the draw if the tile has data
	if (!this->empty() && this->rendererCollision()) {

		//we need to get some data
		const int total_subimages = this->framesW * this->framesH; //the total subimages made from the image

		//we need to be able to calculate what subimages to grab based on the image index
		//make sure the frame value isn't higher than the number of total images we have
		while (this->frame >= total_subimages) {
			//subtract 1 from frame until we have a valid index
			this->frame--;
		}

		//the subimage's width and height is based on the image's total size / number of images in corresponding direction
		const int subimageW = this->storedSource->w / this->framesW;
		const int subimageH = this->storedSource->h / this->framesH;


		//now we need to select the correct image based on this index
		//calculate the image we want to grab across using modulo and the width of the subimage
		const int subimageX = (this->frame % this->framesW) * (this->storedSource->w / this->framesW);
		//calculate the image we want to grab down using division and the height of the subimage
		const int subimageY = (this->frame / this->framesW) * (this->storedSource->h / this->framesH);

		//make sure we set the mode to gl_texture
		glMatrixMode(GL_TEXTURE);
		glLoadIdentity();

		//we want to make sure that when we load in a texture, we use its pixel coordinates
		//doing this adjusts its scale to the image's size
		glScaled(1.0 / this->storedSource->w, 1.0 / this->storedSource->h, 1.0);

		//now set up modelview
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//we need to account for culling if a flip is to occur
		if (this->HFlip || this->VFlip) { //change the culling
			glFrontFace(GL_CCW); //cull counterclockwise if a flip occurs
		}
		if (this->HFlip && this->VFlip) {
			glFrontFace(GL_CW); //cull clockwise if a double flip is present
		}

		//perform a horizontal flip if the horizontal flip bool is true
		if (this->HFlip) {
			glTranslatef(this->x + this->modposX + (this->w / 2), this->y + this->modposY + (this->h / 2), 0); 	//translate to the center of the object
			glRotatef(180, 0, 1, 0); //rortate the object on its Y axis
			glTranslatef(-(this->x + this->modposX + this->w / 2), -(this->y + this->modposY + this->h / 2), 0);	//translate the object back to its point
		}

		//perform a vertical flip if the vertical flip bool is true
		if (this->VFlip) {
			glTranslatef(this->x + this->modposX + (this->w / 2), this->y + this->modposY + (this->h / 2), 0); 	//translate to the center of the object
			glRotatef(180, 1, 0, 0); //rortate the object on its X axis
			glTranslatef(-(this->x + this->modposX + this->w / 2), -(this->y + this->modposY + this->h / 2), 0);	//translate the object back to its point
		}

		//set up the texture parameters so the image will draw using the precise pixels
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		//bind the parameters to the image
		glBindTexture(GL_TEXTURE_2D, this->image);

		//enable texture drawing
		glEnable(GL_TEXTURE_2D);

		//TODO IMPLEMENT THE SUBIMAGE DRAWING
		//begin drawing
		glBegin(GL_QUADS);
		glTexCoord2i((subimageX), (subimageY)); //top left of the subimage
		glVertex2i((this->x * this->w) + this->modposX, (this->y * this->h) + this->modposY); //top left of tile

		glTexCoord2i((subimageX + subimageW), (subimageY)); //top right of the subimage
		glVertex2i((this->x * this->w) + this->w + this->modposX, (this->y * this->h) + this->modposY); //top right of tile

		glTexCoord2i((subimageX + subimageW), (subimageY + subimageH)); //bottom right of the subimage
		glVertex2i((this->x * this->w) + this->w + this->modposX, (this->y * this->h) + this->h + this->modposY); //bottom right of tile

		glTexCoord2i((subimageX), (subimageY + subimageH));  //bottom left of the subimage
		glVertex2i((this->x * this->w) + this->modposX, (this->y * this->h) + this->h + this->modposY); //bottom left of tile

		glEnd();

		glMatrixMode(GL_TEXTURE);
		glLoadIdentity();

		//we want to return everything to the status quo
		if (this->HFlip || this->VFlip) { //change the culling
			glFrontFace(GL_CW); //cull clockwise if a flip occurred
		}

		//must disable textures before we do anything else to prevent opengl from getting confused with our textures
		glDisable(GL_TEXTURE_2D);

	}
}

void Tile::execute() {
	this->storedBehavior(this);
}

Tile::Tile() {

	//initialize everything to 0 and 1, we don't have any data starting out
	this->x = 0;
	this->y = 0;
	this->w = 1;
	this->h = 1;

	//set the frame to 0, as we have no information regarding that yet
	this->frame = 0;

	//by default, the number of subimages across and down would be 1
	this->framesW = 1;
	this->framesH = 1;

	//by default, no flip will occur
	this->HFlip = false;
	this->VFlip = false;

	this->setBehavior(Tile::defaultBehavior);
}

Tile::~Tile() {

}