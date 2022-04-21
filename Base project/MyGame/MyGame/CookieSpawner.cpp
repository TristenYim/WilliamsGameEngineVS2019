#include "CookieSpawner.h"

CookieSpawner::CookieSpawner(int ispawnDelay, sf::Vector2i imaxCookieSpeedx100) {
	spawnDelay = ispawnDelay;
	maxCookieSpeedx100 = imaxCookieSpeedx100;
}

void CookieSpawner::update(sf::Time& elapsed) {
	//Determine how much time has passed and adjust the timer
	int msElapsed = elapsed.asMilliseconds();
	timer -= msElapsed;
	
	if (0 >= timer) {
		//Resets the timer
		timer = spawnDelay;

		//Determines the bounds of the game window
		sf::Vector2u size = GAME.getRenderWindow().getSize();

		//Randomizes the location and speed in both directions
		float meteorX = (float)(size.x + 100);
		float meteorY = (float)(rand() % size.y);
		float speedX = (float)(rand() % maxCookieSpeedx100.x) / 100;
		float speedY = (float)(rand() % maxCookieSpeedx100.y) / 100;

		//Adds the cookie
		CookiePtr cookieToAdd = std::make_shared<Cookie>(sf::Vector2f(meteorX, meteorY), sf::Vector2f(speedX, speedY));
		GAME.getCurrentScene().addGameObject(cookieToAdd);
	}
	return;
}