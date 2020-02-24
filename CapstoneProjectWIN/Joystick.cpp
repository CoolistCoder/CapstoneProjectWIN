#include "Joystick.h"

int Joystick::totaljoysticks = 0;

void Joystick::detect() {
	this->joystick = SDL_JoystickOpen(this->joynum);
}

void Joystick::updateSticks() {
	this->leftjoyX = SDL_JoystickGetAxis(this->joystick, 0) / 125;
	this->rightJoyY = SDL_JoystickGetAxis(this->joystick, 1) / 125;
	this->leftjoyX = SDL_JoystickGetAxis(this->joystick, 3) / 125;
	this->rightJoyY = SDL_JoystickGetAxis(this->joystick, 4) / 125;

}

bool Joystick::getButton(int button) {
	return SDL_JoystickGetButton(this->joystick, button);
}

bool Joystick::getPad(int dir) {
	if (SDL_JoystickGetHat(this->joystick, 0) == dir)
		return true;
	else return false;
}

int Joystick::getLeftStickX() {
	this->updateSticks();
	return this->leftjoyX;
}

int Joystick::getLeftStickY() {
	this->updateSticks();
	return this->leftjoyY;
}

int Joystick::getRightStickX() {
	this->updateSticks();
	return this->rightjoyX;
}

int Joystick::getRightStickY() {
	this->updateSticks();
	return this->rightJoyY;
}

int Joystick::getTotalJoysticks() {
	return Joystick::totaljoysticks;
}

Joystick::Joystick() {
	this->joynum = Joystick::totaljoysticks;

	Joystick::totaljoysticks++;

	this->joystick = SDL_JoystickOpen(this->joynum);
	
	this->leftjoyX = 0;
	this->leftjoyY = 0;
	this->rightjoyX = 0;
	this->rightJoyY = 0;
}

Joystick::~Joystick() {
	this->totaljoysticks--;
}