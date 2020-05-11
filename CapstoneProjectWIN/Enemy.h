#pragma once
#include "Player.h"
#include <random>
#include <ctime>

class Enemy : public Sprite {
private:
	static void setup(Entity*); //this sets up the enemy entity
	//static void straightLine(Entity*); //moves the enemy in a straight line
	static void followPlayer(Entity*); //makes the enemy follow the player
	static void die(Entity*); //make the enemy die

	Player* knownplayer; //the player that the enemy knows about


public:

	void moveToPlayer(); //moves the enemy to the player

	void givePlayer(Player*); //gives the enemy a player to track

	void killUponContact(); //kill the player upon impact

	void killAgainstLaser(); //kill the enemy if in contact with a laser

	void execute(); //execute the stored behavior


	Enemy();
	virtual ~Enemy();
};