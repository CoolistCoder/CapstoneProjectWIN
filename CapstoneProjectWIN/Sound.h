#pragma once
//Sounds are simply that: they store and play sounds
//They may also play music if a specific load function is used

#include "Entity.h"

class Sound : public Entity {
protected:
	Mix_Chunk* storedSound; //the sound data that's stored in the sound entity
	Mix_Music* storedMusic; //the music data that's stored in the sound entity
	bool isMusic; //this determines if the sound is music
	bool isSound; //this determines if the sound is not music
	bool failedToLoad; //this is just a simple bool to tell us if it loaded or not
	bool waitTillDone; //this flag determines if the sound can only be played when no sounds are playing
	int soundChannel; //the sound channel the sound is attached to
	int volume; //the volume of the sound
	static int globalVolume; //the volume of all sounds

	static void defaultBehavior(Entity*); //the default behavior of the entity

public:
	void loadSound(const char*); //load a sound into the sound entity
	void loadMusic(const char*); //load music in to the sound entity
	bool loaded(); //returns the failedtoload variable
	void play(); //plays the sound data stored in the Sound
	void waitUntilDone(); //sets the waittilldone flag to true
	void nowait(); //sets the waittilldone flag to false
	void setChannel(int); //set the sound channel
	void setVolume(int); //set the volume of the sound
	static void setGlobalVolume(int); //set the volume of all sounds
	void stop(); // stops the sound that's playing
	void pause(); //pauses the sound that's playing
	void resume(); //resumes paused sounds
	bool getPlaying(); //returns if the sound or music is playing

	void execute(); //execute stored behavior


	Sound();
	virtual ~Sound();
};