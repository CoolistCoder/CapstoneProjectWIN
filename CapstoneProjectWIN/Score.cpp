#include "Score.h"

void Score::defaultBehavior(Entity* s) {
	Score* temp = static_cast<Score*>(s);

	//update the score if the score has a player
	if (temp->knownPlayer != nullptr) {
		temp->score = temp->knownPlayer->getScore();
	}
	//just draw the score
	temp->setString("Score: " + std::to_string(temp->score));
	temp->drawText();
}

void Score::givePlayer(Player* p) {
	if (p) //if the value p has data, then give it to the score text
		this->knownPlayer = p;
}

Score::Score() {
	// TODO Auto-generated constructor stub
	this->score = 0;
	this->knownPlayer = nullptr;
	this->setBehavior(Score::defaultBehavior);
}

Score::~Score() {
	// TODO Auto-generated destructor stub
}
