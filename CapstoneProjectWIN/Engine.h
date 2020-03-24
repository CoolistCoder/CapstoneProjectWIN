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

#include "Image.h"

#include "ErrorLog.h"

class Engine {
private:
	bool isrunning;
	bool success;
	SDL_Window* window;
	SDL_GLContext context;
	unsigned int framerate;
	Uint32 firsttick;
	ErrorLog* log; //the error log that the engine will know about (TODO IMPLEMENT THIS)

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
	unsigned int getResW() { return this->rendererW; }; //get the renderer's width
	unsigned int getResH() { return this->rendererH; }; //get the renderer's height

	void maximizeWindow();
	void restoreWindow();
	void fullscreenWindow();
	void normalscreenWindow();

	void stop();

	void setFPS(unsigned int);

	static bool getKey(SDL_Scancode);

	void addJoystick(Joystick*);
	Joystick* getJoystick(unsigned int); //retrieves a joystick based on its index

	Engine();
	virtual ~Engine();
};