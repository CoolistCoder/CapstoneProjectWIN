#include "ErrorLog.h"

void ErrorLog::logError(std::string errorDesc) {
	this->errorDescription = errorDesc; //simply give the errorDescription the description of the error
}

void ErrorLog::logError(const char* errorDesc) {
	this->errorDescription = errorDesc; //simply give the errorDescription the description of the error
}

void ErrorLog::printError() {
	//if there's no error, just say so
	if (this->errorDescription.empty()) {
		std::cout << "No errors to report" << std::endl;
	}
	else {
		//if an error is logged, print it out
		std::cout << this->errorDescription << std::endl;
	}
}

void ErrorLog::popupError() {
	//create a little popup using SDL2 to display the error
	if (this->errorDescription.empty())
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "No errors to report", "No errors to report.", nullptr);
	else
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", this->errorDescription.c_str(), nullptr);
}

ErrorLog::ErrorLog() {
	this->storeToFile = false; //by default, we don't need it to store data to a file
}

ErrorLog::~ErrorLog() {

}