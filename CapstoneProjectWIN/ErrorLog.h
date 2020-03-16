#pragma once
//simple object included in the engine designed to give the developer a clue where an error might be
//It is a good way to guage issues and what might be wrong and where

#include <typeinfo> //this is for retrieving an object's type if we need it
#include <iostream>
#include <SDL_image.h>

class ErrorLog {
private:
	std::string errorDescription;
	bool storeToFile;

public:
	void logError(std::string); //logs an error with a standard string
	void logError(const char*); //logs an error with a c string
	void printError(); //prints a logged error
	void popupError(); //creates a popup box with the stored error

	//TODO implement file based error logging

	ErrorLog();
	virtual ~ErrorLog();
};