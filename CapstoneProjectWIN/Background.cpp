#include "Background.h"

void Background::defaultBehavior(Entity* e)
{
	static_cast<Background*>(e)->draw();
}

void Background::setFrameCount(unsigned int across, unsigned int down) {
	//this will subdivide the image, be careful when doing this!
	this->framesW = across;
	this->framesH = down;
}

void Background::setFrame(int currentFrame) {
	//set the current frame based on the integer index
	if (currentFrame >= 0) { //prevent this from being less than 0
		this->frame = currentFrame;
	}
}

void Background::draw() {
	//we only want to implement the draw if the background has data
	if (!this->empty()) {
		//these values determine whether or not to use the renderer or custom values
		int drawToX, drawToY, drawToW, drawToH;

		//assign X and Y to the object's data
		drawToX = this->x;
		drawToY = this->y;

		//if we want to use the renderer's data:
		if (this->toRenderer && this->getEngine()) {
			drawToW = this->getEngine()->getResW(); //get the renderer's width
			drawToH = this->getEngine()->getResH(); //get the renderer's height
		}
		else { //if we can't get the renderer's information, simply set W and H to the stored values
			drawToW = this->w;
			drawToH = this->h;
		}

		//we need to get some data
		const int total_subimages = this->framesW * this->framesH; //total subimages made from the image

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
		//calculate the image we want to grab accross using modulos and the width of the subimage
		const int subimageX = (this->frame % this->framesW) * (this->storedSource->w / this->framesW);
		//calculate the image we want to grab down using division and the height of the subimage
		const int subimageY = (this->frame / this->framesW) * (this->storedSource->h / this->framesH);


		glMatrixMode(GL_TEXTURE); //the texture matrix will be the matrix we will perform our operations on
		glLoadIdentity(); //load the identity matrix

		//adjust the matrix to the size of our image
		glScaled(1.0 / this->storedSource->w, 1.0 / this->storedSource->h, 1.0); //the scale will be derived from the image dimensions

		//now use modelview for drawing the image
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//apply if the rotation isn't zero
		if (this->rotation != 0) {
			//translate so center is at (0,0,0)
			glTranslatef(drawToX + this->modposX + (drawToW / 2), drawToY + this->modposY + (drawToH / 2), 0);

			//rotate the background a specified angle around the z-axis (2-D rotation)
			glRotatef(this->rotation, 0.0, 0.0, 1.0);

			//translate back to original position
			glTranslatef(-(drawToX + this->modposX + (drawToW / 2)), -(drawToY + this->modposY + (drawToH / 2)), 0);
		}

		//we need to account for culling if a flip is to occur
		if (this->toggleFlipX || this->toggleFlipY) { //change the culling
			glFrontFace(GL_CCW); //cull counterclockwise if a flip occurs
		}
		if (this->toggleFlipX && this->toggleFlipY) {
			glFrontFace(GL_CW); //cull clockwise if a double flip is present
		}

		//perform a horizontal flip if the xFlip bool is true
		if (this->toggleFlipX) {
			//translate so center is at (0,0,0)
			glTranslatef(drawToX + this->modposX + (drawToW / 2), drawToY + this->modposY + (drawToH / 2), 0);

			//rotate the background a specified angle around the z-axis (2-D rotation)
			glRotatef(180, 0.0, 1.0, 0.0);

			//translate back to original position
			glTranslatef(-(drawToX + this->modposX + (drawToW / 2)), -(drawToY + this->modposY + (drawToH / 2)), 0);
		}

		//perform a vertical flip if the yFlip bool is true
		if (this->toggleFlipY) {
			//translate so center is at (0,0,0)
			glTranslatef(drawToX + this->modposX + (drawToW / 2), drawToY + this->modposY + (drawToH / 2), 0);

			//rotate the background a specified angle around the z-axis (2-D rotation)
			glRotatef(180, 1.0, 0.0, 0.0);

			//translate back to original position
			glTranslatef(-(drawToX + this->modposX + (drawToW / 2)), -(drawToY + this->modposY + (drawToH / 2)), 0);
		}

		//set up the parameters for drawing the image so it uses the pixels
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		//bind this texture to our image
		glBindTexture(GL_TEXTURE_2D, this->image);

		//enable texture drawing
		glEnable(GL_TEXTURE_2D);

		// NOTE: The following is inefficient code for flipping.
		// With 4 different blocks of versions of drawing, it became cumbersome to add in subimage code
		// Used the above rotations to flip the image instead, to keep only one draw block

		//*****************************************************************************************************

		//if (xFlip && !yFlip) {
		//	glBegin(GL_QUADS);
		//	glTexCoord2i(this->storedSource->w, 0);				//top left of texture
		//	glVertex2i(0, 0);	//top left of background

		//	glTexCoord2i(0, 0);				//top right of texture
		//	glVertex2i(this->knownEngine->getResW(), 0);	//top right of background

		//	glTexCoord2i(0, this->storedSource->h);				//bottom right of texture
		//	glVertex2i(this->knownEngine->getResW(), this->knownEngine->getResH());	//bottom right of background

		//	glTexCoord2i(this->storedSource->w, this->storedSource->h);				//bottom left of texture
		//	glVertex2i(0, this->knownEngine->getResH());	//bottom left of background
		//	glEnd();
		//}
		//else if (xFlip && !yFlip) {
		//	glBegin(GL_QUADS);
		//	glTexCoord2i(0, this->storedSource->h);				//top left of texture
		//	glVertex2i(0, 0);	//top left of background

		//	glTexCoord2i(this->storedSource->w, this->storedSource->h);				//top right of texture
		//	glVertex2i(this->knownEngine->getResW(), 0);	//top right of background

		//	glTexCoord2i(this->storedSource->w, 0);				//bottom right of texture
		//	glVertex2i(this->knownEngine->getResW(), this->knownEngine->getResH());	//bottom right of background

		//	glTexCoord2i(0, 0);				//bottom left of texture
		//	glVertex2i(0, this->knownEngine->getResH());	//bottom left of background
		//	glEnd();
		//}
		//else if (xFlip && yFlip) {
		//	glBegin(GL_QUADS);
		//	glTexCoord2i(this->storedSource->w, this->storedSource->h);				//top left of texture
		//	glVertex2i(0, 0);	//top left of background

		//	glTexCoord2i(0, this->storedSource->h);				//top right of texture
		//	glVertex2i(this->knownEngine->getResW(), 0);	//top right of background

		//	glTexCoord2i(0, 0);				//bottom right of texture
		//	glVertex2i(this->knownEngine->getResW(), this->knownEngine->getResH());	//bottom right of background

		//	glTexCoord2i(this->storedSource->w, 0);				//bottom left of texture
		//	glVertex2i(0, this->knownEngine->getResH());	//bottom left of background
		//	glEnd();
		//}
		//else {

		//***************************************************************************************************************




			glBegin(GL_QUADS);
					glTexCoord2i((0), (0));				//top left of subimage
					glVertex2i(drawToX + this->modposX, drawToY + this->modposY);	//top left of background

					glTexCoord2i((2550), (0));				//top right of subimage
					glVertex2i(drawToX + this->modposX + drawToW, drawToY + this->modposY);	//top right of background

					glTexCoord2i((2550), (3309));				//bottom right of subimage
					glVertex2i(drawToX + this->modposX + drawToW, drawToY + this->modposY + drawToH);	//bottom right of background

					glTexCoord2i((0), (3309));				//bottom left of subimage
					glVertex2i(drawToX + this->modposX, drawToY + this->modposY + drawToH);	//bottom left of background
			glEnd();
		//}

		glMatrixMode(GL_TEXTURE);
		glLoadIdentity();

		//must disable textures to prevent OpenGL mixing up the textures as we go
		glDisable(GL_TEXTURE_2D);
	}
}

