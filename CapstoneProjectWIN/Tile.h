#pragma once
#include "Sprite.h" //include the sprite so we can use it for collisions

//The tile is a sprite that does not move freely, nor rotates
//it is confined to a gridlike pattern based on its size

class Tile : public Entity, public Image
{
protected:
    //todo for the most part, duplicate how the sprite works - rotation
public:
    //todo modify the draw function to draw the tile based on its position * its width (or height)
    //todo modify the draw function to remove its rotation
    //todo modify the draw to ONLY draw if the tile is within the rendering area
};

