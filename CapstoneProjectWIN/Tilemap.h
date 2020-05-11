#pragma once
#include "Tile.h"
#include <vector>

class Tilemap : public Image, public Entity
{
protected:
    int mapX, mapY; //the X and Y position of the tilemap (in tiles)
    int mapW, mapH; //the Width and Height of the tilemap (in tiles)
    std::vector<Tile*> tiles; //all of the tiles located in the tilemap
    static void defaultBehavior(Entity*); //set the default behavior of the tilemap
    bool individualColors; //determines whether or not to modify the individual colors of the tilemap


public:

    void createMap(int*, unsigned int); //accept in an array of data to generate a map
    void tileSize(int,int); //sets the size of all tiles within the tilemap
    void frameCount(int,int); //sets the frame count of all tiles within the tilemap
    void setPosition(int, int); //sets the position of the tilemap (and all of the tiles within itself)
    void clearMap(); //clears out any data in the tilemap
    void setSize(int, int); //sets the width and height of the tilemap

    Tile* getTile(unsigned int); //gets a tile from the tiles vector

    void isGlobalColor() { this->individualColors = false; }; //forces all tiles to be the same color globally
    void notGlobalColor() { this->individualColors = true; }; //allows all tiles to be individually colored
    unsigned int tileQuantity() { return this->tiles.size(); }; //returns the number of tiles stored

    void drawmap(); //draw the tiles stored in our tilemap

    void execute();
    
    Tilemap();
    virtual ~Tilemap();

};

