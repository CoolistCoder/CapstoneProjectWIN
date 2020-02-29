#include "Engine.h"

void Engine::recalcRenderer() {
	float ratio;
	int scaleW, scaleH;
	int currentW, currentH;

	SDL_GetWindowSize(this->window, &currentW, &currentH);
	ratio = (float)this->windowW / (float)this->windowH;
	scaleH = currentH;
	scaleW = currentH * ratio;

	glViewport((currentW / 2) - (scaleW / 2), (currentH / 2) - (scaleH / 2), scaleW, scaleH);

}

void Engine::init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::string errmsg = "UNABLE TO INIT SDL: ";
		errmsg.append(SDL_GetError());

		SDL_ShowSimpleMessageBox(
			SDL_MESSAGEBOX_ERROR,
			"ERROR",
			errmsg.c_str(),
			nullptr
		);
		return;
	}

	if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) < 1) {
		std::string errmsg = "UNABLE TO INIT SDL: ";
		errmsg.append(SDL_GetError());

		SDL_ShowSimpleMessageBox(
			SDL_MESSAGEBOX_ERROR,
			"ERROR",
			errmsg.c_str(),
			nullptr
		);
		return;
	}

	Mix_OpenAudio(
		44100,
		MIX_DEFAULT_FORMAT,
		2,
		1024);

	if (Mix_Init(MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_OGG) < 1) {
		std::string errmsg = "UNABLE TO INIT SDL: ";
		errmsg.append(SDL_GetError());

		SDL_ShowSimpleMessageBox(
			SDL_MESSAGEBOX_ERROR,
			"ERROR",
			errmsg.c_str(),
			nullptr
		);
		return;
	}

	this->success = true;
}

void Engine::end() {
	Mix_CloseAudio();

	if (this->context) {
		SDL_GL_DeleteContext(this->context);
	}

	if (this->window) {
		SDL_DestroyWindow(this->window);
	}

	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Engine::makeWindow(unsigned int w, unsigned int h, std::string title) {

	if (this->success && !this->window) {
		this->window = SDL_CreateWindow(
			title.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			w,
			h,
			SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
		);

		if (!this->window) {
			this->windowW = w;
			this->windowH = h;
			this->rendererW = this->windowW;
			this->rendererH = this->windowH;

			SDL_ShowSimpleMessageBox(
				SDL_MESSAGEBOX_ERROR,
				"ERROR",
				"COULD NOT CREATE THE WINDOW",
				nullptr
			);
			return;
		}
		else {
			this->setGLDefaults();
		}
	}
}

void Engine::setGLDefaults() {
	this->context = SDL_GL_CreateContext(this->window);

	const int bitsdepth = 8;
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, bitsdepth);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, bitsdepth);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, bitsdepth);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, bitsdepth);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	SDL_GL_SetSwapInterval(0);

	glShadeModel(GL_SMOOTH);

	glCullFace(GL_BACK);

	glFrontFace(GL_CW);

	glEnable(GL_CULL_FACE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(0, 0, 0, 255);

	int w, h;
	SDL_GetWindowSize(this->window, &w, &h);
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0, w, h, 0);
	gluPerspective(
		0.0,
		(float)w / (float)h,
		0.0,
		1024.0
	);

	this->isrunning = true;
}

bool Engine::getRunning() {
	return this->isrunning;
}

void Engine::clearScreen() {
	this->firsttick = SDL_GetTicks();

	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			this->isrunning = false;
		}
	}

	this->recalcRenderer();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (!this->alljoysticks.empty()) {
		for (int i = 0; i < Joystick::getTotalJoysticks(); i++) {
			this->alljoysticks.at(i)->detect();
		}
	}
}

void Engine::drawScreen() {
	
	double frameDel = 1000.0 / this->framerate;
	double frameTime = SDL_GetTicks() - this->firsttick;
	if (frameTime < frameDel) {
		SDL_Delay(static_cast<Uint32>(frameDel - frameTime));

	}

	SDL_GL_SwapWindow(this->window);
}

void Engine::setPosition(unsigned int x, unsigned int y) {
	SDL_SetWindowPosition(this->window, x, y);
}

void Engine::setSize(unsigned int w, unsigned int h) {
	this->windowW = w;
	this->windowH = h;
	SDL_SetWindowSize(this->window, w, h);
}

void Engine::setName(std::string newname) {
	if (!newname.empty()) {
		SDL_SetWindowTitle(this->window, newname.c_str());
	}
}

void Engine::setResolution(unsigned int w, unsigned int h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, h, 0);
}

void Engine::maximizeWindow() {
	SDL_MaximizeWindow(this->window);
}

void Engine::restoreWindow() {
	SDL_RestoreWindow(this->window);
}

void Engine::fullscreenWindow() {
	SDL_SetWindowFullscreen(this->window, SDL_WINDOW_FULLSCREEN_DESKTOP);
}

void Engine::normalscreenWindow() {
	SDL_SetWindowFullscreen(this->window, 0);
}

void Engine::stop() {
	this->isrunning = false;
}

void Engine::setFPS(unsigned int newFPS) {
	this->framerate = newFPS;
}

bool Engine::getKey(SDL_Scancode key) {
	if (key >= 0 || key < 256) {
		const Uint8* whichkey = SDL_GetKeyboardState(NULL);

		if (whichkey[key]) {
			return true;
		}
	}
	return false;
}

void Engine::addJoystick(Joystick* newjoystick) {
	if (newjoystick) {
		this->alljoysticks.push_back(newjoystick);
	}
}

Engine::Engine() {
	this->context = 0;
	this->window = nullptr;
	this->isrunning = false;
	this->success = false;
	this->framerate = 60;
	this->windowW = 640;
	this->windowH = 480;

	this->rendererW = this->windowW;
	this->rendererH = this->windowH;

	this->init();
}

Engine::~Engine() {
	this->end();
}