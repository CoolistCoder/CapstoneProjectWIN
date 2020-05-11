#include "Enemy.h"

void Enemy::setup(Entity* e) {
	Enemy* temp = static_cast<Enemy*>(e); //cast the enemy to make things easier

	//use a little bit of randomness to determine where to put the enemy
	temp->x = rand() % (1920 / 4); //randomize the position of the enemy
	temp->y = rand() % (1080 / 4);

	//then, determine where to put the enemy
	if (temp->x > temp->y) {
		//determine if X is larger than Y
		//if it is, we want to set it at the left or right side of the screen
		if (temp->x < (1920 / 8)) {
			//determine if x is to the left of the screen
			//if it is, we want to set it all the way left
			temp->x = -25;
		}
		else {
			//if the x is to the right
			//make it go all the way to the right
			temp->x = (1920 / 4);
		}

		//regardless, center the y
		temp->y = (1080 / 8);
		//now make it follow the player
		temp->setBehavior(Enemy::followPlayer);
	}
	else {
		//the enemy goes to the top or bottom
		if (temp->y < (1080 / 8)) {
			//if the y is higher than the center
			//make it all the way up
			temp->y = -25;
		}
		else {
			//if it is lower than the center
			//make it all the way down
			temp->y = (1080 / 4);
		}
		//regardless, center the x
		temp->x = (1920 / 8);
		//for now, make the enemy follow the player
		temp->setBehavior(Enemy::followPlayer);
	}

}

void Enemy::followPlayer(Entity* e) {
	Enemy* temp = static_cast<Enemy*>(e); //cast the enemy to make things easier
	temp->moveToPlayer(); //use the movetoplayer code
	temp->killUponContact(); //this will kill the player and the enemy
	temp->killAgainstLaser(); //make the enemy die if shot with a laser
	temp->draw(); //draw the enemy

}

void Enemy::die(Entity* e) {
	Enemy* temp = static_cast<Enemy*>(e); //cast the enemy to make things easier

	//make the enemy go through its setup process once more
	temp->setBehavior(Enemy::setup);

}

void Enemy::moveToPlayer() {
	//simply graduate the enemy's position to the player's position
	if (this->x > this->knownplayer->getPosX()) {
		this->x--;
	}
	else {
		this->x++;
	}

	if (this->y > this->knownplayer->getPosY()) {
		this->y--;
	}
	else {
		this->y++;
	}
}

void Enemy::givePlayer(Player* p) {
	//simply set knownplayer to p
	this->knownplayer = p;
}

void Enemy::killUponContact() {
	//if a collision is make between the player and the enemy, both will die
	if (this->collideAgainst(this->knownplayer)) {
		this->setBehavior(Enemy::die);
		this->knownplayer->kill();
	}
}

void Enemy::killAgainstLaser() {
	//if a collision is made with the player's laser then
	if (this->collideAgainst(this->knownplayer->getLaserX(), this->knownplayer->getLaserY())) {
		this->setBehavior(Enemy::die); //just die
	}
}

void Enemy::execute() {
	//simply run the stored code
	this->storedBehavior(this);
}

Enemy::Enemy() {
	// TODO Auto-generated constructor stub
	//when we create an enemy, randomize the seed
	srand(time(nullptr));
	this->knownplayer = nullptr;

	//load the enemy's image
	this->loadImage("setpieces.png");
	this->setFrameCount(4, 1);
	this->setSize(24, 16);
	this->setFrame(2);

	//set the enemy's default behavior
	this->setBehavior(Enemy::setup);

}

Enemy::~Enemy() {
	// TODO Auto-generated destructor stub
}