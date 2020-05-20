
#include "Player.h"

void Player::control(Entity* p) {
	//make the player a fleshy color
	static_cast<Player*>(p)->modifyColor(255, 203, 209);

	//set the player's frame to 0
	static_cast<Player*>(p)->setFrame(0);

	//allow the player to run
	static_cast<Player*>(p)->run();

	//make sure the fire key isn't being pressed
	if (!Engine::getKey(SDL_SCANCODE_LCTRL)) {
		//make the player move around
		if (Engine::getKey(SDL_SCANCODE_DOWN)) {
			static_cast<Player*>(p)->moveDown();
		}
		if (Engine::getKey(SDL_SCANCODE_UP)) {
			static_cast<Player*>(p)->moveUp();
		}
		if (Engine::getKey(SDL_SCANCODE_LEFT)) {
			static_cast<Player*>(p)->moveLeft();
		}
		if (Engine::getKey(SDL_SCANCODE_RIGHT)) {
			static_cast<Player*>(p)->moveRight();
		}
	}
	else {
		//TODO perform the fire
		static_cast<Player*>(p)->setFrame(3);
		//we need the player to have the ability to make lasers
		static_cast<Player*>(p)->shootLaser();
	}

	//we need to check against all walls.  If the player knows it has walls, we need to die when we collide with them
	if (static_cast<Player*>(p)->walls) {
		//if the player knows about the walls
		for (unsigned int i = 0; i < static_cast<Player*>(p)->walls->tileQuantity(); i++) {
			//check each tile to see if a collision has occured
			if (static_cast<Player*>(p)->walls->getTile(i)->collideAgainst(static_cast<Player*>(p)) &&
				static_cast<Player*>(p)->walls->getTile(i)->isFrame(1)) {
				//this determines whether or not the player is colliding with a tile that happens to be a wall
				static_cast<Player*>(p)->setBehavior(Player::die); //make it die
			}
		}
	}

	const int laserspeed = 8; //the speed of the laser


	//fire the laser!
	if (static_cast<Player*>(p)->fired) {
		static_cast<Player*>(p)->lasersound->play();
		if (!static_cast<Player*>(p)->savedDirection) { //if the laser is supposed to go left
			static_cast<Player*>(p)->laser->setLinePosition(
				static_cast<Player*>(p)->laserStartX,
				static_cast<Player*>(p)->laserStartY,
				static_cast<Player*>(p)->laserX + static_cast<Player*>(p)->w,
				static_cast<Player*>(p)->laserY
			);

			static_cast<Player*>(p)->laserStartX -= laserspeed;
			static_cast<Player*>(p)->laserX -= laserspeed;
		}
		else { //if the laser is supposed to go right
			static_cast<Player*>(p)->laser->setLinePosition(
				static_cast<Player*>(p)->laserStartX,
				static_cast<Player*>(p)->laserStartY,
				static_cast<Player*>(p)->laserX + static_cast<Player*>(p)->w,
				static_cast<Player*>(p)->laserY
			);

			static_cast<Player*>(p)->laserStartX += laserspeed;
			static_cast<Player*>(p)->laserX += laserspeed;


		}

		//check if a wall collision was made
		if (static_cast<Player*>(p)->walls) {
			//if the player knows about the walls
			for (unsigned int i = 0; i < static_cast<Player*>(p)->walls->tileQuantity(); i++) {
				//check each tile to see if a collision has occured
				if (static_cast<Player*>(p)->walls->getTile(i)->collideAgainst(static_cast<Player*>(p)->laserStartX, static_cast<Player*>(p)->laserStartY) &&
					static_cast<Player*>(p)->walls->getTile(i)->isFrame(1)) {
					//this determines whether or not the player is colliding with a tile that happens to be a wall
					static_cast<Player*>(p)->fired = false;
					static_cast<Player*>(p)->lasersound->stop();
				}
			}
		}

		static_cast<Player*>(p)->laser->execute();
	}
	else {
		static_cast<Player*>(p)->laser->setLinePosition(-1, -1, -1, -1);
		static_cast<Player*>(p)->laserX = 0;
		static_cast<Player*>(p)->laserY = 0;
		static_cast<Player*>(p)->laserStartX = 0;
		static_cast<Player*>(p)->laserStartY = 0;
	}



	//now draw the player
	static_cast<Player*>(p)->draw();
}

