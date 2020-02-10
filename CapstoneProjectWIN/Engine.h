#pragma once
#include <iostream>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <Windows.h>

#include <GL/GL.h>
#include <gl/GLU.h>

class Engine {
private:
	bool isrunning;
	bool success;
	SDL_Window* window;
	SDL_GLContext context;
	unsigned int framerate;
	Uint32 firsttick;

	void recalcRenderer();

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

	void setFPS(unsigned int);

	Engine();
	virtual ~Engine();
};