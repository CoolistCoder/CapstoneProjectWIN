#include "Tilemap.h"

void Tilemap::defaultBehavior(Entity* e) {
    static_cast<Tilemap*>(e)->drawmap();
}

void Tilemap::createMap(int* arr, unsigned int arrsize) {
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

void Tilemap::allTileSize(int w, int h) {
    //go through and give each tile a universal size
    for (unsigned int i = 0; i < this->tiles.size(); i++) {
        this->tiles.at(i)->setSize(w,h);
    }
}

void Tilemap::allFrameCount(int a, int d) {
    //go through and set each tile's frame count
    for (unsigned int i = 0; i < this->tiles.size(); i++) {
        this->tiles.at(i)->setFrameCount(a,d);
    }
}

void Tilemap::drawmap() {
    if (this->getEngine()) { //Check to see if we have a valid engine FIRST
        //go through each tile stored in our vector and draw it
        for (unsigned int i = 0; i < this->tiles.size(); i++) {
            this->tiles.at(i)->setPosition
            (
                i % this->mapW,
                i / this->mapW
            );

            this->tiles.at(i)->modifyOffset(this->modposX, this->modposY);
            this->tiles.at(i)->modifyRenderArea(this->renderAreaW, this->renderAreaH);
            this->tiles.at(i)->setViewData(this->viewarx, this->viewary, this->viewarw, this->viewarh);

            this->tiles.at(i)->draw();
        }
    }
}

void Tilemap::execute() {
    this->storedBehavior(this);
}

Tilemap::Tilemap() {
    //set data to defaults
    this->mapX = 0;
    this->mapY = 0;
    this->mapW = 4;
    this->mapH = 5;

    //override the default behavior
    this->setBehavior(Tilemap::defaultBehavior);
}

Tilemap::~Tilemap() {
    //TODO implement the free
    for (unsigned int i = 0; i < this->tiles.size(); i++) {
        if (this->tiles.at(i)) { //check to see if a tile is present at a point
            //delete this->tiles.at(i); //empty the tiles from the vector
        }
        //this->tiles.clear(); //clear out all empty tiles
    }
}