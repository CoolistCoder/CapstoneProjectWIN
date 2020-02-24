#pragma once
#include <SDL_image.h>

#include <iostream>

class Joystick {
private:
	static int totaljoysticks;
	int joynum;
	SDL_Joystick* joystick;

	int leftjoyX, leftjoyY;
	int rightjoyX, rightJoyY;

	void updateSticks();

public:
	bool getButton(int);
	bool getPad(int);
	int getLeftStickX();
	int getLeftStickY();
	int getRightStickX();
	int getRightStickY();

	void detect();
	static int getTotalJoysticks();

	Joystick();
	virtual ~Joystick();

};