void Background::flipX() {
	if (this->toggleFlipX == false)
		this->toggleFlipX = true;
	else this->toggleFlipX = false;
}

void Background::flipY() {
	if (this->toggleFlipY == false)
		this->toggleFlipY = true;
	else this->toggleFlipY = false;
}

void Background::setRotation(int angle) {
	this->rotation = angle;
}

void Background::setToRenderSize() {
	this->toRenderer= true;
}

void Background::detachFromRenderer() {
	this->toRenderer = false;
}

void Background::setPosition(int x, int y) {
	//set the x and y position of the background
	this->x = x;
	this->y = y;
}

void Background::setSize(unsigned int w, unsigned int h) {
	//set the width and height of background (can't be less than 0)
	if (w > 0) {
		this->w = w;
	}
	if (h > 0) {
		this->h = h;
	}
}

void Background::execute() {
	this->storedBehavior(this);
}

Background::Background() {
	//initialize position to 0
	this->x = 0;
	this->y = 0;

	//by default, width and height are set to some default value
	this->w = 640;
	this->h = 480;

	//set the frame to 0, we have no information regarding that yet
	this->frame = 0;

	//DOESN"T WORK
	//obtain the center of the background
	this->centerX = (this->w / 2);
	this->centerY = (this->h / 2);

	//by default, no flip should occur
	this->toggleFlipX = false;
	this->toggleFlipY = false;

	//by default, the number of subimages accross and down would be 1
	this->framesW = 1;
	this->framesH = 1;

	//by default, the background is visible
	this->visible = true;

	//set the default behavior of the background
	this->setBehavior(Background::defaultBehavior);
}

Background::~Background() {

}