#pragma once

#include "Engine/GameEngine.h"
#include "Cookie.h"

class CookieSpawner : public GameObject {
public:
	CookieSpawner(int ispawnDelay, sf::Vector2i imaxCookieSpeedx100);
	//Methods overriden from GameObject
	void update(sf::Time& elapsed);
private:
	int timer = 0;
	//Timer is reset to spawnDelay each time a cookie is added
	int spawnDelay;
	//The max cookie speed in both directions times 100 since rand doesn't work with floats
	sf::Vector2i maxCookieSpeedx100;
};

typedef std::shared_ptr<CookieSpawner> CookieSpawnerPtr;