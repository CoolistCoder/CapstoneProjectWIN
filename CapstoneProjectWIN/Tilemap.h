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

public:

    void createMap(int*, unsigned int); //accept in an array of data to generate a map
    void allTileSize(int,int); //sets the size of all tiles within the tilemap
    void allFrameCount(int,int); //sets the frame count of all tiles within the tilemap

    void drawmap(); //draw the tiles stored in our tilemap

    void execute();
    
    Tilemap();
    virtual ~Tilemap();

};

