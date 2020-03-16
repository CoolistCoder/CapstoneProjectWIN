#include "Engine.h"

void Engine::recalcRenderer() {
	float ratio; //the ratio of width to height
	int scaleW, scaleH; //the adjusted scale of renderer
	int currentW, currentH; //the current window size

	SDL_GetWindowSize(this->window, &currentW, &currentH); //store the size of the window
	ratio = (float)this->windowW / (float)this->windowH; //ratio should be taken from current scene size
	scaleH = currentH; //the renderer height will remain the same as the window height, thus allowing for the ratio to be applied to the other axis
	scaleW = currentH * ratio; //the width will be scaled relative to the height change

	glViewport((currentW / 2) - (scaleW / 2), (currentH / 2) - (scaleH / 2), scaleW, scaleH);

}

void Engine::init() {
	//This is the process of initialization

	//we will first use the everything flag built into SDL
	//in order to test if SDL initialized
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		//this is to attach a specific error message
		std::string errmsg = "UNABLE TO INIT SDL: "; //universal error message beginning
		errmsg.append(SDL_GetError()); //add SDL's error report to message

		//failure to init occurs if the value of SDL_Init < 0
		//we want to show a message box so the user knows what went wrong
		SDL_ShowSimpleMessageBox(
			SDL_MESSAGEBOX_ERROR, //this creates a message box with an error symbol
			"ERROR",			  //this is the box title
			errmsg.c_str(),		  //display our error description
			nullptr				  //our window is currently null, so we should just use nullptr
		);
		//now we need to break from init if this failure has occured
		return;
	}

	//initialize the image module
	if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) < 1) {
		//this is to attach a specific error message
		std::string errmsg = "UNABLE TO INIT SDL: "; //universal error message beginning
		errmsg.append(SDL_GetError()); //add SDL's error report to message

		//IMG init fails if the value of either of the above variables is returned as 0
		//we want to show a message box so the user knows what went wrong
		SDL_ShowSimpleMessageBox(
			SDL_MESSAGEBOX_ERROR, //this creates a message box with an error symbol
			"ERROR",			  //this is the box title
			errmsg.c_str(),		  //display our error description
			nullptr				  //our window is currently null, so we should just use nullptr
		);
		//now we need to break from init if this failure has occured
		return;
	}

	//some setup for SDL_Mixer before initializing
	Mix_OpenAudio(
		44100,				//The range of frequency that the sound is given
		MIX_DEFAULT_FORMAT, //use default settings when using the sound
		2,					//we want 2 channels for audio
		1024);				//the amount of bytes per sample (the higher, the clearer)

	//initialize the mixer module
	if (Mix_Init(MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_OGG) < 1) {
		//this is to attach a specific error message
		std::string errmsg = "UNABLE TO INIT SDL: "; //universal error message beginning
		errmsg.append(SDL_GetError()); //add SDL's error report to message

		//MIX init also fails if the returned value is 0
		//we want to show a message box so the user knows what went wrong
		SDL_ShowSimpleMessageBox(
			SDL_MESSAGEBOX_ERROR, //this creates a message box with an error symbol
			"ERROR",			  //this is the box title
			errmsg.c_str(),		  //display our error description
			nullptr				  //our window is currently null, so we should just use nullptr
		);
		//now we need to break from init if this failure has occured
		return;
	}

	//set the success variable to 'true' if all these processes have run successfully
	this->success = true;
}

void Engine::end() {
	//this happens at the end of the engine's run
	//once finished, the engine needs to clear out all of its elements

	//Close open audio channels
	Mix_CloseAudio();

	//clear out the context
	if (this->context) {//only clear if context is not empty
		SDL_GL_DeleteContext(this->context); //delete active context
	}

	//delete the window
	if (this->window) {//only delete if window is not empty
		SDL_DestroyWindow(this->window); //special function deleting window
										 //and all its properties w/o causing leaks
	}

	//finally, we implement the quit functions
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
	//this function will close any resources that SDL uses
}

