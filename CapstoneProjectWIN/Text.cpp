
#include "Text.h"

void Text::defaultBehavior(Entity* e) {
	static_cast<Text*>(e)->drawText(); //just draw the text
}

void Text::setString(std::string _str) {
	//empty the string
	this->clearString();

	//check to see if the string is valid
	if (!_str.empty()) {
		//now just set the string
		this->string_to_draw = _str;
		//create all of our tiles that we need
		Tile* newtile; //generate our tile pointer to add our data to the tilemap
		//create a for loop to determine what attribs to give our tile
		for (unsigned int i = 0; i < this->string_to_draw.size(); i++) {
			newtile = new Tile; //create our new tile
			newtile->setFrameCount(16, 6);
			newtile->setFrame(this->string_to_draw[i] - 32); //set the frame of the sprite based on the value at arr[i]
			newtile->setSize(this->w, this->h);
			newtile->setEngine(this->getEngine()); //give our tiles the necessary engine
			newtile->shareImage(this);
			this->tiles.push_back(newtile); //add the tile to the tilemap
		}
	}
}

void Text::clearString() {
	//simply clear the string
	this->string_to_draw.clear();
	//then clear all the tiles in the vector
	for (unsigned int i = 0; i < this->tiles.size(); i++) {
		this->tiles[i]->nullify(); //nullify the images first
		delete this->tiles[i]; //empty the tiles from the vector
	}
	this->tiles.clear(); //clear out all empty tiles
}

std::string Text::getString() {
	return this->string_to_draw; //retrieve the stored string
}

void Text::drawText() {
	if (this->getEngine()) { //Check to see if we have a valid engine FIRST
		//go through each tile stored in our vector and draw it
		for (unsigned int i = 0; i < this->tiles.size(); i++) {
			this->tiles[i]->setPosition
			(
				i + this->x, //set the x position of the text
				this->y //set the y position of the text
			);
			if (this->assignedcamera) //we need to be absolutely certain that the tiles are being assigned properly
				this->tiles.at(i)->assigned();
			this->tiles[i]->modifyOffset(this->modposX, this->modposY);
			this->tiles[i]->modifyRenderArea(this->renderAreaW, this->renderAreaH);
			this->tiles[i]->setViewData(this->viewarx, this->viewary, this->viewarw, this->viewarh);

			//determine whether or not to use global colors
			if (!this->individualColors) {
				this->tiles[i]->modifyColor(this->r, this->g, this->b); //set each tile's color to the sprite sheet's
				this->tiles[i]->modifyAlpha(this->a); //set each tile's alpha to the sprite sheet's
			}

			//then draw
			this->tiles[i]->draw();
		}
	}
}

void Text::setSize(int w, int h) {
	//make sure w and h are greater than 0
	if (w > 0 && h > 0) {
		//simply apply that to the w and height of this object
		this->w = w;
		this->h = h;
		//then, check to see if we can apply this to the tiles if they exist
		for (unsigned int i = 0; i < this->tiles.size(); i++) {
			this->tiles[i]->setSize(this->w, this->h);
		}
	}
}

void Text::setPosition(int x, int y) {
	//just set the x and y variables
	this->x = x;
	this->y = y;
}

Tile* Text::getTile(unsigned int _at) {
	//simply get a tile at the _at index so long as the tile is within the index
	if (_at < this->tiles.size()) {
		return this->tiles[_at];
	}
	return nullptr; //if a tile is not found return null
}

void Text::execute() {
	this->storedBehavior(this); //execute the stored behavior
}

Text::Text() {
	// TODO Auto-generated constructor stub
	this->loadImage("t.png"); //load in the default text
	//make sure we have the default font
	if (!this->empty()) { //if we do have the font, use the data from the font
		this->x = 0;
		this->y = 0;
		this->w = this->storedSource->w / 16; //these are the values assigned to each character
		this->h = this->storedSource->h / 6;
		this->hasfont = true;
	}
	else { //if we don't have the font, give it some default values
		this->x = 0;
		this->y = 0;
		this->w = 1;
		this->h = 1;
		this->hasfont = false;
	}

	this->setBehavior(Text::defaultBehavior);

	this->individualColors = false; //by default, let's use a global color

}

Text::~Text() {
	// TODO Auto-generated destructor stub
	this->clearString();
}
