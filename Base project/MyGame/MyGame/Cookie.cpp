#include "Cookie.h"
#include "GameScene.h"
#include "Explosion.h"

Cookie::Cookie(sf::Vector2f ipos, sf::Vector2f ispeed) {
	sprite_.setTexture(GAME.getTexture("Resources/meteor.png"));
	sprite_.setPosition(ipos);
	assignTag("cookie");
	speed = ispeed;
	setCollisionCheckEnabled(true);
}

void Cookie::draw() {
	GAME.getRenderWindow().draw(sprite_);
	return;
}

void Cookie::update(sf::Time& elapsed) {
	int msElapsed = elapsed.asMilliseconds();
	sf::Vector2f pos = sprite_.getPosition();

	if (0 > pos.x || GAME.getRenderWindow().getSize().y < pos.y || 0 > pos.y ) {
		if (0 > pos.x) {
			GameScene& currentScene_ = (GameScene&)GAME.getCurrentScene();
			currentScene_.decreaseLives();
		}
		makeDead();
	}
	else {
		sprite_.setPosition(sf::Vector2f(pos.x - speed.x * msElapsed, pos.y + speed.y * msElapsed));
	}
	return;
}

sf::FloatRect Cookie::getCollisionRect() {
	return sprite_.getGlobalBounds();
}

void Cookie::handleCollision(GameObject& otherObject) {
	GameScene& currentScene = (GameScene&)GAME.getCurrentScene();
	if (otherObject.hasTag("laser")) {
		currentScene.increaseScore();
		otherObject.makeDead();
	}
	ExplosionPtr explosion_ = std::make_shared<Explosion>(sprite_.getPosition());
	currentScene.addGameObject(explosion_);
	makeDead();
	return;
}