#include "Sprite.h"

void Sprite::setPosition(int x, int y) {
	//set the position of the sprite with the x and y
	this->x = x;
	this->y = y;
}

void Sprite::setSize(int w, int h) {
	//limit the width and height so they can't be less than 0
	if (w > 0) {
		this->w = w;
	}
	if (h > 0) {
		this->h = h;
	}
}

void Sprite::defaultBehavior(Entity* d) {
	//by default, simply draw the sprite
	static_cast<Sprite*>(d)->draw();
}

void Sprite::setFrameCount(unsigned int across, unsigned int down) {
	//this will subdivide the image, be careful when using this!
	this->framesW = across;
	this->framesH = down;
}

void Sprite::setFrame(int currentFrame) {
	//set the current frame based on the integer index
	if (currentFrame >= 0) { //prevent this from being less than 0
		this->frame = currentFrame;
	}
}

void Sprite::setRotation(int theta) {
	this->rotation = theta;
}

bool Sprite::collideAgainst(Sprite* spr) {
	//like the collideAgainst code with the individual points, but for another sprite
	if (spr) {
		//we need to compare the values given with the sprite
		if ((this->y + this->h) < spr->y)
			//return false if the sprite is too far up
			return false;
		if (this->y > (spr->y + spr->h))
			//return false if the sprite is too far down
			return false;
		if ((this->x + this->w) < spr->x)
			//return false if the sprite is too far left
			return false;
		if (this->x > (spr->x + spr->w))
			//return false if the sprite is too far right
			return false;
		//return true if the values overlap
		return true;
	}
	return false;
}

bool Sprite::collideAgainst(int x, int y) {
	//simply check to see if these values are within the box
	if ((x >= this->x && x <= this->x + this->w) && (y >= this->y && y <= this->y + this->h)) {
		//The X of the point must be greater than or equal to the X of the sprite
		//The X of the point must also be less than or equal to the relative width of the sprite
		//the Y of the point must be greater than or equal to the Y of the sprite
		//The Y of the point must also be less than or equal to the relative height of the sprite
		return true; //if these conditions are met, return true
	}
	return false; //otherwise, return false
}

bool Sprite::collideAgainst(int x, int y, int w, int h) {
	//we need to compare the values given with the sprite
	if ((this->y + this->h) < y)
		//return false if the sprite is too far up
		return false;
	if (this->y > (y + h))
		//return false if the sprite is too far down
		return false;
	if ((this->x + this->w) < x)
		//return false if the sprite is too far left
		return false;
	if (this->x > (x + w))
		//return false if the sprite is too far right
		return false;
	//return true if the values overlap
	return true;
}

void Sprite::draw() {
	//we only want to implement the draw if the sprite has data
	if (!this->empty()) {

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

		//apply rotation if rotation isn't 0
		if (this->rotation != 0) {
			glTranslatef(this->x + this->modposX + (this->w / 2), this->y + this->modposY + (this->h / 2), 0); 	//translate to the center of the object
			glRotatef(this->rotation, 0, 0, 1); //rortate the object on its Z axis
			glTranslatef(-(this->x + this->modposX + this->w / 2), -(this->y + this->modposY + this->h / 2), 0);	//translate the object back to its point
		}

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
			glColor4ub(this->r, this->g, this->b, this->a); //set the colors of the entity beforehand

			glTexCoord2i((subimageX), (subimageY)); //top left of the subimage
			glVertex2i(this->x + this->modposX, this->y + this->modposY); //top left of sprite

			glTexCoord2i((subimageX + subimageW), (subimageY)); //top right of the subimage
			glVertex2i(this->x + this->w + this->modposX, this->y + this->modposY); //top right of sprite

			glTexCoord2i((subimageX + subimageW), (subimageY + subimageH)); //bottom right of the subimage
			glVertex2i(this->x + this->w + this->modposX, this->y + this->h + this->modposY); //bottom right of sprite

			glTexCoord2i((subimageX), (subimageY + subimageH));  //bottom left of the subimage
			glVertex2i(this->x + this->modposX, this->y + this->h + this->modposY); //bottom left of sprite

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

void Sprite::execute() {
	//execute the stored behavior
	this->storedBehavior(this);
}

Sprite::Sprite() {
	// TODO Auto-generated constructor stub
	//initialize everything to 0 and 1, we don't have any data starting out
	this->x = 0;
	this->y = 0;
	this->w = 1;
	this->h = 1;

	//set the frame to 0, as we have no information regarding that yet
	this->frame = 0;

	//set the rotation of the sprite to 0, we have no data for this yet
	this->rotation = 0;

	//by default, the number of subimages across and down would be 1
	this->framesW = 1;
	this->framesH = 1;

	//by default, no flip will occur
	this->HFlip = false;
	this->VFlip = false;

	//set the default behavior of the sprite
	this->setBehavior(Sprite::defaultBehavior);
}

Sprite::~Sprite() {
	// TODO Auto-generated destructor stub
}