void Player::die(Entity* p) {
	static_cast<Player*>(p)->modifyColor(255, 255, 0);
	static_cast<Player*>(p)->deathsound->play();
	static int waitstatic = 0;
	waitstatic++;
	if (waitstatic > 2) {
		//we need to make the player electrocute and restart
		if (static_cast<Player*>(p)->frame != 0 && static_cast<Player*>(p)->frame != 4) {
			//if the frame of the sprite is neither 1 or 5
			//we want to set it to 0
			static_cast<Player*>(p)->frame = 0;
		}
		else {
			//if the frame is 1 or 5 we want to alternate between them
			if (static_cast<Player*>(p)->frame == 0) {
				static_cast<Player*>(p)->frame = 4;
			}
			else {
				static_cast<Player*>(p)->frame = 0;
			}
		}
		waitstatic = 0;
		//make the laser reset too
		static_cast<Player*>(p)->fired = false;
	}


	static_cast<Player*>(p)->draw();

	//increment waittime until it reaches the point it needs to be at
	static_cast<Player*>(p)->waittime++;
	if (static_cast<Player*>(p)->waittime > static_cast<Player*>(p)->deathwait) {
		static_cast<Player*>(p)->waittime = 0; //the waittime is reset
		static_cast<Player*>(p)->score--; //remove 1 from the score
		static_cast<Player*>(p)->deathsound->stop();
		static_cast<Player*>(p)->setBehavior(Player::setup); //reset the object
	}

}

void Player::setup(Entity* p) {
	//this function sets up the default values for the player
	//give the player its appropriate sprite
	static_cast<Player*>(p)->loadImage("guy.png");
	//set up the properties for the sprite
	static_cast<Player*>(p)->setFrameCount(5, 1); //5 tiles across, 1 down
	static_cast<Player*>(p)->setSize(12, 16); //make the sprite about as big as its frame
	static_cast<Player*>(p)->setPosition(1920 / 8, 1080 / 8);

	//at the end of setup, switch to control mode
	static_cast<Player*>(p)->setBehavior(Player::control);

}

void Player::moveDown() {
	//set the frame appropriately
	if (walkDelayTimer < walkDelayMax) {
		walkDelayTimer++; //increment the walkdelaytimer as long as it is lower than the max
	}
	else {
		//reset the timer and toggle the frame
		this->walkFrame++;
		if (this->walkFrame > 2) {
			this->walkFrame = 1;
		}
		walkDelayTimer = 0;
	}
	this->setFrame(walkFrame); //set this to the walkframe

	//just move and update the position
	this->y += this->speed;
	this->setPosition(this->x, this->y);
}

void Player::moveUp() {
	//set the frame appropriately
	if (walkDelayTimer < walkDelayMax) {
		walkDelayTimer++; //increment the walkdelaytimer as long as it is lower than the max
	}
	else {
		//reset the timer and toggle the frame
		this->walkFrame++;
		if (this->walkFrame > 2) {
			this->walkFrame = 1;
		}
		walkDelayTimer = 0;
	}
	this->setFrame(walkFrame); //set this to the walkframe
	//just move and update the position
	this->y -= this->speed;;
	this->setPosition(this->x, this->y);

}

void Player::moveLeft() {
	//set the frame appropriately
	if (walkDelayTimer < walkDelayMax) {
		walkDelayTimer++; //increment the walkdelaytimer as long as it is lower than the max
	}
	else {
		//reset the timer and toggle the frame
		this->walkFrame++;
		if (this->walkFrame > 2) {
			this->walkFrame = 1;
		}
		walkDelayTimer = 0;
	}
	this->setFrame(walkFrame); //set this to the walkframe

		//make the player laser face left
	this->laserLeft = true;
	this->laserRight = false;

	//make sure to mirror properly
	this->activateHorizontalFlip();

	//just move and update the position
	this->x -= this->speed;;
	this->setPosition(this->x, this->y);

}

