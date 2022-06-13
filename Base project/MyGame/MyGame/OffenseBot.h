#pragma once

#include "Engine/GameEngine.h"
const std::string OFFENSE_TAG = "offense";

enum Operation { GoUp, GoRight, GoDown, GoLeft, Stop, GoScore };
enum OffenseType { SbaseNshoot, SbaseGshoot, SbaseBshoot, SSbaseGshoot, FbaseNshoot, FbaseGshoot, FbaseBshoot, SFbaseNshoot, SFbaseGshoot, SFOP };

class OffenseBot : public GameObject {
public:
	OffenseBot(sf::Vector2f ipos, bool spawnOnBottom, OffenseType type);

	void update(sf::Time& elapsed);
	sf::FloatRect getCollisionRect();
	void draw();
	void handleCollision(GameObject& otherGameObject);
	sf::Vector2f getPosition();
private:
	std::vector<Operation> directions;
	float movementSpeed;
	int currentOperation = 0;
	float scoringTimer = scoringDelay;
	float scoringDelay;
	int percentChanceOfScoring;
	int hp;
	int reward;

	void move(float msElapsed);
	void scoreAction();

	OffenseBot(OffenseBot const&);
};

typedef std::shared_ptr<OffenseBot> OffenseBotPtr;