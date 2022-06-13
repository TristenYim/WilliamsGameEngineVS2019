#pragma once

#include "Engine/GameEngine.h"

class Scores : public TextObject {
public:
	Scores(sf::Vector2f pos, int charSize, sf::Color textColor, int iplayerScore, sf::Vector2f ipos);

	static void addEnemyScore(int scoreToAdd);
	static void removePlayerScore(int scoreToRemove);

	static sf::Vector2f getPosition();
	sf::FloatRect getCollisionRect();
	void draw();
	void update(sf::Time& elapsed);
private:
	static sf::Sprite sprite_;
	static int playerScore;
	static int enemyScore;

	// To make it seem more like a FIRST game, the player loses if the enemy gets more points than the player
	// The player loses points by getting penalties and the enemy gets points by scoring
	// It's basically just a lives system in different clothes
	static void checkForLosing();
};

typedef std::shared_ptr<Scores> ScoresPtr;