void Player::shootLaser() {
	//create a laser!
	//if a laser is not present we want to allow the player to create one
	if (!this->fired) {
		this->fired = true; //make the laser fire!

		//check the direction
		if (this->laserLeft) {
			this->savedDirection = false; //it goes left
		}
		else if (this->laserRight) {
			this->savedDirection = true; //it goes right
		}

		//the starting positions rely on the direction
		if (this->savedDirection) { //make the laser move right from the palm
			this->laserX = this->x + 11;
			this->laserY = this->y + 5;
			this->laserStartX = this->x + 11;
			this->laserStartY = this->y + 5;
			this->laser->setLinePosition(this->x, this->y, this->x + this->w, this->y);
		}
		else { //make the laser move left from the palm
			this->laserX = this->x - 11;
			this->laserY = this->y + 5;
			this->laserStartX = this->x - 11;
			this->laserStartY = this->y + 5;
			this->laser->setLinePosition(this->x, this->y, this->x + this->w, this->y);
		}



	}

}

void Player::moveRight() {
	//set the frame appropriately
	if (walkDelayTimer < walkDelayMax) {
		walkDelayTimer++; //increment the walkdelaytimer as long as it is lower than the max
	}
	else {
		//reset the timer and toggle the frame
		this->walkFrame++;
		if (this->walkFrame > 2) {
			this->walkFrame = 1;
		}
		walkDelayTimer = 0;
	}
	this->setFrame(walkFrame); //set this to the walkframe

		//make the player laser face right
	this->laserRight = true;
	this->laserLeft = false;

	//make sure to mirror properly
	this->deactivateHorizontalFlip();

	//just move and update the position
	this->x += this->speed;;
	this->setPosition(this->x, this->y);
}

void Player::kill() {
	//just set the behavior to die
	this->setBehavior(Player::die);
}

void Player::run() {
	//if the shift key is held, the player will run
	if (Engine::getKey(SDL_SCANCODE_LSHIFT)) {
		this->speed = 5;
	}
	else {
		this->speed = 3;
	}
}

void Player::wallIs(Tilemap* w) {
	if (w) {
		this->walls = w; //give the player the wall data if it is valid
	}
}

void Player::execute() {
	//execute the stored behavior
	this->storedBehavior(this);
}

Player::Player() {
	// TODO Auto-generated constructor stub
	//run the setup function
	this->setBehavior(Player::setup);

	this->walkDelayTimer = 0;
	this->walkFrame = 1;

	//starting off, we have no data
	this->walls = nullptr;
	this->laser = nullptr;

	//we haven't died yet so waittime is 0
	this->waittime = 0;

	//laser values are defaulted
	this->laserLeft = false;
	this->laserRight = true; //by default the player faces right
	this->laserX = 0;
	this->laserY = 0;
	this->laserStartX = this->x;
	this->laserStartY = this->y;

	this->laser = new Line;
	this->laser->setEngine(this->getEngine()); //make sure the laser has everything we need
	this->laser->setLinePosition(-1, -1, -1, -1); //simply make the laser as long as the player
	this->laser->modifyColor(255, 0, 0); //make the laser red
	this->fired = false;

	this->savedDirection = true;

	this->speed = 1;

	//default score values
	this->score = 0;

	//set up the sound variables of the player
	this->lasersound = new Sound;
	this->deathsound = new Sound;
	this->lasersound->loadSound("laser.wav");
	this->deathsound->loadSound("electricity.wav");
	this->lasersound->setChannel(0);
	this->deathsound->setChannel(1);
	this->lasersound->waitUntilDone();
	this->lasersound->setVolume(100);
	this->deathsound->setVolume(40);

}

Player::~Player() {
	// TODO Auto-generated destructor stub

	//we need to delete any sounds that are present
	if (this->lasersound) {
		delete this->lasersound;
	}
	if (this->deathsound) {
		delete this->deathsound;
	}

	//we need to make sure to delete any lasers that are present
	if (this->laser != nullptr) {
		delete this->laser;
	}
}
