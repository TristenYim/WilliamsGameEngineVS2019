#pragma once

#include "Engine/GameEngine.h"

class Cookie : public GameObject {
public:
	//Creates cookie
	Cookie(sf::Vector2f ipos, sf::Vector2f ispeed);

	//Methods overriden from GameObject
	void draw();
	void update(sf::Time& elapsed);
	sf::FloatRect getCollisionRect();
	void handleCollision(GameObject& otherObject_);
private:
	sf::Sprite sprite_;
	//The x is the horizontal speed (Positive is left) and the y is the vertical speed (Positive is down)
	sf::Vector2f speed;
};

typedef std::shared_ptr<Cookie> CookiePtr;