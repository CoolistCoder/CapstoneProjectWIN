#include "Tilemap.h"

void Tilemap::defaultBehavior(Entity* e) {
    static_cast<Tilemap*>(e)->drawmap();
}

void Tilemap::createMap(int* arr, unsigned int arrsize) {
    //first empty out the map
    this->clearMap();
    if (!this->empty() && this->getEngine()) {
        Tile* newtile; //generate our tile pointer to add our data to the tilemap
        //create a for loop to determine what attribs to give our tile
        for (unsigned int i = 0; i < arrsize; i++) {
            newtile = new Tile; //create our new tile
            newtile->setFrame(*(arr + i)); //set the frame of the sprite based on the value at arr[i]
            newtile->setEngine(this->getEngine()); //give our tiles the necessary engine
            newtile->shareImage(this);
            this->tiles.push_back(newtile); //add the tile to the tilemap
        }
    }

}

void Tilemap::tileSize(int w, int h) {
    //go through and give each tile a universal size
    for (unsigned int i = 0; i < this->tiles.size(); i++) {
        this->tiles[i]->setSize(w,h);
    }
}

void Tilemap::frameCount(int a, int d) {
    //go through and set each tile's frame count
    for (unsigned int i = 0; i < this->tiles.size(); i++) {
        this->tiles[i]->setFrameCount(a,d);
    }
}

void Tilemap::setPosition(int x, int y) {
    //all this needs to do is change the x and y variables in the object
    this->mapX = x;
    this->mapY = y;
}

void Tilemap::drawmap() {
    if (this->getEngine()) { //Check to see if we have a valid engine FIRST
        //go through each tile stored in our vector and draw it
        for (unsigned int i = 0; i < this->tiles.size(); i++) {
            this->tiles[i]->setPosition
            (
                (i % this->mapW) + this->mapX, //set the tiles across + position of the tilemap itself
                (i / this->mapW) + this->mapY //set the tiles down + position of the tilemap itself
            );
            if (this->assignedCamera) //we need to be absolutely certain that the tiles are being assigned properly
                this->tiles[i]->assigned();

            this->tiles[i]->modifyOffset(this->modposX, this->modposY);
            this->tiles[i]->modifyRenderArea(this->renderAreaW, this->renderAreaH);
            this->tiles[i]->setViewData(this->viewarx, this->viewary, this->viewarw, this->viewarh);

            //determine whether or not to use global colors
            if (!this->individualColors) {
                this->tiles[i]->modifyColor(this->r, this->g, this->b); //set each tile's color to the sprite sheet's
                this->tiles[i]->modifyAlpha(this->a); //set each tile's alpha to the sprite sheet's
            }

            this->tiles[i]->draw();
        }
    }
}

void Tilemap::execute() {
    this->storedBehavior(this);
}

void Tilemap::clearMap() {
    for (unsigned int i = 0; i < this->tiles.size(); i++) {
        this->tiles[i]->nullify(); //nullify the images first
        delete this->tiles[i]; //empty the tiles from the vector
    }
    this->tiles.clear(); //clear out all empty tiles
}

void Tilemap::setSize(int w, int h) {
    if (w > 0 && h > 0) { //just make sure w/h is > 0 before assignment
        this->mapW = w;
        this->mapH = h;
    }
}

Tile* Tilemap::getTile(unsigned int _at) {
    //simply get a tile at the _at index so long as the tile is within the index
    if (_at < this->tiles.size()) {
        return this->tiles[_at];
    }
    return nullptr; //if a tile is not found return null
}

Tilemap::Tilemap() {
    //set data to defaults
    this->mapX = 0;
    this->mapY = 0;
    this->mapW = 4;
    this->mapH = 5;

    //set the individual colors variable to false
    this->individualColors = false;

    //override the default behavior
    this->setBehavior(Tilemap::defaultBehavior);
}

Tilemap::~Tilemap() {
    //TODO implement the free
    for (unsigned int i = 0; i < this->tiles.size(); i++) {
        this->tiles[i]->nullify(); //nullify the images first
        delete this->tiles[i]; //empty the tiles from the vector
    }
    this->tiles.clear(); //clear out all empty tiles
    //std::cout << "Tilemap deleted" << std::endl;
}