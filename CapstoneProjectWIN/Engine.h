#pragma once
#include <Windows.h>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <GL/GL.h>
#include <GL/GLU.h>

#include "Joystick.h"
#include <vector>

class Engine {
private:
	bool isrunning;
	bool success;
	SDL_Window* window;
	SDL_GLContext context;
	unsigned int framerate;
	Uint32 firsttick;

	unsigned int windowW, windowH;
	unsigned int rendererW, rendererH;

	void recalcRenderer();

	std::vector<Joystick*> alljoysticks;

public:
	void init();
	void end();
	void makeWindow(unsigned int, unsigned int, std::string);
	void setGLDefaults();

	bool getRunning();
	void clearScreen();
	void drawScreen();

	void setPosition(unsigned int, unsigned int);
	void setSize(unsigned int, unsigned int);
	void setName(std::string);
	void setResolution(unsigned int, unsigned int);

	void maximizeWindow();
	void restoreWindow();
	void fullscreenWindow();
	void normalscreenWindow();

	void stop();

	void setFPS(unsigned int);

	bool getKey(SDL_Scancode);

	void addJoystick(Joystick*);

	Engine();
	virtual ~Engine();
};