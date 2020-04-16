#include "Entity.h"

void Entity::setBehavior(void newBehavior(Entity* e)) {
	//like the scene, just give the stored variable the function
	this->storedBehavior = newBehavior;
}

void Entity::giveJoystick(Joystick* newJoystick) {
	//simply give the entity the joystick
	if (newJoystick) {
		this->knownJoystick = newJoystick;
	}
}

Joystick* Entity::getJoystick() {
	//just return the stored joystick
	return this->knownJoystick;
}

void Entity::attachEntity(Entity* newEntity) {
	//sometimes, we need an entity to be aware of another one
	//by simply providing the entity with another one, we can allow it to use values from the other one
	//but we don't want multiple instances so check first
	for (unsigned int i = 0; i < this->attachedEntities.size(); i++) {
		//simply break if a match is found
		if (this->attachedEntities.at(i) == newEntity)
			return;
	}
	//otherwise attach
	this->attachedEntities.push_back(newEntity);
}

void Entity::coupleEntity(Entity* newEntity) {
	//this one works the same as the attachEntity function but also attaches this entity to the other entity
	this->attachedEntities.push_back(newEntity); //attach the new entity to this entity
	newEntity->attachedEntities.push_back(this); //attach this entity to the new entity
}

Entity* Entity::getAttachedEntity(unsigned int index) {
	//this will return nullptr if the index is not valid
	if (index < this->attachedEntities.size()) {
		return this->attachedEntities.at(index); //if it is valud, return the entity at given index
	}
	return nullptr;
}

void Entity::detachEntity(Entity* e) {
	//this will find which entity the developer would like to detach
	//simply iterate, find if the addresses match, and handle things accordingly
	for (unsigned int i = 0; i < this->attachedEntities.size(); i++) {
		if (this->attachedEntities.at(i) == e) {
			//if we have a match, then detach and return
			this->attachedEntities.erase(this->attachedEntities.begin() + i);
			return; //immediately return
		}
	}
}

void Entity::decoupleEntity(Entity* e) {
	//this will find which entity the developer would like to detach and remove this entity from it as well
	//simply iterate, find if the addresses match, and handle things accordingly

	//first we need to detach this entity from the one we found
	for (unsigned int i = 0; i < e->attachedEntities.size(); i++) {
		if (e->attachedEntities.at(i) == this) {
			//if found, remove it and break from the loop
			e->attachedEntities.erase(e->attachedEntities.begin() + i);
			break;
		}
	}
	//nothing will happen if this is not found

	for (unsigned int i = 0; i < this->attachedEntities.size(); i++) {
		if (this->attachedEntities.at(i) == e) {
			//if we have a match, then detach and return
			this->attachedEntities.erase(this->attachedEntities.begin() + i);
			return; //immediately return
		}
	}
}

void Entity::modifyOffset(int x, int y) {
	//just set the values
	this->modposX = x;
	this->modposY = y;
}

void Entity::modifyRenderArea(int w, int h) {
	if (w > 0 && h > 0) {
		//just set the values
		this->renderAreaW = w;
		this->renderAreaH = h;
	}
}

Entity::Entity() {
	//TODO Auto-Generated constructor stub
	this->priority = 0; //if priorities match, they're drawn in order of when they're added
	this->knownJoystick = nullptr; //initially, there is no joystick
	this->knownEngine = nullptr;
}

Entity::~Entity() {
	//TODO Auto-Generated destructor stub
}