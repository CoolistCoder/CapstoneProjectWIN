#include "Engine.h"

void Engine::recalcRenderer() {

}

void Engine::init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		SDL_ShowSimpleMessageBox(
			SDL_MESSAGEBOX_ERROR,
			"ERROR",
			"UNABLE TO INIT SDL",
			nullptr
		);
		return;
	}

	if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) < 1) {
		SDL_ShowSimpleMessageBox(
			SDL_MESSAGEBOX_ERROR,
			"ERROR",
			"UNABLE TO INIT SDL IMAGE",
			nullptr
		);
		return;
	}

	if (Mix_Init(MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_OGG) < 1) {
		SDL_ShowSimpleMessageBox(
			SDL_MESSAGEBOX_ERROR,
			"ERROR",
			"UNABLE TO INIT SDL MIXER",
			nullptr
		);
		return;
	}

	this->success = true;
}

void Engine::end() {
	if (this->context) {
		SDL_GL_DeleteContext(this->context);
	}

	if (this->window) {
		SDL_DestroyWindow(this->window);
	}

	SDL_Quit();
}

void Engine::makeWindow(unsigned int w, unsigned int h, std::string title) {
	if (this->success) {
		this->window = SDL_CreateWindow(
			title.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			w,
			h,
			SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
		);

		if (!this->window) {
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

	SDL_GL_SetSwapInterval(1);

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
}