void Engine::makeWindow(unsigned int w, unsigned int h, std::string title) {

	if (this->success && !this->window) {//only create window if we successfully initialize engine and a window has not already been created
		//the window needs to be initialized
		//we need to use an SDL function to do this
		this->window = SDL_CreateWindow( //this function properly sets the windows properties
			title.c_str(), //SDL library is written in C, so title must be converted to c string
			SDL_WINDOWPOS_CENTERED, //we want the window appear centered on the screen horizontally
			SDL_WINDOWPOS_CENTERED, //we want the window appear centered on the screen verically
			w,		//width of window
			h,		//height of window
			SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE //we need the window to be our OpenGL target, and to be resizeable
		);

		//check if this was done correctly (otherwise we cannot complete the window init)
		if (!this->window) {
			//if successful, give the window and renderer sizes our values
			this->windowW = w;	//to start, the window's size is what we specified above
			this->windowH = h;
			this->rendererW = this->windowW; //until we change the resolution,
			this->rendererH = this->windowH; //the renderer's size is equal to the window

			//check to see if window is empty
			//if so, display error message
			SDL_ShowSimpleMessageBox(
				SDL_MESSAGEBOX_ERROR, //messagebox is an error box
				"ERROR",			  //title
				"COULD NOT CREATE THE WINDOW", //description of error
				nullptr					//window is not here, so use nullptr
			);
			//we need to leave this function if this process failed
			return;
		}
		else {
			//if the window was properly initialized, we can call the OpenGL setup function,
			//which preps the window for OpenGL
			this->setGLDefaults();
		}
	}
}

void Engine::setGLDefaults() {
	//this function just needs to run in the window creation function
	//first, we need to set the context
	this->context = SDL_GL_CreateContext(this->window);
	//this will give OpenGL information on our window so we can draw to it

	//TODO modify bitsdepth in case we want to change how much depth our graphics need
	//we need to tell our engine what the color depth is so we can fine tune the color depth of our graphics
	const int bitsdepth = 8;	//this is used to set the color depth of our engine for RGBA
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, bitsdepth); //set the bits of our red channel to bitsdepth
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, bitsdepth); //set the bits of our green channel to bitsdepth
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, bitsdepth); //set the bits of our blue channel to bitsdepth
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, bitsdepth); //set the bits of our alpha channel to bitsdepth
	//if all is done right, the color values will range from 0 to 255, with 255 being max opacity

	//the highest version of OpenGL we want to develop for is 3.3, so we want to tell that to OpenGL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	//now we need to tell OpenGL how often we want it to update
	SDL_GL_SetSwapInterval(0);	//disable VSync

	//OpenGL uses triangles to form drawings, which often meet with hard edges
	//to avoid this, we tell OpenGL to smooth them out using this internal function
	glShadeModel(GL_SMOOTH);	//this will make the sprites we load look much less divided

	//we always want to backs of any triangles drawn to be ignored for performance
	glCullFace(GL_BACK); //this will ignore the back side of the triangles drawn

	//when any triangle is drawn to the screen, draw it in a clockwise formation
	glFrontFace(GL_CW);

	//now enable culling
	glEnable(GL_CULL_FACE);

	//we want to be able to adjust the color values of our sprites on the fly and enable transparency
	//we will enable color blending for this
	glEnable(GL_BLEND); //enable the engine to do the color blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	//enable the source image's alpha to be read and allow it to be transparent

	//the clear color for the engine will be black
	glClearColor(0, 0, 0, 255);	//use a solid black, hence why the alpha is at 255 (full opacity)

	//we need to set the viewport for the engine
	//the viewport will show us how much of the scene we can see
	//it is effectively the resolution of the scene
	//before we do this, we will want to get the current size of the window
	int w, h;	//two integers to store the width and height
	//the function we use is a pass by reference SDL function that will get the current size of the window
	SDL_GetWindowSize(this->window, &w, &h);	//this will put the size in the w and h variables
	//now we can set the viewport
	glViewport(0, 0, w, h); //because the window is just created, we don't need to call the recalc function to modify it yet

	//now we want to make sure that we are modifying the perspective of the scene
	//the modes where we modify our OpenGL scene or objects is known as a matrix
	//in this case, we are modifying our projection matrix, which will change how objects are seen from the camera
	glMatrixMode(GL_PROJECTION);	//set the active matrix to the projection matrix
	glLoadIdentity();	//LOAD THE MATRIX< IF THIS STEP IS SKIPPED IT WILL NOT CHANGE THE MATRIX

	//set our perspective to a flat, orthographic view
	//set up the ortho view first
	gluOrtho2D(0, w, h, 0);	//this will change how objects are drawn to the screen using the size of our window
	gluPerspective(
		0.0,				 //the perspective will be completely flat
		(float)w / (float)h, //the aspect ratio is still in place, this will be adjusted with the recalc function
		0.0,				 //the closest we see our 2D objects is at 0, which is where our camera is located
		1024.0				 //the furthest point we should see our objects would be at 1, but this doesn't need to change
	);
	//because our engine is mostly 2D, these values may not change

	//once all this has been done, we can set the isrunning variable to true
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
	this->setPosition(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
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
	this->rendererW = w;
	this->rendererH = h;
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

Joystick* Engine::getJoystick(unsigned int index) {
	if (!this->alljoysticks.empty()) {
		if (index < this->alljoysticks.size()) {
			return this->alljoysticks.at(index);
		}
		return this->alljoysticks.at(0);
	}
	return nullptr;
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