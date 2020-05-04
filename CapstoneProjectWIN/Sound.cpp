#include "Sound.h"

int Sound::globalVolume = 120; //default to the highest volume

void Sound::defaultBehavior(Entity* d) {
	//really, just do nothing
}

void Sound::loadSound(const char* soundfile) {
	//first, make sure the name isn't blank
	if (soundfile) {
		//load the sound into the storedsound pointer
		this->storedSound = Mix_LoadWAV_RW(SDL_RWFromFile(soundfile, "rb"), 1);
		if (this->storedSound) {
			this->isSound = true; //this is a sound, so the sound is true
			this->failedToLoad = false; //the sound did not fail to load
		}
		else {
			//an error has occured!
			this->failedToLoad = true; //the sound failed to load
		}
	}
}

void Sound::loadMusic(const char* musicfile) {
	//first, make sure the name isn't blank
	if (musicfile) {
		//load the music into the storedmusic pointer
		this->storedMusic = Mix_LoadMUS(musicfile);
		if (this->storedMusic) {
			this->isMusic = true; //this is music, so we load it in as music
			this->failedToLoad = false; //the music loaded properly, so this is false
		}
		else {
			//an error has occured!
			this->failedToLoad = true; //the music failed to load, so this is true
		}
	}
}

bool Sound::loaded() {
	return !this->failedToLoad;
}

void Sound::play() {
	//set the volume first!
	Mix_Volume(this->soundChannel, this->volume);
	Mix_VolumeMusic(this->volume);

	if (this->isSound) { //if the sound is just a sound
		if (this->waitTillDone) { //if we have to wait...
			if (!Mix_Playing(this->soundChannel)) {
				Mix_PlayChannel(this->soundChannel, this->storedSound, 0); //play the sound data if the channel isn't playing
			}
		}
		else {
			Mix_PlayChannel(this->soundChannel, this->storedSound, 0); //play the sound
		}
	}
	else if (this->isMusic) { //if the sound is music
		if (this->waitTillDone) { //if we have to wait...
			if (!Mix_PlayingMusic()) {
				Mix_PlayMusic(this->storedMusic, 1); //play the music if no music is playing
			}
		}
		else { //if we don't have to wait
			Mix_PlayMusic(this->storedMusic, 1); //play the music
		}
	}
	//nothing will happen if neither is true
}

void Sound::waitUntilDone() {
	this->waitTillDone = true;
}

void Sound::nowait() {
	this->waitTillDone = false;
}

void Sound::setChannel(int sc) {
	this->soundChannel = sc;
}

void Sound::setVolume(int newvolume) {
	//limit the volume levels between 0 to max (global volume)
	if (newvolume >= 0 && newvolume <= Sound::globalVolume) {
		this->volume = newvolume; //set the volume
	}
}

void Sound::setGlobalVolume(int newvolume) {
	//limit the volume levels between 0 to max (120)
	if (newvolume >= 0 && newvolume <= 120) {
		Sound::globalVolume = newvolume; //set the volume for all sounds
	}
}

void Sound::execute() {
	this->storedBehavior(this); //just execute the stored behavior
}

void Sound::stop() {
	if (this->isSound) { //if the sound is just a sound
		if (Mix_Playing(this->soundChannel)) { //if the sound is playing
			Mix_HaltChannel(this->soundChannel); //stop the sound
		}

	}
	else if (this->isMusic) { //if the sound is music
		if (Mix_PlayingMusic()) {
			Mix_HaltMusic(); //stop the music
		}
	}
	//nothing will happen if neither is true
}

void Sound::pause() {
	if (this->isSound) { //if the sound is just a sound
		if (Mix_Playing(this->soundChannel)) {
			Mix_Pause(this->soundChannel); //pause the channel
		}
	}
	else if (this->isMusic) { //if the sound is music
		if (Mix_PlayingMusic()) {
			Mix_PauseMusic(); //pause the music
		}
	}
	//nothing will happen if neither is true
}

void Sound::resume() {
	if (this->isSound) { //if the sound is just a sound
		if (Mix_Playing(this->soundChannel)) {
			Mix_Resume(this->soundChannel); //resume the channel
		}
	}
	else if (this->isMusic) { //if the sound is music
		if (Mix_PlayingMusic()) {
			Mix_ResumeMusic(); //resume the music
		}
	}
	//nothing will happen if neither is true
}

bool Sound::getPlaying() {
	//first, check to see if this is music or sound
	if (this->isMusic) {
		//if this is music we want to check to see if the music channel is being played
		return Mix_PlayingMusic(); //just return playingmusic
	}
	else if (this->isSound) {
		//if this is sound we want to check to see if the sound channel is being played
		return Mix_Playing(this->soundChannel); //just check to see if the sound channel is playing
	}
	return false; //by default nothing returns
}


Sound::Sound() {
	// TODO Auto-generated constructor stub
	//by default, the sound is not music, nor sound
	this->isMusic = false;
	this->isSound = false;

	//we need our load fail bool to act as a simple error catch
	this->failedToLoad = false;

	//by default, the sound is attached to the first available sound channel
	this->soundChannel = 0;

	//by default, the volume matches the global volume
	this->volume = Sound::globalVolume;

	//by default, the sounds will wait until done
	this->waitTillDone = true;

	this->storedMusic = nullptr;
	this->storedSound = nullptr;

	//set the default behavior
	this->setBehavior(Sound::defaultBehavior);
}

Sound::~Sound() {
	// TODO Auto-generated destructor stub
	if (this->storedSound) { //if we have sound data, we just need to free it
		Mix_FreeChunk(this->storedSound);
	}
	if (this->storedMusic) { //if we have music data, we just need to free it
		Mix_FreeMusic(this->storedMusic);
	}
}